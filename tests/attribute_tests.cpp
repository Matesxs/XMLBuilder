#include "common.hpp"

#include <string>
#include <cstdint>
#include <cmath>

using namespace std::string_view_literals;

TEST(Attributes, charArrayKey)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", "value1");

  char attKey2Arr[] = "testAtt2";
  char* attKey2 = attKey2Arr;
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute(attKey2, "value2");

  const char* attKey3 = "testAtt3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute(attKey3, "value3");

  char attKey4[] = "testAtt4";
  XMLBuilder::Node node4 = XMLBuilder::Node("test4").AddAttribute(attKey4, "value4");

  const char attKey5[] = "testAtt5";
  XMLBuilder::Node node5 = XMLBuilder::Node("test5").AddAttribute(attKey5, "value5");

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
  EXPECT_EQ(node4.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 4, 4, 4));
  EXPECT_EQ(node5.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 5, 5, 5));
}

TEST(Attributes, stringKey)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute(std::string("testAtt1"), "value1");

  std::string attKey2 = "testAtt2";
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute(attKey2, "value2");

  const std::string attKey3 = "testAtt3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute(attKey3, "value3");

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, stringViewKey)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1"sv, "value1");

  std::string_view attKey2 = "testAtt2";
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute(attKey2, "value2");

  const std::string_view attKey3 = "testAtt3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute(attKey3, "value3");

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, charArrayValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", "value1");

  char value2Arr[] = "value2";
  char* value2 = value2Arr;
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", value2);

  const char* value3 = "value3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", value3);

  char value4[] = "value4";
  XMLBuilder::Node node4 = XMLBuilder::Node("test4").AddAttribute("testAtt4", value4);

  const char value5[] = "value5";
  XMLBuilder::Node node5 = XMLBuilder::Node("test5").AddAttribute("testAtt5", value5);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
  EXPECT_EQ(node4.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 4, 4, 4));
  EXPECT_EQ(node5.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 5, 5, 5));
}

TEST(Attributes, stringValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", std::string("value1"));

  std::string value2 = "value2";
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", value2);

  const std::string value3 = "value3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", value3);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, stringViewValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", "value1"sv);

  std::string_view value2 = "value2"sv;
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", value2);

  const std::string_view value3 = "value3"sv;
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", value3);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, BoolValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", true);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", false);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, "true"));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, "false"));
}

TEST(Attributes, ShortValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", static_cast<short>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", static_cast<short>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", static_cast<unsigned short>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, IntValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", static_cast<int>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", static_cast<int>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", static_cast<unsigned int>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, LongValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", static_cast<long>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", static_cast<long>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", static_cast<unsigned long>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, LongLongValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", static_cast<long long>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", static_cast<long long>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", static_cast<unsigned long long>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, int8Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", static_cast<int8_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", static_cast<int8_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", static_cast<uint8_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, int16Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", static_cast<int16_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", static_cast<int16_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", static_cast<uint16_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, int32Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", static_cast<int32_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", static_cast<int32_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", static_cast<uint32_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, int64Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", static_cast<int64_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", static_cast<int64_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", static_cast<uint64_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, floatValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.456789f);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.456789f);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nanf("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, doubleValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.456789);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.456789);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nan("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, longDoubleValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.456789l);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.456789l);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nanl("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, floatValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.456789f, 2);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.456789f, 2);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nanf("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, doubleValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.456789, 2);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.456789, 2);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nan("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, longDoubleValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.456789l, 2);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.456789l, 2);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nanl("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, floatValueLimitExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.45f, 8);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.45f, 8);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nanf("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, doubleValueLimitExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.45, 8);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.45, 8);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nan("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, longDoubleValueLimitExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddAttribute("testAtt1", 123.45l, 8);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAtt2", -123.45l, 8);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddAttribute("testAtt3", std::nanl("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, CatchEmptyAttributeKey)
{
  EXPECT_THROW(XMLBuilder::Node("test").AddAttribute("", "test"), std::invalid_argument);
}

TEST(Attributes, MultipleStringValues)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddAttribute("test1", "value1").AddAttribute("test2", "value2"sv).AddAttribute("test3", std::string("value3"));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"value1\" test2=\"value2\" test3=\"value3\"/>\n", DEFAULT_HEADER));
}

TEST(Attributes, MultipleWholeNumberValues)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddAttribute("test1"sv, static_cast<uint8_t>(123)).AddAttribute(std::string("test2"), static_cast<unsigned long long>(456)).AddAttribute("test3", static_cast<int32_t>(-789));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test3=\"{}\"/>\n", DEFAULT_HEADER, static_cast<uint8_t>(123), static_cast<unsigned long long>(456), static_cast<int32_t>(-789)));
}

TEST(Attributes, MultipleFloatingpointNumberValues)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddAttribute("test1"sv, 123.456f).AddAttribute(std::string("test2"), 92.2).AddAttribute("test3", 1455.48765788l);
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test3=\"{}\"/>\n", DEFAULT_HEADER, 123.456f, 92.2, 1455.48765788l));
}

TEST(Attributes, ValueTypeMix)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddAttribute("test1"sv, "123").AddAttribute(std::string("test2"), 92.2).AddAttribute("test3", static_cast<int8_t>(-8)).AddAttribute("test4", 32.448888l, 3).AddAttribute("test5"sv, static_cast<uint64_t>(1850000000));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test3=\"{}\" test4=\"{}\" test5=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, -8, 32.449, 1850000000));
}

