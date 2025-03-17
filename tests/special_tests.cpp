#include "common.hpp"

XMLBuilder::RootNode testReturnRoot()
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

  return root;
}

TEST(Special, DataRetention)
{
  XMLBuilder::RootNode root = testReturnRoot();
  EXPECT_EQ(root.Generate(), std::format("{}<parent1 test1=\"123\" test2=\"parent\">\n\t<parent11 test=\"14.36\">\n\t\t<parent11Child1/>\n\t\t<parent11Child2 child2=\"ack\">14.2000</parent11Child2>\n\t</parent11>\n</parent1>\n<parent2 test1=\"parent2\" test2=\"120500\">\n\t<parent2Child1>hi</parent2Child1>\n\t<parent2Child2 test1=\"test\"/>\n</parent2>\n<test3 root=\"root\">14</test3>\n", DEFAULT_HEADER));
}

TEST(Special, FullRLTest)
{
  XMLBuilder::RootNode root;
  root.AddChild(XMLBuilder::ParentNode("dat:dataPack").AddAttribute("version", "1.0").AddAttribute("id", "1741957155-1").AddAttribute("application", "ATP").AddAttribute("programVersion", "2.0.0")
                .AddChild(XMLBuilder::ParentNode("dat:dataPackItem").AddAttribute("version", "2.0").AddAttribute("id", "23230971452/19/1")
                          .AddChild(XMLBuilder::ParentNode("bnk:bank").AddAttribute("version", "2.0")
                                    .AddChild(XMLBuilder::ParentNode("bnk:bankHeader")
                                              .AddChild(XMLBuilder::ValueNode("bnk:bankType", "receipt"))
                                              .AddChild(XMLBuilder::ParentNode("bnk:account")
                                                        .AddChild(XMLBuilder::ValueNode("typ:ids", "AM1")))
                                              .AddChild(XMLBuilder::ValueNode("bnk:symVar", "028-2095944-2421910"))
                                              .AddChild(XMLBuilder::ValueNode("bnk:dateStatement", "2024-11-05"))
                                              .AddChild(XMLBuilder::ValueNode("bnk:datePayment", "2024-11-03")))
                                    .AddChild(XMLBuilder::ParentNode("bnk:bankSummary")
                                              .AddChild(XMLBuilder::ParentNode("bnk:foreignCurrency")
                                                        .AddChild(XMLBuilder::ParentNode("typ:currency")
                                                                  .AddChild(XMLBuilder::ValueNode("typ:ids", "EUR")))
                                                        .AddChild(XMLBuilder::ValueNode("typ:amount", 1))
                                                        .AddChild(XMLBuilder::ValueNode("typ:priceSum", 74.13l, 2))))))
                .AddChild(XMLBuilder::ParentNode("dat:dataPackItem").AddAttribute("version", "2.0").AddAttribute("id", "23230971452/61/1")
                          .AddChild(XMLBuilder::ParentNode("bnk:bank").AddAttribute("version", "2.0")
                                    .AddChild(XMLBuilder::ParentNode("bnk:bankHeader")
                                              .AddChild(XMLBuilder::ValueNode("bnk:bankType", "receipt"))
                                              .AddChild(XMLBuilder::ParentNode("bnk:account")
                                                        .AddChild(XMLBuilder::ValueNode("typ:ids", "AM1")))
                                              .AddChild(XMLBuilder::ValueNode("bnk:symVar", "028-2549070-8518720"))
                                              .AddChild(XMLBuilder::ValueNode("bnk:dateStatement", "2024-11-05"))
                                              .AddChild(XMLBuilder::ValueNode("bnk:datePayment", "2024-11-03")))
                                    .AddChild(XMLBuilder::ParentNode("bnk:bankSummary")
                                              .AddChild(XMLBuilder::ParentNode("bnk:foreignCurrency")
                                                        .AddChild(XMLBuilder::ParentNode("typ:currency")
                                                                  .AddChild(XMLBuilder::ValueNode("typ:ids", "EUR")))
                                                        .AddChild(XMLBuilder::ValueNode("typ:amount", 1))
                                                        .AddChild(XMLBuilder::ValueNode("typ:priceSum", 186.31l, 2)))))));

  const std::string_view result =
"<?xml version=\"1.0\" encoding=\"Windows-1250\"?>\n\
<dat:dataPack application=\"ATP\" id=\"1741957155-1\" programVersion=\"2.0.0\" version=\"1.0\">\n\
\t<dat:dataPackItem id=\"23230971452/19/1\" version=\"2.0\">\n\
\t\t<bnk:bank version=\"2.0\">\n\
\t\t\t<bnk:bankHeader>\n\
\t\t\t\t<bnk:bankType>receipt</bnk:bankType>\n\
\t\t\t\t<bnk:account>\n\
\t\t\t\t\t<typ:ids>AM1</typ:ids>\n\
\t\t\t\t</bnk:account>\n\
\t\t\t\t<bnk:symVar>028-2095944-2421910</bnk:symVar>\n\
\t\t\t\t<bnk:dateStatement>2024-11-05</bnk:dateStatement>\n\
\t\t\t\t<bnk:datePayment>2024-11-03</bnk:datePayment>\n\
\t\t\t</bnk:bankHeader>\n\
\t\t\t<bnk:bankSummary>\n\
\t\t\t\t<bnk:foreignCurrency>\n\
\t\t\t\t\t<typ:currency>\n\
\t\t\t\t\t\t<typ:ids>EUR</typ:ids>\n\
\t\t\t\t\t</typ:currency>\n\
\t\t\t\t\t<typ:amount>1</typ:amount>\n\
\t\t\t\t\t<typ:priceSum>74.13</typ:priceSum>\n\
\t\t\t\t</bnk:foreignCurrency>\n\
\t\t\t</bnk:bankSummary>\n\
\t\t</bnk:bank>\n\
\t</dat:dataPackItem>\n\
\t<dat:dataPackItem id=\"23230971452/61/1\" version=\"2.0\">\n\
\t\t<bnk:bank version=\"2.0\">\n\
\t\t\t<bnk:bankHeader>\n\
\t\t\t\t<bnk:bankType>receipt</bnk:bankType>\n\
\t\t\t\t<bnk:account>\n\
\t\t\t\t\t<typ:ids>AM1</typ:ids>\n\
\t\t\t\t</bnk:account>\n\
\t\t\t\t<bnk:symVar>028-2549070-8518720</bnk:symVar>\n\
\t\t\t\t<bnk:dateStatement>2024-11-05</bnk:dateStatement>\n\
\t\t\t\t<bnk:datePayment>2024-11-03</bnk:datePayment>\n\
\t\t\t</bnk:bankHeader>\n\
\t\t\t<bnk:bankSummary>\n\
\t\t\t\t<bnk:foreignCurrency>\n\
\t\t\t\t\t<typ:currency>\n\
\t\t\t\t\t\t<typ:ids>EUR</typ:ids>\n\
\t\t\t\t\t</typ:currency>\n\
\t\t\t\t\t<typ:amount>1</typ:amount>\n\
\t\t\t\t\t<typ:priceSum>186.31</typ:priceSum>\n\
\t\t\t\t</bnk:foreignCurrency>\n\
\t\t\t</bnk:bankSummary>\n\
\t\t</bnk:bank>\n\
\t</dat:dataPackItem>\n\
</dat:dataPack>\n";

  EXPECT_EQ(root.Generate(), result);
}
