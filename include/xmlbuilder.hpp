#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <type_traits>
#include <stdexcept>

/**
 * @brief Main namespace of the libry
 */
namespace XMLBuilder
{
	/**
	 * @brief Type definitions
	 */
	namespace types
	{
		/**
		 * @brief String types convertible to string
		 * @details Defines all types that are convertible to string_view, in other words all string types
		 * 
		 * @tparam T Type to check
		 */
		template<class T>
		concept Strings = std::is_convertible_v<T, std::string_view>;

		/**
		 * @brief Non-string types convertible to string
		 * @details Defines all non-string (arithmetical) types that can be converted to string
		 * 
		 * @tparam T Type to check
		 */
		template<typename T>
		concept Stringable = requires(T t) { { std::to_string(t) } -> std::same_as<std::string>; };

		/**
		 * @brief String and non-string types convertible to string
		 * @details Defines types that are directly string type or is convertible to string
		 * 
		 * @tparam T Type to check
		 */
		template<typename T>
		concept Stringlike = Strings<T> || Stringable<T>;

		/**
		 * @brief Floating point numbers
		 * @details Defines all floating point types
		 * 
		 * @tparam T Type to check
		 */
		template<class T>
		concept Floating = std::is_floating_point_v<T>;

		template<class T>
		concept Integral = std::is_integral_v<T>;

		/**
		 * @brief Type converters
		 */
		namespace converters
		{
			/**
			 * @brief %Stringlike type to string conversion
			 * @details Convert any %Stringlike type to string
			 * 
			 * @tparam T Stringlike object type
			 * @param t %Stringlike object to conver to string
			 * @return decltype(auto) Value converted to string
			 */
			template<Stringlike T>
			inline decltype(auto) toString(T& t)
			{
				if constexpr (Stringable<T>)
					return std::format("{}", t);
				else
					return std::string(t);
			}

			/**
			 * @brief %Floating point number string conversion
			 * @details Convert any %Floating type to string with fixed precision
			 * 
			 * @tparam T Floating type of value
			 * @param value %Floating point value
			 * @param precision Number of fixed decimal places the floating point number will have as a string
			 * @return std::string %Floating point number converted to string
			 */
			template<Floating T>
			inline std::string floatingToString(const T value, size_t precision)
			{
				std::ostringstream ss;
				ss << std::fixed << std::setprecision(precision);
				ss << value;
				return ss.str();
			}
		}
	}

	/**
	 * @brief Meta class definitions
	 */
	namespace meta
	{
		template<class ParentType>
		class ChildrenStore;

		/**
		 * @brief Tag storage
		 * @details Meta class for storing information about node tag
		 */
		class Tagged
		{
		public:
			/**
			 * @brief Construct a new Tagged object
			 * @warning Throws invalid_argument exception when tag is empty
			 * 
			 * @tparam T types::Strings type of tag
			 * @param tag Value object of tag
			 */
			template<types::Strings T>
			Tagged(const T& tag) :
				m_tag(tag)
			{
				if (m_tag.empty())
					throw std::invalid_argument("Tag can't be empty");
			}

		protected:
			/**
			 * @brief Tag stored as a string
			 */
			const std::string m_tag;
		};


		/**
		 * @brief Definition of class that can be generated
		 * @details Defines interface that generator classes can use as final string output
		 */
		class Generatable
		{
		public:
			/**
			 * @brief Method to generate final string
			 * @details Creates new stream, creates XML header and calls _Generate function
			 * 
			 * @param version Version string for XML header
			 * @param encoding Encoding string for XML header
			 * @return std::string Final output string
			 */
			std::string Generate(const std::string& version = "1.0", const std::string& encoding = "Windows-1250") const
			{
				std::ostringstream outputStream;
				outputStream << "<?xml version=\"" << version << "\" encoding=\"" << encoding << "\"?>" << std::endl;
				_Generate(outputStream, 0);
				return outputStream.str();
			}

			/**
			 * @brief Generate and output final string to stream
			 * 
			 * @param stream Reference to output stream
			 * @return std::ostream& Reference to output stream
			 */
			std::ostream& Print(std::ostream& stream) const
			{
				stream << Generate();
				return stream;
			}

			/**
			 * @brief Operator for generating and outputing final string to stream
			 * 
			 * @param stream Reference to output stream
			 * @param object Reference to object being printed
			 * @return std::ostream& Reference to output stream
			 */
			friend std::ostream& operator<<(std::ostream& stream, const Generatable& object)
			{
				return object.Print(stream);
			}

			/**
			 * @brief Generate final string on direct string conversion
			 * @details Returns result of Generate function
			 * 
			 * @return std::string Final output string
			 */
			operator std::string() const
			{
				return Generate();
			}

