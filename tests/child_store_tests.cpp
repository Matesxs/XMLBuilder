//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

TEST(ChildStore, AddChildren)
{
    XMLBuilder::RootNode root;
    EXPECT_NO_THROW(root.AddChild<XMLBuilder::Node>("child1"));
    EXPECT_NO_THROW(root.AddChild<XMLBuilder::ValueNode>({"child2", "value2"}));
    EXPECT_NO_THROW(root.AddChild(XMLBuilder::ParentNode("child3")));
}

TEST(ChildStore, AddChildrenChaining)
{
    XMLBuilder::RootNode root;
    EXPECT_NO_THROW(root.AddChild<XMLBuilder::Node>("child1").AddChild<XMLBuilder::ValueNode>({"child2", "value2"}).AddChild(XMLBuilder::ParentNode("child3")));
}

TEST(ChildStore, ChildCount)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    XMLBuilder::RootNode root2;
    EXPECT_NO_THROW(root2.AddChild<XMLBuilder::Node>("child1").AddChild<XMLBuilder::ValueNode>({"child2", "value2"}).AddChild(XMLBuilder::ParentNode("child3")));

    EXPECT_EQ(root1.ChildrenCount(), 3);
    EXPECT_EQ(root2.ChildrenCount(), 3);
}

TEST(ChildStore, RemoveChild)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    EXPECT_TRUE(root1.RemoveChild(1));
    EXPECT_TRUE(root1.RemoveChild(0));
    EXPECT_EQ(root1.ChildrenCount(), 1);
}

TEST(ChildStore, RemoveChildrenInvalidIndex)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    EXPECT_FALSE(root1.RemoveChild(3));
    EXPECT_EQ(root1.ChildrenCount(), 3);
}

TEST(ChildStore, GetChildByMethodInBaseType)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    const XMLBuilder::RootNode root2 = XMLBuilder::RootNode().AddChild<XMLBuilder::Node>("child1").AddChild<XMLBuilder::ValueNode>({"child2", "value2"}).AddChild(XMLBuilder::ParentNode("child3"));

    EXPECT_NO_THROW(root1.ChildAt(0));
    EXPECT_NO_THROW(root1.ChildAt(1));
    EXPECT_NO_THROW(root1.ChildAt(2));

    EXPECT_NO_THROW(root2.ChildAt(0));
    EXPECT_NO_THROW(root2.ChildAt(1));
    EXPECT_NO_THROW(root2.ChildAt(2));
}

TEST(ChildStore, GetChildByMethodInParentType)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    const XMLBuilder::RootNode root2 = XMLBuilder::RootNode().AddChild<XMLBuilder::Node>("child1").AddChild<XMLBuilder::ValueNode>({"child2", "value2"}).AddChild(XMLBuilder::ParentNode("child3"));

    EXPECT_NO_THROW(root1.ChildAt<XMLBuilder::Node>(0));
    EXPECT_NO_THROW(root1.ChildAt<XMLBuilder::ValueNode>(1));
    EXPECT_NO_THROW(root1.ChildAt<XMLBuilder::ParentNode>(2));

    EXPECT_NO_THROW(root2.ChildAt<XMLBuilder::Node>(0));
    EXPECT_NO_THROW(root2.ChildAt<XMLBuilder::ValueNode>(1));
    EXPECT_NO_THROW(root2.ChildAt<XMLBuilder::ParentNode>(2));
}

TEST(ChildStore, GetChildByMethodInInvalidParentType)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    const XMLBuilder::RootNode root2 = XMLBuilder::RootNode().AddChild<XMLBuilder::Node>("child1").AddChild<XMLBuilder::ValueNode>({"child2", "value2"}).AddChild(XMLBuilder::ParentNode("child3"));

    EXPECT_THROW(root1.ChildAt<XMLBuilder::ValueNode>(0), std::invalid_argument);
    EXPECT_THROW(root1.ChildAt<XMLBuilder::ParentNode>(1), std::invalid_argument);
    EXPECT_THROW(root1.ChildAt<XMLBuilder::Node>(2), std::invalid_argument);

    EXPECT_THROW(root2.ChildAt<XMLBuilder::ValueNode>(0), std::invalid_argument);
    EXPECT_THROW(root2.ChildAt<XMLBuilder::ParentNode>(1), std::invalid_argument);
    EXPECT_THROW(root2.ChildAt<XMLBuilder::Node>(2), std::invalid_argument);
}

