//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

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

TEST(Generate, WithChild)
{
    XMLBuilder::RootNode rootNode;
    rootNode.AddChild(XMLBuilder::Node("test"));
    EXPECT_EQ(rootNode.Generate(), std::format("{}{}\n", DEFAULT_HEADER, "<test/>"));
}

TEST(Generate, ConstNode)
{
    const XMLBuilder::RootNode rootNode;
    EXPECT_EQ(rootNode.Generate(), DEFAULT_HEADER);
}
