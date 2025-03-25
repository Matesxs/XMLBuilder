//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

TEST(Attributes, SetStringByMethod)
{
    XMLBuilder::Node node("test");
    node.SetAttribute("name", "value");
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test name=\"value\"/>"));
}

TEST(Attributes, SetFloatingNumberByMethod)
{
    XMLBuilder::Node node("test");
    node.SetAttribute("name", 123.456, 5);
    EXPECT_EQ(node.Generate(), std::format("{}<test name=\"{}\"/>\n", DEFAULT_HEADER, std::format("{:.5f}", 123.456)));
}

TEST(Attributes, SetByMethodInvalidName)
{
    XMLBuilder::Node node("test");
    EXPECT_THROW(node.SetAttribute("", "test"), std::invalid_argument);
    EXPECT_THROW(node.SetAttribute("", 123.456, 5), std::invalid_argument);
}

TEST(Attributes, SetStringByOperator)
{
    XMLBuilder::Node node("test");
    node << std::pair("name", "value");
    EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test name=\"value\"/>"));
}

TEST(Attributes, SetFloatingNumberByOperator)
{
    XMLBuilder::Node node("test");
    node << std::pair("name", std::pair(123.456, 5));
    EXPECT_EQ(node.Generate(), std::format("{}<test name=\"{}\"/>\n", DEFAULT_HEADER, std::format("{:.5f}", 123.456)));
}

TEST(Attributes, SetFloatingNumberByOperatorInvalidPrecision)
{
    XMLBuilder::Node node("test");
    EXPECT_THROW(node << std::pair("name", std::pair(123.456, -5)), std::invalid_argument);
}

TEST(Attributes, SetByOperatorInvalidName)
{
    XMLBuilder::Node node("test");
    EXPECT_THROW(node << std::pair("", "test"), std::invalid_argument);
    EXPECT_THROW(node << std::pair("", std::pair(123.456, 5)), std::invalid_argument);
}

TEST(Attributes, Contains)
{
    XMLBuilder::Node node("test");
    node.SetAttribute("name", "value");

    EXPECT_TRUE(node.ContainsAttribute("name"));
    EXPECT_FALSE(node.ContainsAttribute("test"));
    EXPECT_FALSE(node.ContainsAttribute(""));
}

TEST(Attributes, Remove)
{
    XMLBuilder::Node node("test");
    node.SetAttribute("name", "value");

    EXPECT_TRUE(node.ContainsAttribute("name"));
    EXPECT_FALSE(node.RemoveAttribute("test"));
    EXPECT_FALSE(node.RemoveAttribute(""));
    EXPECT_TRUE(node.ContainsAttribute("name"));

    EXPECT_TRUE(node.RemoveAttribute("name"));
    EXPECT_FALSE(node.ContainsAttribute("name"));
}

TEST(Attributes, GetByMethod)
{
    XMLBuilder::Node node1("test1");
    node1.SetAttribute("name", "value1");

    const XMLBuilder::Node node2 = XMLBuilder::Node("test2").SetAttribute("name", "value2");

    EXPECT_EQ(node1.GetAttribute("name"), "value1");
    EXPECT_EQ(node2.GetAttribute("name"), "value2");
}

TEST(Attributes, GetByMethodInvalidName)
{
    XMLBuilder::Node node1("test1");
    node1.SetAttribute("name", "value1");

    const XMLBuilder::Node node2 = XMLBuilder::Node("test2").SetAttribute("name", "value2");

    EXPECT_THROW(node1.GetAttribute("test"), std::out_of_range);
    EXPECT_THROW(node1.GetAttribute(""), std::invalid_argument);
    EXPECT_THROW(node2.GetAttribute("test"), std::out_of_range);
    EXPECT_THROW(node2.GetAttribute(""), std::invalid_argument);
}

TEST(Attributes, GetByOperator)
{
    XMLBuilder::Node node1("test1");
    node1.SetAttribute("name", "value1");

    const XMLBuilder::Node node2 = XMLBuilder::Node("test2").SetAttribute("name", "value2");

    EXPECT_EQ(node1["name"], "value1");
    EXPECT_EQ(node2["name"], "value2");
}

TEST(Attributes, GetByOperatorInvalidName)
{
    XMLBuilder::Node node1("test1");
    node1.SetAttribute("name", "value1");

    const XMLBuilder::Node node2 = XMLBuilder::Node("test2").SetAttribute("name", "value2");

    EXPECT_THROW(node1["test"], std::out_of_range);
    EXPECT_THROW(node1[""], std::invalid_argument);
    EXPECT_THROW(node2["test"], std::out_of_range);
    EXPECT_THROW(node2[""], std::invalid_argument);
}

TEST(Attributes, SetMultiple)
{
    XMLBuilder::Node node("test");
    node.SetAttribute("name1", "value1");
    node.SetAttribute("name2", 123);
    node.SetAttribute("name3", 123.456, 1);

    EXPECT_EQ(node.Generate(), std::format("{}<test name1=\"value1\" name2=\"123\" name3=\"{:.1f}\"/>\n", DEFAULT_HEADER, 123.456));
}

TEST(Attributes, RemoveMultiple)
{
    XMLBuilder::Node node("test");
    node.SetAttribute("name1", "value1");
    node.SetAttribute("name2", 123);
    node.SetAttribute("name3", 123.456, 1);

    EXPECT_TRUE(node.RemoveAttribute("name2"));
    EXPECT_FALSE(node.RemoveAttribute("name4"));
    EXPECT_TRUE(node.RemoveAttribute("name1"));

    EXPECT_EQ(node.Generate(), std::format("{}<test name3=\"{:.1f}\"/>\n", DEFAULT_HEADER, 123.456));
}

TEST(Attributes, SetAttributeChaining)
{
    XMLBuilder::Node node("test");
    node.SetAttribute("name1", "value1").SetAttribute("name2", 123).SetAttribute("name3", 123.456, 1);

    EXPECT_EQ(node.Generate(), std::format("{}<test name1=\"value1\" name2=\"123\" name3=\"{:.1f}\"/>\n", DEFAULT_HEADER, 123.456));
}
