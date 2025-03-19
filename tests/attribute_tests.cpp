#include "common.hpp"

#include <string>
#include <cstdint>
#include <cmath>

using namespace std::string_view_literals;

TEST(Attributes, AddByCharArrayKey)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", "value1");

  char attKey2Arr[] = "testAtt2";
  char* attKey2 = attKey2Arr;
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute(attKey2, "value2");

  const char* attKey3 = "testAtt3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute(attKey3, "value3");

  char attKey4[] = "testAtt4";
  XMLBuilder::Node node4 = XMLBuilder::Node("test4").AddOrModifyAttribute(attKey4, "value4");

  const char attKey5[] = "testAtt5";
  XMLBuilder::Node node5 = XMLBuilder::Node("test5").AddOrModifyAttribute(attKey5, "value5");

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
  EXPECT_EQ(node4.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 4, 4, 4));
  EXPECT_EQ(node5.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 5, 5, 5));
}

TEST(Attributes, AddByStringKey)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute(std::string("testAtt1"), "value1");

  std::string attKey2 = "testAtt2";
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute(attKey2, "value2");

  const std::string attKey3 = "testAtt3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute(attKey3, "value3");

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, AddByStringViewKey)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1"sv, "value1");

  std::string_view attKey2 = "testAtt2";
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute(attKey2, "value2");

  const std::string_view attKey3 = "testAtt3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute(attKey3, "value3");

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, AddCharArrayValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", "value1");

  char value2Arr[] = "value2";
  char* value2 = value2Arr;
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", value2);

  const char* value3 = "value3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", value3);

  char value4[] = "value4";
  XMLBuilder::Node node4 = XMLBuilder::Node("test4").AddOrModifyAttribute("testAtt4", value4);

  const char value5[] = "value5";
  XMLBuilder::Node node5 = XMLBuilder::Node("test5").AddOrModifyAttribute("testAtt5", value5);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
  EXPECT_EQ(node4.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 4, 4, 4));
  EXPECT_EQ(node5.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 5, 5, 5));
}

TEST(Attributes, AddStringValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", std::string("value1"));

  std::string value2 = "value2";
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", value2);

  const std::string value3 = "value3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", value3);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, AddStringViewValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", "value1"sv);

  std::string_view value2 = "value2"sv;
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", value2);

  const std::string_view value3 = "value3"sv;
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", value3);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, AddByOperatorCharArrayValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1");
  node1 << std::pair{"testAtt1", "value1"};

  char value2Arr[] = "value2";
  char* value2 = value2Arr;
  XMLBuilder::Node node2 = XMLBuilder::Node("test2");
  node2 << std::pair{"testAtt2", value2};

  const char* value3 = "value3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3");
  node3 << std::pair{"testAtt3", value3};

  char value4[] = "value4";
  XMLBuilder::Node node4 = XMLBuilder::Node("test4");
  node4 << std::pair{"testAtt4", value4};

  const char value5[] = "value5";
  XMLBuilder::Node node5 = XMLBuilder::Node("test5");
  node5 << std::pair{"testAtt5", value5};

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
  EXPECT_EQ(node4.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 4, 4, 4));
  EXPECT_EQ(node5.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 5, 5, 5));
}

TEST(Attributes, AddByOperatorStringValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1");
  node1 << std::pair{"testAtt1", std::string("value1")};

  std::string value2 = "value2";
  XMLBuilder::Node node2 = XMLBuilder::Node("test2");
  node2 << std::pair{"testAtt2", value2};

  const std::string value3 = "value3";
  XMLBuilder::Node node3 = XMLBuilder::Node("test3");
  node3 << std::pair{"testAtt3", value3};

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, AddByOperatorStringViewValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1");
  node1 << std::pair{"testAtt1", "value1"sv};

  std::string_view value2 = "value2"sv;
  XMLBuilder::Node node2 = XMLBuilder::Node("test2");
  node2 << std::pair{"testAtt2", value2};

  const std::string_view value3 = "value3"sv;
  XMLBuilder::Node node3 = XMLBuilder::Node("test3");
  node3 << std::pair{"testAtt3", value3};

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"value{}\"/>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(Attributes, AddBoolValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", true);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", false);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, "true"));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, "false"));
}

