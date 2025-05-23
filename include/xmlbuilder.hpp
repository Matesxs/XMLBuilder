#pragma once

#include <format>
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
		 * @brief String types convertible to std::string_view
		 * @details Defines all types that are convertible to std::string_view, in other words all string types
		 * 
		 * @tparam T Type to check
		 */
		template<class T>
		concept Strings = std::is_convertible_v<T, std::string_view>;

		/**
		 * @brief Non-string types convertible to std::string
		 * @details Defines all non-string (arithmetical) types that can be converted to std::string
		 * 
		 * @tparam T Type to check
		 */
		template<typename T>
		concept Stringable = requires(T t) { { std::to_string(t) } -> std::same_as<std::string>; };

		/**
		 * @brief String and non-string types convertible to std::string
		 * @details Defines types that are directly string type or is convertible to std::string
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

        /**
        * @brief Whole number type
        * @brief Defines all whole number types
        *
        * @tparam T Type to check
        */
		template<class T>
		concept Integral = std::is_integral_v<T>;

		/**
		* @brief Types of nodes
		*/
		enum NodeTypes
		{
		    NT_NODE, ///< Points to Node
		    NT_VALUE, ///< Points to ValueNode
		    NT_PARENT, ///< Points to ParentNode
		    NT_UNKNOWN, ///< Unknown node
		};

		/**
		 * @brief Type converters
		 */
		namespace converters
		{
			/**
			 * @brief %Stringlike type to std::string conversion
			 * @details Convert any %Stringlike type to string
			 * 
			 * @tparam T XMLBuilder::types::Stringlike object type
			 * @param t XMLBuilder::types::Stringlike object to conver to std::string
			 * @return std::string Value converted to string
			 */
			template<Stringlike T>
			auto toString(const T& t) -> std::string
			{
				if constexpr (Stringable<T>)
					return std::format("{}", t);
				else
					return std::string(t);
			}

			/**
			 * @brief %Floating point number to std::string conversion
			 * @details Convert any %Floating type to string with fixed precision
			 * 
			 * @tparam T XMLBuilder::types::Floating type of value
			 * @param value %Floating point value to convert to std::string
			 * @param precision Number of fixed decimal places the floating point number will have as a string
			 * @return std::string %Floating point number converted to string
			 */
			template<Floating T>
			auto floatingToString(const T value, const size_t precision) -> std::string
			{
				std::ostringstream ss;
				ss << std::fixed << std::setprecision(precision); // NOLINT(*-narrowing-conversions)
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
			 * @brief Construct a new %Tagged object
			 * @warning Throws std::invalid_argument exception when tag is empty
			 * 
			 * @tparam T XMLBuilder::types::Strings type of tag
			 * @param tag Value object of tag
			 */
			template<types::Strings T>
			Tagged(const T& tag) : // NOLINT(*-explicit-constructor)
				m_tag(tag)
			{
				if (m_tag.empty())
					throw std::invalid_argument("Tag can't be empty");
			}

			virtual ~Tagged() = default;

            /**
            * @brief Modify tag of the node
            *
            * @tparam T XMLBuilder::types::Strings type of tag
            * @param tag New tag of the node
            */
			template<types::Strings T>
            auto SetTag(const T& tag) -> bool
            {
                const std::string newTag(tag);
	            if (newTag.empty()) return false;
	            m_tag = newTag;
	            return true;
            }

            /**
            * @brief Get node tag
            * @details Returns constant reference to node tag
            *
            * @return const std::string& Constant reference to node tag
            */
			[[nodiscard]] auto GetTag() const -> const std::string&
			{
			    return m_tag;
			}

		protected:
			/**
			 * @brief Tag stored as a string
			 */
			std::string m_tag;
		};


		/**
		 * @brief Definition of class that can be generated
		 * @details Defines interface that generator classes can use as final string output
		 */
		class Generatable
		{
		public:
			virtual ~Generatable() = default;

			/**
			 * @brief Method to generate final string
			 * @details Creates new stream, creates XML header and calls _Generate function
			 * 
			 * @param version Version string for XML header
			 * @param encoding Encoding string for XML header
			 * @return std::string Final output string
			 */
			[[nodiscard]] auto Generate(const std::string& version = "1.0", const std::string& encoding = "Windows-1250") const -> std::string
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
			auto Print(std::ostream& stream) const -> std::ostream&
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
			friend auto operator<<(std::ostream& stream, const Generatable& object) -> std::ostream&
			{
				return object.Print(stream);
			}

			/**
			 * @brief Generate final string on direct string conversion
			 * @details Returns result of Generate function
			 * 
			 * @return std::string Final output string
			 */
			explicit operator std::string() const
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
			[[nodiscard]] static auto _GenerateDepthPadding(const size_t depth) -> std::string  // NOLINT(*-reserved-identifier)
			{
			    // Easy way of returning string with *n* characters
			    return std::string(depth, '\t'); // NOLINT(*-return-braced-init-list)
			}

			/**
			 * @brief Interface for generating output to stream of a node
			 * @details Virtual method implemented by child nodes used to generate string representation of the node and its children (if applicable) to output stream
			 * 
			 * @param outputStream Output stream
			 * @param depth Current depth of the node
			 */
			virtual void _Generate(std::ostringstream& outputStream, size_t depth) const = 0; // NOLINT(*-reserved-identifier)
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
			Attributable() = default;

		public:
			virtual ~Attributable() = default;

			/**
			 * @brief Add or modify stringlike attribute
			 * @details Add new stringlike attribute if the attribute name is not present in this node
			 * @warning Attribute names are unique
			 * @warning Throws std::invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @tparam V XMLBuilder::types::Stringlike type of the attribute value
			 * @param name Name of the attribute
			 * @param value Value of the attribute
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::Strings N, types::Stringlike V>
			auto SetAttribute(const N& name, const V& value) -> ParentType&
			{
				const std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				m_attributes.insert_or_assign(key, types::converters::toString(value));
				return static_cast<ParentType&>(*this);
			}

			/**
			 * @brief Add or modify floating point attribute
			 * @details Add new floating point attribute if the attribute name is not present in this node
			 * @warning Attribute names are unique
			 * @warning Throws std::invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @tparam V XMLBuilder::types::Floating type of attribute value
			 * @param name Name of the attribute
			 * @param value Value of the attribute
			 * @param precision Fixed precision of the floating point value to be saved in attribute value
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::Strings N, types::Floating V>
			auto SetAttribute(const N& name, const V value, size_t precision) -> ParentType&
			{
				const std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				m_attributes.insert_or_assign(key, types::converters::floatingToString(value, precision));
				return static_cast<ParentType&>(*this);
			}

			/**
			 * @brief Check if node contains attribute
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return true Attribute name is present in the node
			 * @return false Attribute name is not present in the node
			 */
			template<types::Strings N>
			auto ContainsAttribute(const N& name) const -> bool
			{
				const std::string key(name);
				if (key.empty()) return false;
				return m_attributes.contains(key);
			}

			/**
			 * @brief Remove existing attribute
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return true Attribute removed
			 * @return false Invalid name or attribute not present in node
			 */
			template<types::Strings N>
			auto RemoveAttribute(const N& name) -> bool
			{
				const std::string key(name);
				if (key.empty()) return false;
				if (!ContainsAttribute(key)) return false;

				m_attributes.erase(key);

				return true;
			}

			/**
			 * @brief Returns reference to the string value of attribute
			 * @warning Throws std::out_of_range exception if called with name of attribute that is not present in node
			 * @warning Throws std::invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return std::string& Reference to the string value of attribute
			 */
			template<types::Strings N>
			auto GetAttribute(const N& name) -> std::string&
			{
				const std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				if (!ContainsAttribute(key))
					throw std::out_of_range("Key not in attributes");

				return m_attributes.at(key);
			}

			/**
			 * @brief Returns constant reference to the string value of attribute
			 * @warning Throws std::out_of_range exception if called with name of attribute that is not present in node
			 * @warning Throws std::invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return const std::string& Constant reference to the string value of attribute
			 */
			template<types::Strings N>
			auto GetAttribute(const N& name) const -> const std::string&
			{
				const std::string key(name);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				if (!ContainsAttribute(key))
					throw std::out_of_range("Key not in attributes");

				return m_attributes.at(key);
			}

			/**
			 * @brief Returns reference to the string value of attribute
			 * @details Operator calling Attributable::GetAttribute for getting reference of the string value of attribute
			 * @warning Throws std::out_of_range exception if called with name of attribute that is not present in node
			 * @warning Throws std::invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return std::string& Reference to the string value of attribute
			 */
			template<types::Strings N>
			auto operator[](const N& name) -> std::string&
			{
				return GetAttribute(name);
			}

			/**
			 * @brief Returns constant reference to the string value of attribute
			 * @details Operator calling XMLBuilder::meta::Attributable::GetAttribute for getting string value of attribute
			 * @warning Throws std::out_of_range exception if called with name of attribute that is not present in node
			 * @warning Throws std::invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @param name Name of attribute
			 * @return const std::string& Constant reference to the string value of attribute
			 */
			template<types::Strings N>
			auto operator[](const N& name) const -> const std::string&
			{
				return GetAttribute(name);
			}

			/**
			 * @brief Operator for adding or modifying stringlike attribute
			 * @warning Throws std::invalid_argument exception if called with empty attribute name
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @tparam V XMLBuilder::types::Stringlike type of the attribute value
			 * @param data Data pair of attribute name and new attribute value
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::Strings N, types::Stringlike V>
			auto operator<<(const std::pair<N, V>& data) -> ParentType&
			{
				const std::string key(data.first);
				if (key.empty())
					throw std::invalid_argument("Key can't be empty");

				m_attributes.insert_or_assign(key, types::converters::toString(data.second));

				return static_cast<ParentType&>(*this);
			}

			/**
			 * @brief Operator for adding or modifying floating point attribute
			 * @warning Throws std::invalid_argument exception if called with empty attribute name
			 * @warning Throws std::invalid_argument exception if called with precision value lower than 0
			 * 
			 * @tparam N XMLBuilder::types::Strings type for name of the attribute
			 * @tparam V XMLBuilder::types::Floating type of the attribute value
			 * @tparam P XMLBuilder::types::Integral type of attribute value precision
			 * @param data Data pair of attribute name and pair of attribute value and fixed value precision
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::Strings N, types::Floating V, types::Integral P>
			auto operator<<(const std::pair<N, std::pair<V, P>>& data) -> ParentType&
			{
				const std::string key(data.first);
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
			void _WriteAttributes(std::ostringstream& outputStream) const // NOLINT(*-reserved-identifier)
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
		friend ParentType;
};


		/**
		 * @brief Base meta class of node
		 * @details Only as a separator of root node and standard nodes
		 */
		class NodeBase : public Generatable
		{
		/**
		 * @brief Friend of XMLBuilder::meta::ChildrenStore class
		 * @details Because child store access XMLBuilder::meta::NodeBase::_Generate method of the generatable nodes
		 *
		 * @tparam ParentType Parent type of child store
		 */
		template<class ParentType>
		friend class ChildrenStore;

		public:
		    /**
		    * @brief Return type of the node
		    * @details Virtual method that signals true type of the node when in it's node base form
		    *
		    * @return XMLBuilder::types::NodeTypes Type of the node
            */
		    [[nodiscard]] virtual auto Type() const -> types::NodeTypes = 0;

			/**
			* @brief Cast instance of the base node class as parent type
			* @warning Raises std::invalid_argument exception when trying to cast to type that is not based on this class
			* @warning Throws std::invalid_argument exception when cast to requested type failed
			*
			* @tparam ParentType Type to which cast this object
			* @return ParentType& Reference to this object casted to parent type
			*/
			template<class ParentType = NodeBase>
			auto As() -> ParentType&
			{
				if constexpr (!std::is_base_of_v<NodeBase, ParentType>)
					throw std::invalid_argument("Node type is not a child");

				if constexpr (std::is_same_v<ParentType, NodeBase>)
					return *this;
				else
				{
					auto childPtrCasted	= dynamic_cast<ParentType*>(this);
					if (!childPtrCasted)
						throw std::invalid_argument("This is not valid type of this child");

					return *childPtrCasted;
				}
			}
		};
	}

	/**
	* @brief Common type for nodes that can be added as child node
	* @details Exposed XMLBuilder::meta::NodeBase for users to use for referencing common type for all nodes that can be assigned as child nodes
	*/
	using ChildableNode = meta::NodeBase;

	/**
	* @brief Types of nodes
	* @details User exposed XMLBuilder::types::NodeTypes
	*/
	using NodeType = types::NodeTypes;

	namespace types
	{
		/**
		 * @brief Check for base node type
		 * @details Used to limit child node type only to types based on XMLBuilder::ChildableNode
		 * @tparam T Type to check
		 */
		template <typename T>
		concept ChildableNodeBased = std::is_base_of_v<ChildableNode, T>;
	}

	namespace meta
	{
		/**
		 * @brief Store of children nodes
		 * @details Class for storage of children and implement interface for managing them
		 * @details Childs are stored as vector of shared pointers of ChildableNode for keeping reference to the data of original type
		 * 
		 * @tparam ParentType Parent type of the actual node
		 */
		template<class ParentType>
		class ChildrenStore
		{
			ChildrenStore() = default;

		public:
			virtual ~ChildrenStore() = default;

			/**
			 * @brief Add child node
			 * @details Add child node to vector of children of node
			 * 
			 * @tparam ChildType ChildableNode type of child
			 * @param child Child reference object
			 * @return ParentType& Return self reference based on parent type for chaining
			 */
			template<types::ChildableNodeBased ChildType>
			auto AddChild(const ChildType& child) -> ParentType&
			{
				m_children.push_back(std::make_shared<ChildType>(child));
				return static_cast<ParentType&>(*this);
			}

			/**
			 * @brief Return number of children nodes stored
			 * 
			 * @return size_t Number of stored children
			 */
			[[nodiscard]] auto ChildrenCount() const -> size_t
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
			auto RemoveChild(const size_t idx) -> bool
			{
				if (idx >= ChildrenCount()) return false;
				m_children.erase(m_children.begin() + idx); // NOLINT(*-narrowing-conversions)
				return true;
			}

			/**
			 * @brief Return reference to child
			 * @details Base pointer of the child gets converted back to the pointer to parent type and returned as a reference
			 * @warning Throws std::out_of_range exception when index is invalid
			 * @warning Throws std::invalid_argument exception when cast to requested type failed
			 * 
			 * @tparam ChildType XMLBuilder::types::ChildableNodeBased type of child
			 * @param idx Index of child node
			 * @return ChildType& Reference to child object
			 */
			template<types::ChildableNodeBased ChildType = ChildableNode>
			auto ChildAt(const size_t idx) -> ChildType&
			{
				if (idx >= ChildrenCount())
					throw std::out_of_range("Index out of range");

				if constexpr (std::is_same_v<ChildType, NodeBase>)
					return *m_children.at(idx);
				else
				{
					auto childPtrCasted	= std::dynamic_pointer_cast<ChildType>(m_children.at(idx));
					if (!childPtrCasted)
						throw std::invalid_argument("This is not valid type of this child");

					return *childPtrCasted;
				}
			}

			/**
			 * @brief Return child by constant reference
			 * @details Base pointer of the child gets converted back to the pointer to parent type and returned as constant reference
			 * @warning Throws std::out_of_range exception when index is invalid
			 * @warning Throws std::invalid_argument exception when cast to requested type failed
			 * 
			 * @tparam ChildType XMLBuilder::types::ChildableNodeBased type of child
			 * @param idx Index of child node
			 * @return const ChildType& Constant reference to child object
			 */
			template<types::ChildableNodeBased ChildType = ChildableNode>
			auto ChildAt(const size_t idx) const -> const ChildType&
			{
				if (idx >= ChildrenCount())
					throw std::out_of_range("Index out of range");

				if constexpr (std::is_same_v<ChildType, NodeBase>)
					return *m_children.at(idx);
				else
				{
					auto childPtrCasted	= std::dynamic_pointer_cast<ChildType>(m_children.at(idx));
					if (!childPtrCasted)
						throw std::invalid_argument("This is not valid type of this child");

					return *childPtrCasted;
				}
			}

			/**
			* @brief Returns iterator pointing to first child node
			* @return std::vector<std::shared_ptr<XMLBuilder::ChildableNode>>::iterator Iterator pointing to first child node
			*/
			auto begin() -> std::vector<std::shared_ptr<ChildableNode>>::iterator
			{
				return m_children.begin();
			}

			/**
			* @brief Returns iterator pointing to one past last child node
			* @return std::vector<std::shared_ptr<XMLBuilder::ChildableNode>>::iterator Iterator pointing to one past last child node
			*/
			auto end() -> std::vector<std::shared_ptr<ChildableNode>>::iterator
			{
				return m_children.end();
			}

			/**
			* @brief Returns read-only iterator pointing to first child node
			* @return std::vector<std::shared_ptr<XMLBuilder::ChildableNode>>::const_iterator Read-only iterator pointing to first child node
			*/
			[[nodiscard]] auto begin() const -> std::vector<std::shared_ptr<ChildableNode>>::const_iterator
			{
				return m_children.begin();
			}

			/**
			* @brief Returns read-only iterator pointing to one past last child node
			* @return std::vector<std::shared_ptr<XMLBuilder::ChildableNode>>::const_iterator Read-only iterator pointing to one past last child node
			*/
			[[nodiscard]] auto end() const -> std::vector<std::shared_ptr<ChildableNode>>::const_iterator
			{
				return m_children.end();
			}

			/**
			* @brief Returns reverse iterator pointing to last child node
			* @return std::vector<std::shared_ptr<XMLBuilder::ChildableNode>>::reverse_iterator Reverse iterator pointing to last child node
			*/
			auto rbegin() -> std::vector<std::shared_ptr<ChildableNode>>::reverse_iterator
			{
				return m_children.rbegin();
			}

			/**
			* @brief Returns reverse iterator pointing to one before first child node
			* @return std::vector<std::shared_ptr<XMLBuilder::ChildableNode>>::reverse_iterator Iterator pointing to one before first child node
			*/
			auto rend() -> std::vector<std::shared_ptr<ChildableNode>>::reverse_iterator
			{
				return m_children.rend();
			}

			/**
			* @brief Returns read-only reverse iterator pointing to last child node
			* @return std::vector<std::shared_ptr<XMLBuilder::ChildableNode>>::const_reverse_iterator Read-only reverse iterator pointing to last children node
			*/
			[[nodiscard]] auto rbegin() const -> std::vector<std::shared_ptr<ChildableNode>>::const_reverse_iterator
			{
				return m_children.rbegin();
			}

			/**
			* @brief Returns read-only reverse iterator pointing to one before first child node
			* @return std::vector<std::shared_ptr<XMLBuilder::ChildableNode>>::const_reverse_iterator Read-only reverse iterator pointing to one before first child node
			*/
			[[nodiscard]] auto rend() const -> std::vector<std::shared_ptr<ChildableNode>>::const_reverse_iterator
			{
				return m_children.rend();
			}

            /**
            * @brief Index operator
            * @details Returning reference to child object
            * @warning Throws std::out_of_range exception when index is invalid
            *
            * @param idx Index of child node
            * @return XMLBuilder::ChildableNode& Reference to child object
            */
			auto operator[](const size_t idx) -> ChildableNode&
			{
				if (idx >= ChildrenCount())
					throw std::out_of_range("Index out of range");

				return *m_children.at(idx);
			}

			/**
			* @brief Constant index operator
			* @details Returning constant reference to child object
			* @warning Throws std::out_of_range exception when index is invalid
			*
			* @param idx Index of child node
			* @return const XMLBuilder::ChildableNode& Constant reference to child object
			*/
			auto operator[](const size_t idx) const -> const ChildableNode&
			{
				if (idx >= ChildrenCount())
					throw std::out_of_range("Index out of range");

				return *m_children.at(idx);
			}

		protected:
			/**
			 * @brief Check if node have children
			 * 
			 * @return true %Node have children
			 * @return false %Node don't have children
			 */
			[[nodiscard]] auto _HaveChildren() const -> bool // NOLINT(*-reserved-identifier)
			{
				return !m_children.empty();
			}

			/**
			 * @brief Write data of each child to output stream
			 * 
			 * @param outputStream Output stream
			 * @param depth Current depth of the node
			 */
			void _WriteChildren(std::ostringstream& outputStream, const size_t depth) const // NOLINT(*-reserved-identifier)
			{
				for (auto& child : m_children)
					child->_Generate(outputStream, depth);
			}

		private:
			/**
			 * @brief Child storage as vector of shared pointer of XMLBuilder::ChildableNode
			 */
			std::vector<std::shared_ptr<ChildableNode>> m_children;
		friend ParentType;
};
	}

	/**
	 * @brief Most basic node
	 * @details %Node with basic node interface, tag and attributes
	 */
	class Node final : public meta::NodeBase, public meta::Tagged, public meta::Attributable<Node>
	{
	public:
		/**
		 * @brief Construct a new %Node object
		 * 
		 * @tparam T XMLBuilder::types::Strings type of tag
		 * @param tag Value of the tag
		 */
		template<types::Strings T>
		Node(const T& tag) : // NOLINT(*-explicit-constructor)
			Tagged(tag)
		{ }

		/**
		* @brief Return type of the node
		* @details Implementation of XMLBuilder::meta::NodeBase virtual method that signals true type of the node when in it's node base form
		*
		* @return XMLBuilder::types::NodeTypes::NT_NODE
		*/
		[[nodiscard]] auto Type() const -> types::NodeTypes override
		{
		    return types::NodeTypes::NT_NODE;
		}

	protected:
		/**
		 * @brief Implementation of XMLBuilder::meta::NodeBase::_Generate method
		 * @details Method for outputing it's XML representation to output stream
		 * 
		 * @param outputStream Output stream
		 * @param depth Current node depth
		 */
		void _Generate(std::ostringstream& outputStream, const size_t depth) const override
		{
			const std::string paddingString = _GenerateDepthPadding(depth);
			outputStream << paddingString;
			outputStream << '<' << m_tag;

			_WriteAttributes(outputStream);

			outputStream << "/>" << std::endl;
		}
	};


	/**
	 * @brief %Node for storing value
	 * @details %Node with base node interface, tag, attributes and storage for value
	 */
	class ValueNode final : public meta::NodeBase, public meta::Tagged, public meta::Attributable<ValueNode>
	{
	public:
		/**
		 * @brief Construct a new Value %Node object
		 * @details Create node from tag and stringlike value
		 * 
		 * @tparam T XMLBuilder::types::Strings type of tag
		 * @tparam V XMLBuilder::types::Stringlike type of value
		 * @param tag Value of the tag
		 * @param value Value to store in node
		 */
		template<types::Strings T, types::Stringlike V>
		ValueNode(const T& tag, const V& value) :
			Tagged(tag),
			m_value(types::converters::toString(value))
		{
			if (m_value.empty())
				throw std::invalid_argument("Value can't be empty");
		}

		/**
		 * @brief Construct a new Value Node object
		 * @details Create node from tag and floating point value
		 * 
		 * @tparam T XMLBuilder::types::Strings type of tag
		 * @tparam V XMLBuilder::types::Floating type of value
		 * @param tag Value of the tag
		 * @param value Value to store in node
		 * @param precision Fixed precision of floating point value to store
		 */
		template<types::Strings T, types::Floating V>
		ValueNode(const T& tag, const V value, size_t precision) :
			Tagged(tag),
			m_value(types::converters::floatingToString(value, precision))
		{ }

		/**
		* @brief Return type of the node
		* @details Implementation of XMLBuilder::meta::NodeBase virtual method that signals true type of the node when in it's node base form
		*
		* @return XMLBuilder::types::NodeTypes::NT_VALUE
		*/
		[[nodiscard]] auto Type() const -> types::NodeTypes override
		{
			return types::NodeTypes::NT_VALUE;
		}

		/**
		 * @brief Modify value of node by stringlike value
		 * 
		 * @tparam V XMLBuilder::types::Stringlike type of value
		 * @param value New value for the node
		 * @return true Value was modified
		 * @return false Value was invalid
		 */
		template<types::Stringlike V>
		auto SetValue(const V& value) -> bool
		{
			const std::string newValue(types::converters::toString(value));
			if (newValue.empty()) return false;
			m_value = newValue;
			return true;
		}

		/**
		 * @brief Modify value of node by floating point value
		 * 
		 * @tparam V XMLBuilder::types::Floating type of value
		 * @param value New value for the node
		 * @param precision Fixed precision of floating point value
		 * @return true Value was modified
		 * @return false Value was invalid
		 */
		template<types::Floating V>
		auto SetValue(const V value, size_t precision) -> bool
		{
			const std::string newValue(types::converters::floatingToString(value, precision));
			m_value = newValue;
			return true;
		}

		/**
		 * @brief Get value of the node
		 * 
		 * @return const std::string& Constant reference to node value string
		 */
		[[nodiscard]] auto GetValue() const -> const std::string&
		{
			return m_value;
		}

		/**
		 * @brief Modify value of node by stringlike value
		 * @warning Throws std::invalid_argument exception if value is empty
		 * 
		 * @tparam V XMLBuilder::types::Stringlike type of value
		 * @param value New value for the node
		 * @return ValueNode& Return self reference for chaining
		 */
		template<types::Stringlike V>
		auto operator=(const V& value) -> ValueNode&
		{
			const std::string newValue(types::converters::toString(value));
			if (newValue.empty())
				throw std::invalid_argument("Value can't be empty");

			m_value = newValue;
			return *this;
		}

		/**
		 * @brief Modify value of node by floating point value
		 * @warning Throws std::invalid_argument exception if called with precision value lower than 0
		 * 
		 * @tparam V XMLBuilder::types::Floating type of value
		 * @tparam P XMLBuilder::types::Integral type of value precision
		 * @param data Pair of value and fixed value precision
		 * @return ValueNode& Return self reference for chaining
		 */
		template<types::Floating V, types::Integral P>
		auto operator=(const std::pair<V, P>& data) -> ValueNode&
		{
			if (data.second < 0)
				throw std::invalid_argument("Precision can't be lower than 0");

			const std::string newValue(types::converters::floatingToString(data.first, static_cast<size_t>(data.second)));
			m_value = newValue;
			return *this;
		}

	protected:
		/**
		 * @brief Implementation of XMLBuilder::meta::NodeBase::_Generate method
		 * @details Method for outputing it's XML representation to output stream
		 * 
		 * @param outputStream Output stream
		 * @param depth Current node depth
		 */
		void _Generate(std::ostringstream& outputStream, const size_t depth) const override
		{
			const std::string paddingString = _GenerateDepthPadding(depth);
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
	 * @brief %Node for storing other nodes
	 * @details %Node with base node interface, tag, attributes and storage of other nodes
	 */
	class ParentNode final : public meta::NodeBase, public meta::Tagged, public meta::Attributable<ParentNode>, public meta::ChildrenStore<ParentNode>
	{
	public:
		/**
		 * @brief Construct a new Parent %Node object
		 * 
		 * @tparam T XMLBuilder::types::Strings type of tag
		 * @param tag Value of the tag
		 */
		template<types::Strings T>
		ParentNode(const T& tag) : // NOLINT(*-explicit-constructor)
			Tagged(tag)
		{ }

		/**
		* @brief Return type of the node
		* @details Implementation of XMLBuilder::meta::NodeBase virtual method that signals true type of the node when in it's node base form
		*
		* @return XMLBuilder::types::NodeTypes::NT_PARENT
		*/
		[[nodiscard]] auto Type() const -> types::NodeTypes override
		{
			return types::NodeTypes::NT_PARENT;
		}

	protected:
		/**
		 * @brief Implementation of XMLBuilder::meta::NodeBase::_Generate method
		 * @details Method for outputing it's XML representation and of children nodes stored in it to output stream
		 * 
		 * @param outputStream Output stream
		 * @param depth Current node depth
		 */
		void _Generate(std::ostringstream& outputStream, const size_t depth) const override
		{
			const std::string paddingString = _GenerateDepthPadding(depth);
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
	 * @brief %Node for storing other nodes
	 * @details %Node without interface of other standard nodes, used only for storing nodes on the highest level
	 */
	class RootNode final : public meta::Generatable, public meta::ChildrenStore<RootNode>
	{
	public:
		/**
		 * @brief Construct a new Root %Node object
		 */
		RootNode() = default;

	protected:
		/**
		 * @brief Implementation of XMLBuilder::meta::NodeBase::_Generate method
		 * @details Method for outputing XML representation of children nodes stored in it to output stream
		 * @details This node don't have any other function than storing children and can't be used only as most top level node
		 * 
		 * @param outputStream Output stream
		 * @param depth Current node depth
		 */
		void _Generate(std::ostringstream& outputStream, const size_t depth) const override
		{
			_WriteChildren(outputStream, depth);
		}
	};
}
