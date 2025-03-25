//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

TEST(Tag, Create)
{
    XMLBuilder::RootNode node;
    EXPECT_EQ(node.Generate(), std::format("{}", DEFAULT_HEADER));
}

TEST(Tag, CreateEmpty)
{
    EXPECT_THROW(XMLBuilder::Node(""), std::invalid_argument);
}

TEST(Tag, Modify)
{
    XMLBuilder::Node node("test1");
    EXPECT_TRUE(node.SetTag("test2"));
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test2/>"));
}

TEST(Tag, ModifyInvalid)
{
    XMLBuilder::Node node("test1");
    EXPECT_FALSE(node.SetTag(""));
}

TEST(Tag, Get)
{
    XMLBuilder::Node node("test");
    EXPECT_EQ(node.GetTag(), "test");

    node.SetTag("test2");
    EXPECT_EQ(node.GetTag(), "test2");
}