TEST(Attributes, AddShortValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", static_cast<short>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", static_cast<short>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", static_cast<unsigned short>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddIntValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", static_cast<int>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", static_cast<int>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", static_cast<unsigned int>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddLongValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", static_cast<long>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", static_cast<long>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", static_cast<unsigned long>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddLongLongValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", static_cast<long long>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", static_cast<long long>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", static_cast<unsigned long long>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddInt8Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", static_cast<int8_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", static_cast<int8_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", static_cast<uint8_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddInt16Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", static_cast<int16_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", static_cast<int16_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", static_cast<uint16_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddInt32Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", static_cast<int32_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", static_cast<int32_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", static_cast<uint32_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddInt64Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", static_cast<int64_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", static_cast<int64_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", static_cast<uint64_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddByOperatorBoolValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", true);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", false);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, "true"));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, "false"));
}

TEST(Attributes, AddByOperatorShortValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", static_cast<short>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", static_cast<short>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", static_cast<unsigned short>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddByOperatorIntValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", static_cast<int>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", static_cast<int>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", static_cast<unsigned int>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddByOperatorLongValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", static_cast<long>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", static_cast<long>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", static_cast<unsigned long>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddByOperatorLongLongValue)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", static_cast<long long>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", static_cast<long long>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", static_cast<unsigned long long>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddByOperatorInt8Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", static_cast<int8_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", static_cast<int8_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", static_cast<uint8_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddByOperatorInt16Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", static_cast<int16_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", static_cast<int16_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", static_cast<uint16_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddByOperatorInt32Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", static_cast<int32_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", static_cast<int32_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", static_cast<uint32_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddByOperatorInt64Value)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", static_cast<int64_t>(123));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", static_cast<int64_t>(-123));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", static_cast<uint64_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, 123));
}

TEST(Attributes, AddFloatValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.456789f);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.456789f);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nanf("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddDoubleValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.456789);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.456789);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nan("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddLongDoubleValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.456789l);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.456789l);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nanl("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddFloatValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.456789f, 2);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.456789f, 2);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nanf("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddDoubleValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.456789, 2);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.456789, 2);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nan("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddLongDoubleValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.456789l, 2);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.456789l, 2);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nanl("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddFloatValueExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.45f, 8);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.45f, 8);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nanf("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddDoubleValueExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.45, 8);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.45, 8);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nan("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddLongDoubleValueExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1").AddOrModifyAttribute("testAtt1", 123.45l, 8);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAtt2", -123.45l, 8);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3").AddOrModifyAttribute("testAtt3", std::nanl("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorFloatValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", 123.456789f);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", -123.456789f);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::nanf("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorDoubleValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", 123.456789);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", -123.456789);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::nan("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorLongDoubleValueRaw)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", 123.456789l);
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", -123.456789l);
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::nanl("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorFloatValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", std::pair(123.456789f, 2));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", std::pair(-123.456789f, 2));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::pair(std::nanf("1"), 2));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorDoubleValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", std::pair(123.456789, 2));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", std::pair(-123.456789, 2));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::pair(std::nan("1"), 2));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorLongDoubleValueLimitPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", std::pair(123.456789l, 2));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", std::pair(-123.456789l, 2));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::pair(std::nanl("1"), 2));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.456789l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.2f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.456789l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorFloatValueExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", std::pair(123.45f, 8));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", std::pair(-123.45f, 8));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::pair(std::nanf("1"), 8));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45f));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45f));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorDoubleValueExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", std::pair(123.45, 8));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", std::pair(-123.45, 8));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::pair(std::nan("1"), 8));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, AddByOperatorLongDoubleValueExtendPrecision)
{
  XMLBuilder::Node node1 = XMLBuilder::Node("test1") << std::pair("testAtt1", std::pair(123.45l, 8));
  XMLBuilder::Node node2 = XMLBuilder::Node("test2") << std::pair("testAtt2", std::pair(-123.45l, 8));
  XMLBuilder::Node node3 = XMLBuilder::Node("test3") << std::pair("testAtt3", std::pair(std::nanl("1"), 8));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 1, 1, 123.45l));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{} testAtt{}=\"{:.8f}\"/>\n", DEFAULT_HEADER, 2, 2, -123.45l));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{} testAtt{}=\"{}\"/>\n", DEFAULT_HEADER, 3, 3, "nan"));
}

TEST(Attributes, CatchEmptyKey)
{
  EXPECT_THROW(XMLBuilder::Node("test").AddOrModifyAttribute("", "test"), std::invalid_argument);
}

TEST(Attributes, MultipleStringValues)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddOrModifyAttribute("test1", "value1").AddOrModifyAttribute("test2", "value2"sv).AddOrModifyAttribute("test3", std::string("value3"));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"value1\" test2=\"value2\" test3=\"value3\"/>\n", DEFAULT_HEADER));
}