TEST(ChildStore, GetChildByMethodInvalidIndex)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    const XMLBuilder::RootNode root2 = XMLBuilder::RootNode().AddChild<XMLBuilder::Node>("child1").AddChild<XMLBuilder::ValueNode>({"child2", "value2"}).AddChild(XMLBuilder::ParentNode("child3"));

    EXPECT_THROW(root1.ChildAt(4), std::out_of_range);
    EXPECT_THROW(root2.ChildAt(4), std::out_of_range);
}

TEST(ChildStore, GetChildByOperator)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    const XMLBuilder::RootNode root2 = XMLBuilder::RootNode().AddChild<XMLBuilder::Node>("child1").AddChild<XMLBuilder::ValueNode>({"child2", "value2"}).AddChild(XMLBuilder::ParentNode("child3"));

    EXPECT_NO_THROW(root1[0]);
    EXPECT_NO_THROW(root1[1]);
    EXPECT_NO_THROW(root1[2]);

    EXPECT_NO_THROW(root2[0]);
    EXPECT_NO_THROW(root2[1]);
    EXPECT_NO_THROW(root2[2]);
}

TEST(ChildStore, GetChildByOperatorInvalidIndex)
{
    XMLBuilder::RootNode root1;
    root1.AddChild<XMLBuilder::Node>("child1");
    root1.AddChild<XMLBuilder::ValueNode>({"child2", "value2"});
    root1.AddChild(XMLBuilder::ParentNode("child3"));

    const XMLBuilder::RootNode root2 = XMLBuilder::RootNode().AddChild<XMLBuilder::Node>("child1").AddChild<XMLBuilder::ValueNode>({"child2", "value2"}).AddChild(XMLBuilder::ParentNode("child3"));

    EXPECT_THROW(root1[4], std::out_of_range);
    EXPECT_THROW(root2[4], std::out_of_range);
}

TEST(ChildStore, Iterator)
{
    const std::vector testTypes = { XMLBuilder::NodeType::NT_NODE, XMLBuilder::NodeType::NT_VALUE, XMLBuilder::NodeType::NT_PARENT };

    XMLBuilder::RootNode root1;
    root1.AddChild(XMLBuilder::Node("test1")).AddChild(XMLBuilder::ValueNode("test2", 123.4)).AddChild(XMLBuilder::ParentNode("test3"));
    const XMLBuilder::RootNode root2 = XMLBuilder::RootNode().AddChild(XMLBuilder::Node("test1")).AddChild(XMLBuilder::ValueNode("test2", 123.4)).AddChild(XMLBuilder::ParentNode("test3"));

    size_t count = 0;
    for (auto& child : root1)
    {
        EXPECT_EQ(child->Type(), testTypes.at(count));
        count++;
    }
    EXPECT_EQ(count, 3);

    for (auto& child : std::vector(root1.rbegin(), root1.rend()))
    {
        count--;
        EXPECT_EQ(child->Type(), testTypes.at(count));
    }
    EXPECT_EQ(count, 0);

    count = 0;
    for (auto& child : root2)
    {
        EXPECT_EQ(child->Type(), testTypes.at(count));
        count++;
    }
    EXPECT_EQ(count, 3);

    for (auto& child : std::vector(root2.rbegin(), root2.rend()))
    {
        count--;
        EXPECT_EQ(child->Type(), testTypes.at(count));
    }
    EXPECT_EQ(count, 0);
}
