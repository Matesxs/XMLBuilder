#include "common.hpp"

#include <string>
#include <string_view>
#include <cstdint>

using namespace std::string_view_literals;

TEST(ValueNode, charArrayValue)
{
  XMLBuilder::ValueNode node1("test1", "value1");

  char value2Arr[] = "value2";
  char* value2 = value2Arr;
  XMLBuilder::ValueNode node2("test2", value2);

  const char* value3 = "value3";
  XMLBuilder::ValueNode node3("test3", value3);

  char value4[] = "value4";
  XMLBuilder::ValueNode node4("test4", value4);

  const char value5[] = "value5";
  XMLBuilder::ValueNode node5("test5", value5);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 3, 3, 3));
  EXPECT_EQ(node4.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 4, 4, 4));
  EXPECT_EQ(node5.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 5, 5, 5));
}

TEST(ValueNode, stringValue)
{
  XMLBuilder::ValueNode node1("test1", std::string("value1"));

  std::string value2 = "value2";
  XMLBuilder::ValueNode node2("test2", value2);

  const std::string value3 = "value3";
  XMLBuilder::ValueNode node3("test3", value3);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(ValueNode, stringViewValue)
{
  XMLBuilder::ValueNode node1("test1", "value1"sv);

  std::string_view value2 = "value2"sv;
  XMLBuilder::ValueNode node2("test2", value2);

  const std::string_view value3 = "value3"sv;
  XMLBuilder::ValueNode node3("test3", value3);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 2, 2, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>value{}</test{}>\n", DEFAULT_HEADER, 3, 3, 3));
}

TEST(ValueNode, NumericBoolValue)
{
  XMLBuilder::ValueNode node1("test1", true);
  XMLBuilder::ValueNode node2("test2", false);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 1, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, 0, 2));
}

TEST(ValueNode, ShortValue)
{
  XMLBuilder::ValueNode node1("test1", static_cast<short>(123));
  XMLBuilder::ValueNode node2("test2", static_cast<short>(-123));
  XMLBuilder::ValueNode node3("test3", static_cast<unsigned short>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, 123, 3));
}

TEST(ValueNode, IntValue)
{
  XMLBuilder::ValueNode node1("test1", static_cast<int>(123));
  XMLBuilder::ValueNode node2("test2", static_cast<int>(-123));
  XMLBuilder::ValueNode node3("test3", static_cast<unsigned int>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, 123, 3));
}

TEST(ValueNode, LongValue)
{
  XMLBuilder::ValueNode node1("test1", static_cast<long>(123));
  XMLBuilder::ValueNode node2("test2", static_cast<long>(-123));
  XMLBuilder::ValueNode node3("test3", static_cast<unsigned long>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, 123, 3));
}

TEST(ValueNode, LongLongValue)
{
  XMLBuilder::ValueNode node1("test1", static_cast<long long>(123));
  XMLBuilder::ValueNode node2("test2", static_cast<long long>(-123));
  XMLBuilder::ValueNode node3("test3", static_cast<unsigned long long>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, 123, 3));
}

TEST(ValueNode, int8Value)
{
  XMLBuilder::ValueNode node1("test1", static_cast<int8_t>(123));
  XMLBuilder::ValueNode node2("test2", static_cast<int8_t>(-123));
  XMLBuilder::ValueNode node3("test3", static_cast<uint8_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, 123, 3));
}

TEST(ValueNode, int16Value)
{
  XMLBuilder::ValueNode node1("test1", static_cast<int16_t>(123));
  XMLBuilder::ValueNode node2("test2", static_cast<int16_t>(-123));
  XMLBuilder::ValueNode node3("test3", static_cast<uint16_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, 123, 3));
}

TEST(ValueNode, int32Value)
{
  XMLBuilder::ValueNode node1("test1", static_cast<int32_t>(123));
  XMLBuilder::ValueNode node2("test2", static_cast<int32_t>(-123));
  XMLBuilder::ValueNode node3("test3", static_cast<uint32_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, 123, 3));
}

