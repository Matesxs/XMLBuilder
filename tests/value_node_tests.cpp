//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

TEST(ValueNode, String)
{
    EXPECT_NO_THROW(XMLBuilder::ValueNode node("test", "test"));
}

TEST(ValueNode, FloatingNumber)
{
    EXPECT_NO_THROW(XMLBuilder::ValueNode node("test", 123.456, 5));
}

TEST(ValueNode, InvalidValue)
{
    EXPECT_THROW(XMLBuilder::ValueNode node("test", ""), std::invalid_argument);
}

TEST(ValueNode, SetStringValueByMethod)
{
    XMLBuilder::ValueNode node("test", "value");
    EXPECT_TRUE(node.SetValue("test"));
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test>test</test>"));
}

TEST(ValueNode, SetFloatingNumberValueByMethod)
{
    XMLBuilder::ValueNode node("test", "value");
    EXPECT_TRUE(node.SetValue(123.456, 1));
    EXPECT_EQ(node.Generate(), std::format("{}<test>{:.1f}</test>\n", DEFAULT_HEADER, 123.456));
}

TEST(ValueNode, SetInvalidByMethod)
{
    XMLBuilder::ValueNode node("test", "value");
    EXPECT_FALSE(node.SetValue(""));
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test>value</test>"));
}

TEST(ValueNode, SetStringValueByOperator)
{
    XMLBuilder::ValueNode node("test", "value");
    EXPECT_NO_THROW(node = "test");
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test>test</test>"));
}

TEST(ValueNode, SetFloatingNumberValueByOperator)
{
    XMLBuilder::ValueNode node("test", "value");
    EXPECT_NO_THROW(node = std::pair(123.456, 1));
    EXPECT_EQ(node.Generate(), std::format("{}<test>{:.1f}</test>\n", DEFAULT_HEADER, 123.456));
}

TEST(ValueNode, SetInvalidStringByOperator)
{
    XMLBuilder::ValueNode node("test", "value");
    EXPECT_THROW(node = "", std::invalid_argument);
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test>value</test>"));
}

TEST(ValueNode, SetFloatingNumberValueByOperatorInvalidPrecision)
{
    XMLBuilder::ValueNode node("test", "value");
    EXPECT_THROW(node = std::pair(123.456, -5), std::invalid_argument);
    EXPECT_EQ(node.Generate(), std::format("{}<test>value</test>\n", DEFAULT_HEADER));
}
