#include "common.hpp"

#include <string>

using namespace std::string_view_literals;

TEST(Generate, ByGenerate)
{
  XMLBuilder::RootNode rootNode;
  EXPECT_EQ(rootNode.Generate(), DEFAULT_HEADER);
}

TEST(Generate, ByString)
{
  XMLBuilder::RootNode rootNode;
  EXPECT_EQ(std::string(rootNode), DEFAULT_HEADER);
}

TEST(Generate, ByPrint)
{
  std::ostringstream stream;
  XMLBuilder::RootNode rootNode;
  rootNode.Print(stream);

  EXPECT_EQ(stream.str(), DEFAULT_HEADER);
}

TEST(Generate, ByPrintOperator)
{
  std::ostringstream stream;
  XMLBuilder::RootNode rootNode;
  stream << rootNode;

  EXPECT_EQ(stream.str(), DEFAULT_HEADER);
}

TEST(Generate, CustomHeader)
{
  XMLBuilder::RootNode rootNode;
  EXPECT_EQ(rootNode.Generate("2.0", "random-encoding"), std::format(HEADER_FORMAT, "2.0", "random-encoding"));
}

TEST(Creation, NodeCharArrayTag)
{
  XMLBuilder::Node node1("test1");

  char name2Arr[] = "test2";
  char* name2 = name2Arr;
  XMLBuilder::Node node2(name2);

  const char* name3 = "test3";
  XMLBuilder::Node node3(name3);

  char name4[] = "test4";
  XMLBuilder::Node node4(name4);

  const char name5[] = "test5";
  XMLBuilder::Node node5(name5);

  const std::string name6 = "test6";
  XMLBuilder::Node node6(name6.c_str());

  EXPECT_EQ(node1.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test1/>"));
  EXPECT_EQ(node2.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test2/>"));
  EXPECT_EQ(node3.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test3/>"));
  EXPECT_EQ(node4.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test4/>"));
  EXPECT_EQ(node5.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test5/>"));
  EXPECT_EQ(node6.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test6/>"));
}

TEST(Creation, NodeStringTag)
{
  std::string name1 = "test1";
  XMLBuilder::Node node1(name1);

  const std::string name2 = "test2";
  XMLBuilder::Node node2(name2);

  EXPECT_EQ(node1.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test1/>"));
  EXPECT_EQ(node2.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test2/>"));
}

TEST(Creation, NodeStringViewTag)
{
  XMLBuilder::Node node1("test1"sv);

  std::string_view name2 = "test2"sv;
  XMLBuilder::Node node2(name2);

  const std::string_view name3 = "test3"sv;
  XMLBuilder::Node node3(name3);

  EXPECT_EQ(node1.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test1/>"));
  EXPECT_EQ(node2.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test2/>"));
  EXPECT_EQ(node3.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test3/>"));
}

TEST(Creation, ParentNodeNoChildren)
{
  XMLBuilder::ParentNode node("test");
  EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test/>"));
}

TEST(Creation, ValueNode)
{
  XMLBuilder::ValueNode node("test", "testValue");
  EXPECT_EQ(node.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test>testValue</test>"));
}

TEST(Creation, CatchEmptyTag)
{
  EXPECT_THROW(XMLBuilder::Node(""), std::invalid_argument);
}

TEST(Creation, CatchValueNodeEmptyValue)
{
  EXPECT_THROW(XMLBuilder::ValueNode node("test", ""), std::invalid_argument);
}

TEST(Utils, ReturnCheckTypes)
{
  XMLBuilder::Node node1("test1");
  XMLBuilder::ValueNode node2("test2", "test2");
  XMLBuilder::ParentNode node3("test3");

  EXPECT_EQ(node1.Type(), XMLBuilder::types::NodeTypes::NT_NODE);
  EXPECT_EQ(node2.Type(), XMLBuilder::types::NodeTypes::NT_VALUE);
  EXPECT_EQ(node3.Type(), XMLBuilder::types::NodeTypes::NT_PARENT);

  XMLBuilder::meta::NodeBase* nodePtr = nullptr;

  nodePtr = &node1;
  EXPECT_EQ(nodePtr->Type(), XMLBuilder::types::NodeTypes::NT_NODE);

  nodePtr = &node2;
  EXPECT_EQ(nodePtr->Type(), XMLBuilder::types::NodeTypes::NT_VALUE);

  nodePtr = &node3;
  EXPECT_EQ(nodePtr->Type(), XMLBuilder::types::NodeTypes::NT_PARENT);
}