		protected:
			/**
			 * @brief Padding string generator
			 * @details Generates padding string based on depth in tree of nodes
			 * 
			 * @param depth Current depth in node tree
			 * @return std::string Padding string
			 */
			std::string _GenerateDepthPadding(size_t depth) const
			{
				std::string output;
				for (size_t i = 0; i < depth; i++)
					output.push_back('\t');
				return output;
			}

			/**
			 * @brief Interface for generating output to stream of a node
			 * @details Virtual method implemented by child nodes used to generate string representation of the node and its children (if applicable) to output stream
			 * 
			 * @param outputStream Output stream
			 * @param depth Current depth of the node
			 */
			virtual void _Generate(std::ostringstream& outputStream, size_t depth) const = 0;
		};


		/**
		 * @brief Store of attributes
		 * @details Class for storage of attributes and implement interface for managing them
		 * 
		 * @tparam ParentType Parent type of the actual node
		 */
		template<class ParentType>
		class Attributable
		{
		public:
			/**
			 * @brief Add or modify stringlike attribute
			 * @details Add new stringlike attribute if the attribute name is not present in this node
			 * @warning Attribute names are unique
			 * @warning Throws invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @tparam V types::Stringlike type of the attribute value
			 * @param name Name of the attribute
			 * @param value Value of the attribute
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::Strings N, types::Stringlike V>
			ParentType& AddOrModifyAttribute(const N& name, const V& value)
			{
				std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				m_attributes.insert_or_assign(key, types::converters::toString(value));
				return static_cast<ParentType&>(*this);
			}

			/**
			 * @brief Add or modify floating point attribute
			 * @details Add new floating point attribute if the attribute name is not present in this node
			 * @warning Attribute names are unique
			 * @warning Throws invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @tparam V types::Floating type of attribute value
			 * @param name Name of the attribute
			 * @param value Value of the attribute
			 * @param precision Fixed precision of the floating point value to be saved in attribute value
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::Strings N, types::Floating V>
			ParentType& AddOrModifyAttribute(const N& name, const V value, size_t precision)
			{
				std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				m_attributes.insert_or_assign(key, types::converters::floatingToString(value, precision));
				return static_cast<ParentType&>(*this);
			}

			/**
			 * @brief Check if node contains attribute
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return true Attribute name is present in the node
			 * @return false Attribute name is not present in the node
			 */
			template<types::Strings N>
			bool ContainsAttribute(const N& name) const
			{
				std::string key(name);
				if (key.empty()) return false;
				return m_attributes.contains(key);
			}

			/**
			 * @brief Remove existing attribute
			 * @warning Attribute name need to be present in the node
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return true Attribute removed
			 * @return false Invalid name or attribute not present in node
			 */
			template<types::Strings N>
			bool RemoveAttribute(const N& name)
			{
				std::string key(name);
				if (key.empty()) return false;
				if (!ContainsAttribute(key)) return false;

				m_attributes.erase(key);

				return true;
			}

			/**
			 * @brief Returns reference to the string value of attribute
			 * @warning Throws out_of_range exception if called with name of attribute that is not present in node
			 * @warning Throws invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return std::string& Reference to the string value of attribute
			 */
			template<types::Strings N>
			std::string& attAt(const N& name)
			{
				std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				if (!ContainsAttribute(key))
					throw std::out_of_range("Key not in attributes");

				return m_attributes.at(key);
			}

			/**
			 * @brief Returns string value of attribute
			 * @warning Throws out_of_range exception if called with name of attribute that is not present in node
			 * @warning Throws invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return std::string String value of attribute
			 */
			template<types::Strings N>
			std::string attAt(const N& name) const
			{
				std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				if (!ContainsAttribute(key))
					throw std::out_of_range("Key not in attributes");

				return m_attributes.at(key);
			}

			/**
			 * @brief Returns reference to the string value of attribute
			 * @details Operator calling Attributable::attAt for getting reference of the string value of attribute
			 * @warning Throws out_of_range exception if called with name of attribute that is not present in node
			 * @warning Throws invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return std::string& Reference to the string value of attribute
			 */
			template<types::Strings N>
			std::string& operator[](const N& name)
			{
				return attAt(name);
			}

			/**
			 * @brief Returns string value of attribute
			 * @details Operator calling Attributable::attAt for getting string value of attribute
			 * @warning Throws out_of_range exception if called with name of attribute that is not present in node
			 * @warning Throws invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return std::string String value of attribute
			 */
			template<types::Strings N>
			std::string operator[](const N& name) const
			{
				return attAt(name);
			}

