#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <type_traits>
#include <stdexcept>

namespace XMLBuilder
{
	namespace types
	{
		template<class T>
		concept Strings = std::is_convertible_v<T, std::string_view>;

		template<typename T>
		concept Stringable = requires(T t) { { std::to_string(t) } -> std::same_as<std::string>; };

		template<typename T>
		concept Stringlike = Strings<T> || Stringable<T>;

		template<class T>
		concept Floating = std::is_floating_point_v<T>;

		namespace converters
		{
			template<Stringlike T>
			decltype(auto) toString(T& t)
			{
				if constexpr (Floating<T>)
					return std::format("{}", t);
				else if constexpr (Stringable<T>)
					return std::to_string(t);
				else
					return t;
			}

			template<Floating T>
			std::string floatingToString(const T value, size_t precision, bool fixed)
			{
				std::stringstream ss;
				if (fixed) ss << std::fixed;
				ss << std::setprecision(precision);
				ss << value;
				return ss.str();
			}
		}
	}

	namespace meta
	{
		template<class ParentType>
		class ChildrenStore;

		class Tagged
		{
		public:
			template<types::Strings T>
			Tagged(const T& tag) :
				m_tag(tag)
			{
				if (m_tag.empty())
					throw std::invalid_argument("Tag can't be empty");
			}

		protected:
			const std::string m_tag;
		};

		template<class ParentType>
		class Attributable
		{
		public:
			template<types::Strings N, types::Stringlike V>
			ParentType& AddAttribute(const N& name, const V& value)
			{
				std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				// Just to not overwrite existing attribute
				if (!m_attributes.contains(key))
					m_attributes.insert({key, std::string(types::converters::toString(value))});
				return static_cast<ParentType&>(*this);
			}

			template<types::Strings N, types::Floating V>
			ParentType& AddAttribute(const N& name, const V value, size_t precision)
			{
				std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				// Just to not overwrite existing attribute
				if (!m_attributes.contains(key))
					m_attributes.insert({key, types::converters::floatingToString(value, precision, true)});
				return static_cast<ParentType&>(*this);
			}

		protected:
			void _WriteAttributes(std::stringstream& outputStream) const
			{
				for (const auto& [attributeName, attributeValue] : m_attributes)
					outputStream << ' ' << attributeName << "=\"" << attributeValue << '\"';
			}

		private:
			std::map<std::string, std::string> m_attributes;
		};

		class Generatable
		{
			public:
			std::string Generate(const std::string& version = "1.0", const std::string& encoding = "Windows-1250") const
			{
				std::stringstream outputStream;
				outputStream << "<?xml version=\"" << version << "\" encoding=\"" << encoding << "\"?>" << std::endl;
				_Generate(outputStream, 0);
				return outputStream.str();
			}

		protected:
			std::string _GenerateDepthPadding(size_t depth) const
			{
				std::string output;
				for (size_t i = 0; i < depth; i++)
					output.push_back('\t');
				return output;
			}

			virtual void _Generate(std::stringstream& outputStream, size_t depth) const = 0;
		};

		class NodeBase : public Generatable
		{
		template<class ParentType>
		friend class meta::ChildrenStore;

		protected:
			// Inherited via Generatable
			virtual void _Generate(std::stringstream& outputStream, size_t depth) const override
			{
				throw std::runtime_error("Unimplemented");
			}
		};
	}

	class Node : public meta::NodeBase, public meta::Tagged, public meta::Attributable<Node>
	{
	public:
		template<types::Strings T>
		Node(const T& tag) :
			meta::Tagged(tag)
		{ }

	protected:
		// Inherited via NodeBase
		virtual void _Generate(std::stringstream& outputStream, size_t depth) const override
		{
			std::string paddingString = _GenerateDepthPadding(depth);
			outputStream << paddingString;
			outputStream << '<' << m_tag;

			_WriteAttributes(outputStream);

			outputStream << "/>" << std::endl;
		}
	};

	namespace types
	{
		template <typename T>
		concept XMLNodeBased = std::is_base_of<meta::NodeBase, T>::value;
	}

	namespace meta
	{
		template<class ParentType>
		class ChildrenStore
		{
		public:
			template<types::XMLNodeBased ChildType>
			ParentType& AddChild(const ChildType& child)
			{
				m_children.push_back(new ChildType(child));
				return static_cast<ParentType&>(*this);
			}

		protected:
			bool _HaveChildren() const
			{
				return !m_children.empty();
			}

			void _WriteChildren(std::stringstream& outputStream, size_t depth) const
			{
				for (auto& child : m_children)
					child->_Generate(outputStream, depth);
			}

		protected:
			std::vector<meta::NodeBase*> m_children;
		};
	}

	class ValueNode : public meta::NodeBase, public meta::Tagged, public meta::Attributable<Node>
	{
	public:
		template<types::Strings T, types::Stringlike V>
		ValueNode(const T& tag, const V& value) :
			meta::Tagged(tag),
			m_value(types::converters::toString(value))
		{
			if (m_value.empty())
				throw std::invalid_argument("Value can't be empty");
		}

		template<types::Strings T, types::Floating V>
		ValueNode(const T& tag, const V value, size_t precision) :
			meta::Tagged(tag),
			m_value(types::converters::floatingToString(value, precision, true))
		{
			if (m_value.empty())
				throw std::invalid_argument("Value can't be empty");
		}

	protected:
		// Inherited via NodeBase
		virtual void _Generate(std::stringstream& outputStream, size_t depth) const override
		{
			std::string paddingString = _GenerateDepthPadding(depth);
			outputStream << paddingString;
			outputStream << '<' << m_tag;

			_WriteAttributes(outputStream);

			outputStream << '>' << m_value << "</" << m_tag << '>' << std::endl;
		}

	private:
		const std::string m_value;
	};

	class ParentNode : public meta::NodeBase, public meta::Tagged, public meta::Attributable<Node>, public meta::ChildrenStore<ParentNode>
	{
	public:
		template<types::Strings T>
		ParentNode(const T& tag) :
			meta::Tagged(tag)
		{ }

	protected:
		// Inherited via NodeBase
		virtual void _Generate(std::stringstream& outputStream, size_t depth) const override
		{
			std::string paddingString = _GenerateDepthPadding(depth);
			outputStream << paddingString;
			outputStream << '<' << m_tag;

			_WriteAttributes(outputStream);

			if (_HaveChildren())
			{
				outputStream << '>' << std::endl;

				_WriteChildren(outputStream, depth + 1);

				outputStream << paddingString;
				outputStream << "</" << m_tag << '>' << std::endl;
			}
			else
			{
				outputStream << "/>" << std::endl;
			}
		}
	};

	class RootNode : public meta::Generatable, public meta::ChildrenStore<RootNode>
	{
	public:
		RootNode() = default;

	protected:
		// Inherited via Generatable
		virtual void _Generate(std::stringstream& outputStream, size_t depth) const override
		{
			_WriteChildren(outputStream, depth);
		}
	};
}