TEST(ValueNode, int64Value)
{
  XMLBuilder::ValueNode node1("test1", static_cast<int64_t>(123));
  XMLBuilder::ValueNode node2("test2", static_cast<int64_t>(-123));
  XMLBuilder::ValueNode node3("test3", static_cast<uint64_t>(123));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, 123, 3));
}

TEST(ValueNode, floatValueRaw)
{
  XMLBuilder::ValueNode node1("test1", 123.456789f);
  XMLBuilder::ValueNode node2("test2", -123.456789f);
  XMLBuilder::ValueNode node3("test3", std::nanf("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123.456789f, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123.456789f, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}

TEST(ValueNode, doubleValueRaw)
{
  XMLBuilder::ValueNode node1("test1", 123.456789);
  XMLBuilder::ValueNode node2("test2", -123.456789);
  XMLBuilder::ValueNode node3("test3", std::nan("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123.456789, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123.456789, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}

TEST(ValueNode, longDoubleValueRaw)
{
  XMLBuilder::ValueNode node1("test1", 123.456789l);
  XMLBuilder::ValueNode node2("test2", -123.456789l);
  XMLBuilder::ValueNode node3("test3", std::nanl("1"));

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, 123.456789l, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, -123.456789l, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}

TEST(ValueNode, floatValueLimitPrecision)
{
  XMLBuilder::ValueNode node1("test1", 123.456789f, 2);
  XMLBuilder::ValueNode node2("test2", -123.456789f, 2);
  XMLBuilder::ValueNode node3("test3", std::nanf("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{:.2f}</test{}>\n", DEFAULT_HEADER, 1, 123.456789f, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{:.2f}</test{}>\n", DEFAULT_HEADER, 2, -123.456789f, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}

TEST(ValueNode, doubleValueLimitPrecision)
{
  XMLBuilder::ValueNode node1("test1", 123.456789, 2);
  XMLBuilder::ValueNode node2("test2", -123.456789, 2);
  XMLBuilder::ValueNode node3("test3", std::nan("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{:.2f}</test{}>\n", DEFAULT_HEADER, 1, 123.456789, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{:.2f}</test{}>\n", DEFAULT_HEADER, 2, -123.456789, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}

TEST(ValueNode, longDoubleValueLimitPrecision)
{
  XMLBuilder::ValueNode node1("test1", 123.456789l, 2);
  XMLBuilder::ValueNode node2("test2", -123.456789l, 2);
  XMLBuilder::ValueNode node3("test3", std::nanl("1"), 2);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{:.2f}</test{}>\n", DEFAULT_HEADER, 1, 123.456789l, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{:.2f}</test{}>\n", DEFAULT_HEADER, 2, -123.456789l, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}

TEST(ValueNode, floatValueLimitExtendPrecision)
{
  XMLBuilder::ValueNode node1("test1", 123.45f, 8);
  XMLBuilder::ValueNode node2("test2", -123.45f, 8);
  XMLBuilder::ValueNode node3("test3", std::nanf("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{:.8f}</test{}>\n", DEFAULT_HEADER, 1, 123.45f, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{:.8f}</test{}>\n", DEFAULT_HEADER, 2, -123.45f, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}

TEST(ValueNode, doubleValueLimitExtendPrecision)
{
  XMLBuilder::ValueNode node1("test1", 123.45, 8);
  XMLBuilder::ValueNode node2("test2", -123.45, 8);
  XMLBuilder::ValueNode node3("test3", std::nan("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{:.8f}</test{}>\n", DEFAULT_HEADER, 1, 123.45, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{:.8f}</test{}>\n", DEFAULT_HEADER, 2, -123.45, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}

TEST(ValueNode, longDoubleValueLimitExtendPrecision)
{
  XMLBuilder::ValueNode node1("test1", 123.45l, 8);
  XMLBuilder::ValueNode node2("test2", -123.45l, 8);
  XMLBuilder::ValueNode node3("test3", std::nanl("1"), 8);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{:.8f}</test{}>\n", DEFAULT_HEADER, 1, 123.45l, 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{:.8f}</test{}>\n", DEFAULT_HEADER, 2, -123.45l, 2));
  EXPECT_EQ(node3.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 3, "nan", 3));
}