			/**
			 * @brief Operator for adding or modifying stringlike attribute
			 * @warning Throws invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @tparam V types::Stringlike type of the attribute value
			 * @param data Data pair of attribute name and new attribute value
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::Strings N, types::Stringlike V>
			ParentType& operator<<(const std::pair<N, V>& data)
			{
				std::string key(data.first);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				m_attributes.insert_or_assign(key, types::converters::toString(data.second));

				return static_cast<ParentType&>(*this);
			}

			/**
			 * @brief Operator for adding or modifying floating point attribute
			 * @warning Throws invalid_argument exception if called with empty attribute name
			 * @warning Throws invalid_argument exception if called with precision value lower than 0
			 * 
			 * @tparam N types::Strings type for name of the attribute
			 * @tparam V types::Floating type of the attribute value
			 * @tparam P types::Integral type of attribute value precision
			 * @param data Data pair of attribute name and pair of attribute value and fixed value precision
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::Strings N, types::Floating V, types::Integral P>
			ParentType& operator<<(const std::pair<N, std::pair<V, P>>& data)
			{
				std::string key(data.first);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				if (data.second.second < 0)
					throw std::invalid_argument("Precision can't be lower than 0");

				m_attributes.insert_or_assign(key, types::converters::floatingToString(data.second.first, static_cast<size_t>(data.second.second)));

				return static_cast<ParentType&>(*this);
			}

		protected:
			/**
			 * @brief Writes attributes to output stream
			 * @details Helper function for outputing attributes to output stream in valid XML format
			 * 
			 * @param outputStream Output stream
			 */
			void _WriteAttributes(std::ostringstream& outputStream) const
			{
				for (const auto& [attributeName, attributeValue] : m_attributes)
					outputStream << ' ' << attributeName << "=\"" << attributeValue << '\"';
			}

		private:
			/**
			 * @brief Storage of attributes
			 * @details Attributes are stored like name, value pairs because names of the attributes need to be unique
			 */
			std::map<std::string, std::string> m_attributes;
		};


		/**
		 * @brief Base meta class of node
		 * @details Only as a separator of root node and standard nodes
		 */
		class NodeBase : public Generatable
		{
		/**
		 * @brief Friend of meta::ChildrenStore class because child store access NodeBase::_Generate method of its child nodes
		 * @tparam ParentType Parent type of child store
		 */
		template<class ParentType>
		friend class meta::ChildrenStore;
		};
	}

	namespace types
	{
		/**
		 * @brief Check for base node type
		 * @details Used to limit child node type only to types based on XMLBuilder::meta::NodeBase
		 * @tparam T Type to check
		 */
		template <typename T>
		concept XMLNodeBased = std::is_base_of<meta::NodeBase, T>::value;
	}

	namespace meta
	{
		/**
		 * @brief Store of children nodes
		 * @details Class for storage of children and implement interface for managing them
		 * @details Childs are stored as vector of shared pointers of types::XMLNodeBased for keeping reference to the data of original type
		 * 
		 * @tparam ParentType Parent type of the actual node
		 */
		template<class ParentType>
		class ChildrenStore
		{
		public:
			/**
			 * @brief Add child node
			 * @details Add child node to vector of children of node
			 * 
			 * @tparam ChildType types::XMLNodeBased type of child
			 * @param child Child reference object
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::XMLNodeBased ChildType>
			ParentType& AddChild(const ChildType& child)
			{
				m_children.push_back(std::make_shared<ChildType>(child));
				return static_cast<ParentType&>(*this);
			}

			/**
			 * @brief Return number of children nodes stored
			 * 
			 * @return size_t Number of stored children
			 */
			size_t ChildrenCount() const
			{
				return m_children.size();
			}

			/**
			 * @brief Remove child node from this node
			 * 
			 * @param idx Index of child to remove
			 * @return true Child was removed
			 * @return false Invalid index of a child
			 */
			bool RemoveChild(size_t idx)
			{
				if (idx >= ChildrenCount()) return false;

				m_children.erase(m_children.begin() + idx);

				return true;
			}

			/**
			 * @brief Return reference to child
			 * @details Base pointer of the child gets converted back to the pointer to parent type and returned as a reference
			 * @warning Throws out_of_range exception when index is invalid
			 * @todo Rework to something more clever
			 * 
			 * @tparam ChildType types::XMLNodeBased type of child
			 * @param idx Index of child
			 * @return ChildType& Child object reference
			 */
			template<types::XMLNodeBased ChildType>
			ChildType& childAt(size_t idx)
			{
				if (idx >= ChildrenCount())
					throw std::out_of_range("Index out of range");

				return *std::dynamic_pointer_cast<ChildType>(m_children.at(idx));
			}