TEST(Attributes, MultipleWholeNumberValues)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddOrModifyAttribute("test1"sv, static_cast<uint8_t>(123)).AddOrModifyAttribute(std::string("test2"), static_cast<unsigned long long>(456)).AddOrModifyAttribute("test3", static_cast<int32_t>(-789));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test3=\"{}\"/>\n", DEFAULT_HEADER, static_cast<uint8_t>(123), static_cast<unsigned long long>(456), static_cast<int32_t>(-789)));
}

TEST(Attributes, MultipleFloatingpointNumberValues)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddOrModifyAttribute("test1"sv, 123.456f).AddOrModifyAttribute(std::string("test2"), 92.2).AddOrModifyAttribute("test3", 1455.48765788l);
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test3=\"{}\"/>\n", DEFAULT_HEADER, 123.456f, 92.2, 1455.48765788l));
}

TEST(Attributes, ValueTypeMix)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddOrModifyAttribute("test1"sv, "123").AddOrModifyAttribute(std::string("test2"), 92.2).AddOrModifyAttribute("test3", static_cast<int8_t>(-8)).AddOrModifyAttribute("test4", 32.448888l, 3).AddOrModifyAttribute("test5"sv, static_cast<uint64_t>(1850000000));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test3=\"{}\" test4=\"{}\" test5=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, -8, 32.449, 1850000000));
}

TEST(Attributes, CatchEmptyAttributeKeyMultiple)
{
  EXPECT_THROW(XMLBuilder::Node("test").AddOrModifyAttribute("test1", static_cast<uint16_t>(123)).AddOrModifyAttribute("test2", 123.4).AddOrModifyAttribute("test3", "test").AddOrModifyAttribute("test4", 1234.567f).AddOrModifyAttribute("", "test"), std::invalid_argument);
}

TEST(Attributes, Contains)
{
  XMLBuilder::Node node("test");
  node.AddOrModifyAttribute("testAttr", 123);

  EXPECT_TRUE(node.ContainsAttribute("testAttr"));
  EXPECT_FALSE(node.ContainsAttribute("testAttr1"));
  EXPECT_FALSE(node.ContainsAttribute(""));
}

TEST(Attributes, ModifyStringValue)
{
  XMLBuilder::Node node("test");
  node.AddOrModifyAttribute("testAttr", 123);

  node.AddOrModifyAttribute("testAttr", "test1");
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, "test1"));

  char value2Arr[] = "test2";
  char* value2 = value2Arr;
  node.AddOrModifyAttribute("testAttr", value2);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value2));

  const char* value3 = "test3";
  node.AddOrModifyAttribute("testAttr", value3);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value3));

  node.AddOrModifyAttribute("testAttr", "test4"sv);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, "test4"));

  std::string_view value5 = "test5";
  node.AddOrModifyAttribute("testAttr", value5);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value5));

  const std::string_view value6 = "test6";
  node.AddOrModifyAttribute("testAttr", value6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value6));

  std::string value7 = "test7";
  node.AddOrModifyAttribute("testAttr", value7);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value7));

  const std::string_view value8 = "test8";
  node.AddOrModifyAttribute("testAttr", value8);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value8));
}

TEST(Attributes, ModifyByOperatorStringValue)
{
  XMLBuilder::Node node("test");
  node << std::pair("testAttr", 123);

  node << std::pair("testAttr", "test1");
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, "test1"));

  char value2Arr[] = "test2";
  char* value2 = value2Arr;
  node << std::pair("testAttr", value2);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value2));

  const char* value3 = "test3";
  node << std::pair("testAttr", value3);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value3));

  node << std::pair("testAttr", "test4"sv);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, "test4"));

  std::string_view value5 = "test5";
  node << std::pair("testAttr", value5);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value5));

  const std::string_view value6 = "test6";
  node << std::pair("testAttr", value6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value6));

  std::string value7 = "test7";
  node << std::pair("testAttr", value7);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value7));

  const std::string_view value8 = "test8";
  node << std::pair("testAttr", value8);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, value8));
}

TEST(Attributes, ModifyWholeNumberValue)
{
  XMLBuilder::Node node("test");
  node.AddOrModifyAttribute("testAttr", 123);

  node.AddOrModifyAttribute("testAttr", 456);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 456));

  node.AddOrModifyAttribute("testAttr", static_cast<short>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));

  node.AddOrModifyAttribute("testAttr", static_cast<long>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123));

  node.AddOrModifyAttribute("testAttr", static_cast<long long>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));

  node.AddOrModifyAttribute("testAttr", static_cast<int8_t>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123));

  node.AddOrModifyAttribute("testAttr", static_cast<int16_t>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));

  node.AddOrModifyAttribute("testAttr", static_cast<int32_t>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123));

  node.AddOrModifyAttribute("testAttr", static_cast<int64_t>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123));
}

