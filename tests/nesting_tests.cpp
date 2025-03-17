#include "common.hpp"

TEST(Nesting, SingleLayerOnRoot)
{
  XMLBuilder::RootNode root;
  root.AddChild(XMLBuilder::Node("test1").AddAttribute("testAttr1", 123).AddAttribute("testAttr2", "xyz")).AddChild(XMLBuilder::ValueNode("test2", "value2").AddAttribute("testAttr1", 12.52, 8).AddAttribute("testAttr2", 456));
  EXPECT_EQ(root.Generate(), std::format("{}<test1 testAttr1=\"123\" testAttr2=\"xyz\"/>\n<test2 testAttr1=\"12.52000000\" testAttr2=\"456\">value2</test2>\n", DEFAULT_HEADER));
}

TEST(Nesting, SingleLayerOnParent)
{
  XMLBuilder::ParentNode parent("parent");
  parent.AddChild(XMLBuilder::Node("test1").AddAttribute("testAttr1", 123).AddAttribute("testAttr2", "xyz")).AddChild(XMLBuilder::ValueNode("test2", "value2").AddAttribute("testAttr1", 12.52, 8).AddAttribute("testAttr2", 456));
  EXPECT_EQ(parent.Generate(), std::format("{}<parent>\n\t<test1 testAttr1=\"123\" testAttr2=\"xyz\"/>\n\t<test2 testAttr1=\"12.52000000\" testAttr2=\"456\">value2</test2>\n</parent>\n", DEFAULT_HEADER));
}

TEST(Nesting, Multilayer)
{
  XMLBuilder::RootNode root;

  XMLBuilder::ParentNode parent11("parent11");
  parent11.AddAttribute("test", 14.358f, 2);
  parent11.AddChild<XMLBuilder::Node>("parent11Child1").AddChild(XMLBuilder::ValueNode("parent11Child2", 14.2l, 4).AddAttribute("child2", "ack"));

  XMLBuilder::ParentNode parent1("parent1");
  parent1.AddAttribute("test1", 123).AddAttribute("test2", "parent");
  parent1.AddChild(parent11);

  XMLBuilder::ParentNode parent2("parent2");
  parent2.AddAttribute("test1", "parent2").AddAttribute("test2", static_cast<uint32_t>(120500));
  parent2.AddChild<XMLBuilder::ValueNode>({"parent2Child1", "hi"}).AddChild(XMLBuilder::Node("parent2Child2").AddAttribute("test1", "test"));

  root.AddChild(parent1).AddChild(parent2).AddChild(XMLBuilder::ValueNode("test3", 14).AddAttribute("root", "root"));

  EXPECT_EQ(root.Generate(), std::format("{}<parent1 test1=\"123\" test2=\"parent\">\n\t<parent11 test=\"14.36\">\n\t\t<parent11Child1/>\n\t\t<parent11Child2 child2=\"ack\">14.2000</parent11Child2>\n\t</parent11>\n</parent1>\n<parent2 test1=\"parent2\" test2=\"120500\">\n\t<parent2Child1>hi</parent2Child1>\n\t<parent2Child2 test1=\"test\"/>\n</parent2>\n<test3 root=\"root\">14</test3>\n", DEFAULT_HEADER));
}

TEST(Nesting, ChildCount)
{
  XMLBuilder::RootNode root;

  XMLBuilder::ParentNode parent11("parent11");
  parent11.AddAttribute("test", 14.358f, 2);
  parent11.AddChild<XMLBuilder::Node>("parent11Child1").AddChild(XMLBuilder::ValueNode("parent11Child2", 14.2l, 4).AddAttribute("child2", "ack"));

  XMLBuilder::ParentNode parent1("parent1");
  parent1.AddAttribute("test1", 123).AddAttribute("test2", "parent");
  parent1.AddChild(parent11);

  XMLBuilder::ParentNode parent2("parent2");
  parent2.AddAttribute("test1", "parent2").AddAttribute("test2", static_cast<uint32_t>(120500));
  parent2.AddChild<XMLBuilder::ValueNode>({"parent2Child1", "hi"}).AddChild(XMLBuilder::Node("parent2Child2").AddAttribute("test1", "test"));

  root.AddChild(parent1).AddChild(parent2).AddChild(XMLBuilder::ValueNode("test3", 14).AddAttribute("root", "root"));

  EXPECT_EQ(root.ChildrenCount(), 3);
  EXPECT_EQ(parent1.ChildrenCount(), 1);
  EXPECT_EQ(parent2.ChildrenCount(), 2);
  EXPECT_EQ(parent11.ChildrenCount(), 2);
}

TEST(Nesting, RemoveChild)
{
  XMLBuilder::RootNode root;

  XMLBuilder::ParentNode parent11("parent11");
  parent11.AddAttribute("test", 14.358f, 2);
  parent11.AddChild<XMLBuilder::Node>("parent11Child1").AddChild(XMLBuilder::ValueNode("parent11Child2", 14.2l, 4).AddAttribute("child2", "ack"));
  parent11.RemoveChild(0);

  XMLBuilder::ParentNode parent1("parent1");
  parent1.AddAttribute("test1", 123).AddAttribute("test2", "parent");
  parent1.AddChild(parent11);

  XMLBuilder::ParentNode parent2("parent2");
  parent2.AddAttribute("test1", "parent2").AddAttribute("test2", static_cast<uint32_t>(120500));
  parent2.AddChild<XMLBuilder::ValueNode>({"parent2Child1", "hi"}).AddChild(XMLBuilder::Node("parent2Child2").AddAttribute("test1", "test"));

  root.AddChild(parent1).AddChild(parent2).AddChild(XMLBuilder::ValueNode("test3", 14).AddAttribute("root", "root"));
  root.RemoveChild(1);

  root.childAt<XMLBuilder::ParentNode>(0).childAt<XMLBuilder::ParentNode>(0).RemoveChild(0);

  EXPECT_EQ(root.Generate(), std::format("{}<parent1 test1=\"123\" test2=\"parent\">\n\t<parent11 test=\"14.36\"/>\n</parent1>\n<test3 root=\"root\">14</test3>\n", DEFAULT_HEADER));
}