			/**
			 * @brief Return child by value
			 * @details Base pointer of the child gets converted back to the pointer to parent type and returned as value
			 * @warning Throws out_of_range exception when index is invalid
			 * @todo Rework to something more clever
			 * 
			 * @tparam ChildType types::XMLNodeBased type of child
			 * @param idx Index of child
			 * @return ChildType Copy Child object
			 */
			template<types::XMLNodeBased ChildType>
			ChildType childAt(size_t idx) const
			{
				if (idx >= ChildrenCount())
					throw std::out_of_range("Index out of range");

				return *std::dynamic_pointer_cast<ChildType>(m_children.at(idx));
			}

		protected:
			/**
			 * @brief Check if node have children
			 * 
			 * @return true Node have children
			 * @return false Node don't have children
			 */
			bool _HaveChildren() const
			{
				return !m_children.empty();
			}

			/**
			 * @brief Write data of each child to output stream
			 * 
			 * @param outputStream Output stream
			 * @param depth Current depth of the node
			 */
			void _WriteChildren(std::ostringstream& outputStream, size_t depth) const
			{
				for (auto& child : m_children)
					child->_Generate(outputStream, depth);
			}

		protected:
			/**
			 * @brief Child storage as vector of shared pointer of meta::NodeBase
			 */
			std::vector<std::shared_ptr<meta::NodeBase>> m_children;
		};
	}

	/**
	 * @brief Most basic node
	 * @details Node with basic node interface, tag and attributes
	 */
	class Node : public meta::NodeBase, public meta::Tagged, public meta::Attributable<Node>
	{
	public:
		/**
		 * @brief Construct a new Node object
		 * 
		 * @tparam T types::Strings type of tag
		 * @param tag Value of the tag
		 */
		template<types::Strings T>
		Node(const T& tag) :
			meta::Tagged(tag)
		{ }

	protected:
		/**
		 * @brief Implementation of meta::NodeBase::_Generate method
		 * @details Method for outputing it's XML representation to output stream
		 * 
		 * @param outputStream Output stream
		 * @param depth Current node depth
		 */
		// Inherited via NodeBase
		virtual void _Generate(std::ostringstream& outputStream, size_t depth) const override
		{
			std::string paddingString = _GenerateDepthPadding(depth);
			outputStream << paddingString;
			outputStream << '<' << m_tag;

			_WriteAttributes(outputStream);

			outputStream << "/>" << std::endl;
		}
	};


	/**
	 * @brief Node for storing value
	 * @details Node with base node interface, tag, attributes and storage for value
	 */
	class ValueNode : public meta::NodeBase, public meta::Tagged, public meta::Attributable<ValueNode>
	{
	public:
		/**
		 * @brief Construct a new Value %Node object
		 * @details Create node from tag and stringlike value
		 * @warning Throws invalid_argument exception if called with precision value lower than 0
		 * 
		 * @tparam T types::Strings type of tag
		 * @tparam V types::Stringlike type of value
		 * @param tag Value of the tag
		 * @param value Value to store in node
		 */
		template<types::Strings T, types::Stringlike V>
		ValueNode(const T& tag, const V& value) :
			meta::Tagged(tag),
			m_value(types::converters::toString(value))
		{
			if (m_value.empty())
				throw std::invalid_argument("Value can't be empty");
		}

		/**
		 * @brief Construct a new Value Node object
		 * @details Create node from tag and floating point value
		 * @warning Throws invalid_argument exception if value is empty
		 * 
		 * @tparam T types::Strings type of tag
		 * @tparam V types::Floating type of value
		 * @param tag Value of the tag
		 * @param value Value to store in node
		 * @param precision Fixed precision of floating point value to store
		 */
		template<types::Strings T, types::Floating V>
		ValueNode(const T& tag, const V value, size_t precision) :
			meta::Tagged(tag),
			m_value(types::converters::floatingToString(value, precision))
		{
			if (m_value.empty())
				throw std::invalid_argument("Value can't be empty");
		}

		/**
		 * @brief Modify value of node by stringlike value
		 * 
		 * @tparam V types::Stringlike type of value
		 * @param value New value for the node
		 * @return true Value was modified
		 * @return false Value was invalid
		 */
		template<types::Stringlike V>
		bool ModifyValue(const V& value)
		{
			std::string newValue(types::converters::toString(value));
			if (newValue.empty()) return false;

			m_value = newValue;

			return true;
		}