TEST(Attributes, CatchEmptyAttributeKeyMultiple)
{
  EXPECT_THROW(XMLBuilder::Node("test").AddAttribute("test1", static_cast<uint16_t>(123)).AddAttribute("test2", 123.4).AddAttribute("test3", "test").AddAttribute("test4", 1234.567f).AddAttribute("", "test"), std::invalid_argument);
}

TEST(Attributes, NotOverwriteExistingAttribute)
{
  XMLBuilder::Node node("test");
  node.AddAttribute("testAttr", 123).AddAttribute("testAttr", 456);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"123\"/>\n", DEFAULT_HEADER));
}

TEST(Attributes, ContainsAttribute)
{
  XMLBuilder::Node node("test");
  node.AddAttribute("testAttr", 123);

  EXPECT_TRUE(node.ContainsAttribute("testAttr"));
  EXPECT_FALSE(node.ContainsAttribute("testAttr1"));
  EXPECT_FALSE(node.ContainsAttribute(""));
}

TEST(Attributes, ModifyAttributeString)
{
  XMLBuilder::Node node("test");
  node.AddAttribute("testAttr", 123);

  node.ModifyAttribute("testAttr", "test1");
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, "test1"));

  char value2Arr[] = "test2";
  char* value2 = value2Arr;
  node.ModifyAttribute("testAttr", value2);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value2));

  const char* value3 = "test3";
  node.ModifyAttribute("testAttr", value3);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value3));

  node.ModifyAttribute("testAttr", "test4"sv);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, "test4"));

  std::string_view value5 = "test5";
  node.ModifyAttribute("testAttr", value5);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value5));

  const std::string_view value6 = "test6";
  node.ModifyAttribute("testAttr", value6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value6));

  std::string value7 = "test7";
  node.ModifyAttribute("testAttr", value7);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value7));

  const std::string_view value8 = "test8";
  node.ModifyAttribute("testAttr", value8);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value8));
}

TEST(Attributes, ModifyAttributeWholeNumber)
{
  XMLBuilder::Node node("test");
  node.AddAttribute("testAttr", 123);

  node.ModifyAttribute("testAttr", 456);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 456));

  node.ModifyAttribute("testAttr", static_cast<short>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));

  node.ModifyAttribute("testAttr", static_cast<long>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123));

  node.ModifyAttribute("testAttr", static_cast<long long>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));

  node.ModifyAttribute("testAttr", static_cast<int8_t>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123));

  node.ModifyAttribute("testAttr", static_cast<int16_t>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));

  node.ModifyAttribute("testAttr", static_cast<int32_t>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123));

  node.ModifyAttribute("testAttr", static_cast<int64_t>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));
}

TEST(Attributes, ModifyAttributeFloating)
{
  XMLBuilder::Node node("test");
  node.AddAttribute("testAttr", 123);

  node.ModifyAttribute("testAttr", 123.123f);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123.123f));

  node.ModifyAttribute("testAttr", -123.123);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123.123));

  node.ModifyAttribute("testAttr", 123.123l);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123.123l));

  node.ModifyAttribute("testAttr", -123.123f, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, -123.123f));

  node.ModifyAttribute("testAttr", 123.123, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, 123.123));

  node.ModifyAttribute("testAttr", -123.123l, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, -123.123l));

  node.ModifyAttribute("testAttr", 123.123f, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, 123.123f));

  node.ModifyAttribute("testAttr", -123.123, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, -123.123));

  node.ModifyAttribute("testAttr", 123.123l, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, 123.123l));
}

TEST(Attributes, ModifyNonExistent)
{
  XMLBuilder::Node node("test");
  node.AddAttribute("testAttr", 123);

  EXPECT_FALSE(node.ModifyAttribute("test", "test"));
  EXPECT_FALSE(node.ModifyAttribute("", "test"));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));
}

TEST(Attributes, RemoveAttribute)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddAttribute("test1"sv, "123").AddAttribute(std::string("test2"), 92.2).AddAttribute("test3", static_cast<int8_t>(-8)).AddAttribute("test4", 32.448888l, 3).AddAttribute("test5"sv, static_cast<uint64_t>(1850000000));

  node.RemoveAttribute("test3");
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test4=\"{}\" test5=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, 32.449, 1850000000));

  node.RemoveAttribute("test5");
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test4=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, 32.449));

  EXPECT_FALSE(node.RemoveAttribute("test"));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test4=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, 32.449));

  EXPECT_FALSE(node.RemoveAttribute(""));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test4=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, 32.449));
}

TEST(Attributes, GetByOperator)
{
  XMLBuilder::Node node("test");
  node.AddAttribute("testAttr", 123);

  const XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAttr2", 1234);

  EXPECT_EQ(node["testAttr"], "123");
  EXPECT_EQ(node2["testAttr2"], "1234");

  EXPECT_THROW(node["testAttr1"], std::out_of_range);
  EXPECT_THROW(node[""], std::invalid_argument);
}

TEST(Attributes, ModifyByOperator)
{
  XMLBuilder::Node node("test");
  node.AddAttribute("testAttr", 123);

  const XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddAttribute("testAttr2", 1234);

  node["testAttr"] = "456";
  node2["testAttr2"] = "4567"; // Dont overwrite because its const node

  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"456\"/>\n", DEFAULT_HEADER));
  EXPECT_EQ(node2.Generate(), std::format("{}<test2 testAttr2=\"1234\"/>\n", DEFAULT_HEADER));
}