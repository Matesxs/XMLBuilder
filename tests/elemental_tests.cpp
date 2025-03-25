//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

TEST(Create, RootNode)
{
    XMLBuilder::RootNode node;
    EXPECT_EQ(node.Generate(), std::format("{}", DEFAULT_HEADER));
}

TEST(Create, Node)
{
    XMLBuilder::Node node("test");
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test/>"));
}

TEST(Create, ValueNodeString)
{
    XMLBuilder::ValueNode node("test", "test");
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test>test</test>"));
}

TEST(Create, ValueNodeFloatingNumber)
{
    XMLBuilder::ValueNode node("test", 123.456, 5);
    EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, std::format("{:.5f}", 123.456)));
}

TEST(Create, ParentNode)
{
    XMLBuilder::ParentNode node("test");
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test/>"));
}

TEST(Create, ParentNodeWithChild)
{
    XMLBuilder::ParentNode node("test");
    node.AddChild(XMLBuilder::Node("test"));
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test>\n\t<test/>\n</test>"));
}