TEST(Attributes, ModifyFloatingValue)
{
  XMLBuilder::Node node("test");
  node.AddOrModifyAttribute("testAttr", 123);

  node.AddOrModifyAttribute("testAttr", 123.123f);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123.123f));

  node.AddOrModifyAttribute("testAttr", -123.123);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123.123));

  node.AddOrModifyAttribute("testAttr", 123.123l);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123.123l));

  node.AddOrModifyAttribute("testAttr", -123.123f, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, -123.123f));

  node.AddOrModifyAttribute("testAttr", 123.123, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, 123.123));

  node.AddOrModifyAttribute("testAttr", -123.123l, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, -123.123l));

  node.AddOrModifyAttribute("testAttr", 123.123f, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, 123.123f));

  node.AddOrModifyAttribute("testAttr", -123.123, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, -123.123));

  node.AddOrModifyAttribute("testAttr", 123.123l, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, 123.123l));
}

TEST(Attributes, ModifyByOperatorFloatingValue)
{
  XMLBuilder::Node node("test");
  node.AddOrModifyAttribute("testAttr", 123);

  node << std::pair("testAttr", 123.123f);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123.123f));

  node << std::pair("testAttr", -123.123);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, -123.123));

  node << std::pair("testAttr", 123.123l);
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{}\"/>\n", DEFAULT_HEADER, 123.123l));

  node << std::pair("testAttr", std::pair(-123.123f, 1));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, -123.123f));

  node << std::pair("testAttr", std::pair(123.123, 1));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, 123.123));

  node << std::pair("testAttr", std::pair(-123.123l, 1));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.1f}\"/>\n", DEFAULT_HEADER, -123.123l));

  node << std::pair("testAttr", std::pair(123.123f, 6));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, 123.123f));

  node << std::pair("testAttr", std::pair(-123.123, 6));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, -123.123));

  node << std::pair("testAttr", std::pair(123.123l, 6));
  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"{:.6f}\"/>\n", DEFAULT_HEADER, 123.123l));
}

TEST(Attributes, Remove)
{
  XMLBuilder::Node node = XMLBuilder::Node("test").AddOrModifyAttribute("test1"sv, "123").AddOrModifyAttribute(std::string("test2"), 92.2).AddOrModifyAttribute("test3", static_cast<int8_t>(-8)).AddOrModifyAttribute("test4", 32.448888l, 3).AddOrModifyAttribute("test5"sv, static_cast<uint64_t>(1850000000));

  node.RemoveAttribute("test3");
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test4=\"{}\" test5=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, 32.449, 1850000000));

  node.RemoveAttribute("test5");
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test4=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, 32.449));

  EXPECT_FALSE(node.RemoveAttribute("test"));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test4=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, 32.449));

  EXPECT_FALSE(node.RemoveAttribute(""));
  EXPECT_EQ(node.Generate(), std::format("{}<test test1=\"{}\" test2=\"{}\" test4=\"{}\"/>\n", DEFAULT_HEADER, 123, 92.2, 32.449));
}

TEST(Attributes, GetByIndexOperator)
{
  XMLBuilder::Node node("test");
  node.AddOrModifyAttribute("testAttr", 123);

  const XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAttr2", 1234);

  EXPECT_EQ(node["testAttr"], "123");
  EXPECT_EQ(node2["testAttr2"], "1234");

  EXPECT_THROW(node["testAttr1"], std::out_of_range);
  EXPECT_THROW(node[""], std::invalid_argument);
}

TEST(Attributes, ModifyByIndexOperator)
{
  XMLBuilder::Node node("test");
  node.AddOrModifyAttribute("testAttr", 123);

  const XMLBuilder::Node node2 = XMLBuilder::Node("test2").AddOrModifyAttribute("testAttr2", 1234);

  node["testAttr"] = "456";
  node2["testAttr2"] = "4567"; // Dont overwrite because its const node

  EXPECT_EQ(node.Generate(), std::format("{}<test testAttr=\"456\"/>\n", DEFAULT_HEADER));
  EXPECT_EQ(node2.Generate(), std::format("{}<test2 testAttr2=\"1234\"/>\n", DEFAULT_HEADER));
}
