//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

TEST(Other, GetNodeType)
{
    XMLBuilder::Node node1("test");
    XMLBuilder::ValueNode node2("test", "test");
    XMLBuilder::ParentNode node3("test");

    EXPECT_EQ(node1.Type(), XMLBuilder::NodeType::NT_NODE);
    EXPECT_EQ(node2.Type(), XMLBuilder::NodeType::NT_VALUE);
    EXPECT_EQ(node3.Type(), XMLBuilder::NodeType::NT_PARENT);
}
