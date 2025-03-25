//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

TEST(NodeCasting, ChildableNodeAsParent)
{
    XMLBuilder::Node node1("test1");
    XMLBuilder::ValueNode node2("test2", "test2");
    XMLBuilder::ParentNode node3("test3");

    XMLBuilder::meta::NodeBase* nodePtr = nullptr;

    nodePtr = &node1;
    EXPECT_EQ(nodePtr->As<XMLBuilder::Node>().GetTag(), "test1");

    nodePtr = &node2;
    EXPECT_EQ(nodePtr->As<XMLBuilder::ValueNode>().GetTag(), "test2");
    EXPECT_EQ(nodePtr->As<XMLBuilder::ValueNode>().GetValue(), "test2");

    nodePtr = &node3;
    EXPECT_EQ(nodePtr->As<XMLBuilder::ParentNode>().GetTag(), "test3");
}

TEST(NodeCasting, ChildableNodeAsInvalidParent)
{
    XMLBuilder::Node node1("test1");
    XMLBuilder::ValueNode node2("test2", "test2");
    XMLBuilder::ParentNode node3("test3");

    XMLBuilder::ChildableNode* nodePtr = nullptr;

    nodePtr = &node1;
    EXPECT_THROW(nodePtr->As<XMLBuilder::ParentNode>(), std::invalid_argument);

    nodePtr = &node2;
    EXPECT_THROW(nodePtr->As<XMLBuilder::Node>(), std::invalid_argument);

    nodePtr = &node3;
    EXPECT_THROW(nodePtr->As<XMLBuilder::ValueNode>(), std::invalid_argument);
}

TEST(NodeCasting, ChildableNodeAsInvalidTypeS)
{
    XMLBuilder::Node node1("test1");
    XMLBuilder::ValueNode node2("test2", "test2");
    XMLBuilder::ParentNode node3("test3");

    XMLBuilder::ChildableNode* nodePtr = nullptr;

    nodePtr = &node1;
    EXPECT_THROW(nodePtr->As<XMLBuilder::meta::Attributable<XMLBuilder::Node>>(), std::invalid_argument);

    nodePtr = &node2;
    EXPECT_THROW(nodePtr->As<XMLBuilder::RootNode>(), std::invalid_argument);

    nodePtr = &node3;
    EXPECT_THROW(nodePtr->As<std::string>(), std::invalid_argument);
}

TEST(NodeCasting, NodeAsChildable)
{
    XMLBuilder::Node node1("test1");
    XMLBuilder::ValueNode node2("test2", "test2");
    XMLBuilder::ParentNode node3("test3");

    XMLBuilder::ChildableNode* nodePtr = nullptr;

    nodePtr = &node1;
    EXPECT_NO_THROW(nodePtr->As());

    nodePtr = &node2;
    EXPECT_NO_THROW(nodePtr->As());

    nodePtr = &node3;
    EXPECT_NO_THROW(nodePtr->As());
}

TEST(NodeCasting, NodeAsChildableRetainType)
{
    XMLBuilder::Node node1("test1");
    XMLBuilder::ValueNode node2("test2", "test2");
    XMLBuilder::ParentNode node3("test3");

    XMLBuilder::ChildableNode* nodePtr = nullptr;

    nodePtr = &node1;
    EXPECT_EQ(nodePtr->As().Type(), XMLBuilder::NodeType::NT_NODE);

    nodePtr = &node2;
    EXPECT_EQ(nodePtr->As().Type(), XMLBuilder::NodeType::NT_VALUE);

    nodePtr = &node3;
    EXPECT_EQ(nodePtr->As().Type(), XMLBuilder::NodeType::NT_PARENT);
}