		/**
		 * @brief Modify value of node by floating point value
		 * 
		 * @tparam V types::Floating type of value
		 * @param value New value for the node
		 * @param precision Fixed precision of floating point value
		 * @return true Value was modified
		 * @return false Value was invalid
		 */
		template<types::Floating V>
		bool ModifyValue(const V value, size_t precision)
		{
			std::string newValue(types::converters::floatingToString(value, precision));
			if (newValue.empty()) return false;

			m_value = newValue;

			return true;
		}

		/**
		 * @brief Get reference to string value of the node
		 * 
		 * @return std::string& Reference to the value of the node
		 */
		std::string& Get()
		{
			return m_value;
		}

		/**
		 * @brief Get value of the node
		 * 
		 * @return std::string Value of the node
		 */
		std::string Get() const
		{
			return m_value;
		}

		/**
		 * @brief Modify value of node by stringlike value
		 * @warning Throws invalid_argument exception if value is empty
		 * 
		 * @tparam V types::Stringlike type of value
		 * @param value New value for the node
		 * @return ValueNode& Return self reference for chaining
		 */
		template<types::Stringlike V>
		ValueNode& operator=(const V& value)
		{
			std::string newValue(types::converters::toString(value));
			if (newValue.empty())
				throw std::invalid_argument("Value can't be empty");

			m_value = newValue;

			return *this;
		}

		/**
		 * @brief Modify value of node by floating point value
		 * @warning Throws invalid_argument exception if value is empty
		 * @warning Throws invalid_argument exception if called with precision value lower than 0
		 * 
		 * @tparam V types::Floating type of value
		 * @tparam P types::Integral type of value precision
		 * @param data Pair of value and fixed value precision
		 * @return ValueNode& Return self reference for chaining
		 */
		template<types::Floating V, types::Integral P>
		ValueNode& operator=(const std::pair<V, P>& data)
		{
			if (data.second < 0)
				throw std::invalid_argument("Precision can't be lower than 0");

			std::string newValue(types::converters::floatingToString(data.first, static_cast<size_t>(data.second)));
			if (newValue.empty())
				throw std::invalid_argument("Value can't be empty");

			m_value = newValue;

			return *this;
		}

	protected:
		/**
		 * @brief Implementation of meta::NodeBase::_Generate method
		 * @details Method for outputing it's XML representation to output stream
		 * 
		 * @param outputStream Output stream
		 * @param depth Current node depth
		 */
		// Inherited via NodeBase
		virtual void _Generate(std::ostringstream& outputStream, size_t depth) const override
		{
			std::string paddingString = _GenerateDepthPadding(depth);
			outputStream << paddingString;
			outputStream << '<' << m_tag;

			_WriteAttributes(outputStream);

			outputStream << '>' << m_value << "</" << m_tag << '>' << std::endl;
		}

	private:
		/**
		 * @brief Stored value of the node in string form
		 */
		std::string m_value;
	};


	/**
	 * @brief Node for storing other nodes
	 * @details Node with base node interface, tag, attributes and storage of other nodes
	 */
	class ParentNode : public meta::NodeBase, public meta::Tagged, public meta::Attributable<ParentNode>, public meta::ChildrenStore<ParentNode>
	{
	public:
		/**
		 * @brief Construct a new Parent %Node object
		 * 
		 * @tparam T types::Strings type of tag
		 * @param tag Value of the tag
		 */
		template<types::Strings T>
		ParentNode(const T& tag) :
			meta::Tagged(tag)
		{ }

	protected:
		/**
		 * @brief Implementation of meta::NodeBase::_Generate method
		 * @details Method for outputing it's XML representation and of children nodes stored in it to output stream
		 * 
		 * @param outputStream Output stream
		 * @param depth Current node depth
		 */
		// Inherited via NodeBase
		virtual void _Generate(std::ostringstream& outputStream, size_t depth) const override
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


	/**
	 * @brief Node for storing other nodes
	 * @details Node without interface of other standard nodes, used only for storing nodes on the highest level
	 */
	class RootNode : public meta::Generatable, public meta::ChildrenStore<RootNode>
	{
	public:
		/**
		 * @brief Construct a new Root %Node object
		 */
		RootNode() = default;

	protected:
		/**
		 * @brief Implementation of meta::NodeBase::_Generate method
		 * @details Method for outputing XML representation of children nodes stored in it to output stream
		 * @details This node don't have any other function than storing children and can't be used only as most top level node
		 * 
		 * @param outputStream Output stream
		 * @param depth Current node depth
		 */
		// Inherited via Generatable
		virtual void _Generate(std::ostringstream& outputStream, size_t depth) const override
		{
			_WriteChildren(outputStream, depth);
		}
	};
}
