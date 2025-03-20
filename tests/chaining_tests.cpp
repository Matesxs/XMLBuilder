#include "common.hpp"

#include <typeinfo>

TEST(KeepType, Node)
{
  XMLBuilder::Node node("test");
  ASSERT_TRUE(typeid(node.AddOrModifyAttribute("test", "test")) == typeid(XMLBuilder::Node));
  ASSERT_TRUE(typeid(node << std::pair("test2", "test2")) == typeid(XMLBuilder::Node));
  ASSERT_TRUE(typeid(node << std::pair("test2", std::pair(12.34, 1))) == typeid(XMLBuilder::Node));
}

TEST(KeepType, ValueNode)
{
  XMLBuilder::ValueNode node("test", "test");
  ASSERT_TRUE(typeid(node.AddOrModifyAttribute("test1", "test1")) == typeid(XMLBuilder::ValueNode));
  ASSERT_TRUE(typeid(node << std::pair("test2", "test2")) == typeid(XMLBuilder::ValueNode));
  ASSERT_TRUE(typeid(node << std::pair("test2", std::pair(12.34, 5))) == typeid(XMLBuilder::ValueNode));
  ASSERT_TRUE(typeid(node = "test1") == typeid(XMLBuilder::ValueNode));
  ASSERT_TRUE(typeid(node = std::pair(12.34, 5)) == typeid(XMLBuilder::ValueNode));
}

TEST(KeepType, ParentNode)
{
  XMLBuilder::ParentNode node("test");
  ASSERT_TRUE(typeid(node.AddOrModifyAttribute("test1", "test1")) == typeid(XMLBuilder::ParentNode));
  ASSERT_TRUE(typeid(node << std::pair("test2", "test2")) == typeid(XMLBuilder::ParentNode));
  ASSERT_TRUE(typeid(node << std::pair("test2", std::pair(12.34, 5))) == typeid(XMLBuilder::ParentNode));
  ASSERT_TRUE(typeid(node.AddChild(XMLBuilder::Node("test1"))) == typeid(XMLBuilder::ParentNode));
}

TEST(KeepType, RootNode)
{
  XMLBuilder::RootNode node;
  ASSERT_TRUE(typeid(node.AddChild(XMLBuilder::Node("test1"))) == typeid(XMLBuilder::RootNode));
}
