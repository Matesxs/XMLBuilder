#include "common.hpp"

#include <string>
#include <cstdint>
#include <cmath>

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

TEST(ValueNode, BoolValue)
{
  XMLBuilder::ValueNode node1("test1", true);
  XMLBuilder::ValueNode node2("test2", false);

  EXPECT_EQ(node1.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 1, "true", 1));
  EXPECT_EQ(node2.Generate(), std::format("{}<test{}>{}</test{}>\n", DEFAULT_HEADER, 2, "false", 2));
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

TEST(ValueNode, GetValueString)
{
  XMLBuilder::ValueNode node("test", 123.45l, 8);

  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.8f}</test>\n", DEFAULT_HEADER, 123.45l));
  EXPECT_EQ(node.Get(), std::format("{:.8f}", 123.45l));
}

TEST(ValueNode, ModifyValueString)
{
  XMLBuilder::ValueNode node("test", "value");

  node.ModifyValue("test1");
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, "test1"));

  char value2Arr[] = "test2";
  char* value2 = value2Arr;
  node.ModifyValue(value2);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value2));

  const char* value3 = "test3";
  node.ModifyValue(value3);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value3));

  node.ModifyValue("test4"sv);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, "test4"));

  std::string_view value5 = "test5";
  node.ModifyValue(value5);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value5));

  const std::string_view value6 = "test6";
  node.ModifyValue(value6);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value6));

  std::string value7 = "test7";
  node.ModifyValue(value7);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value7));

  const std::string_view value8 = "test8";
  node.ModifyValue(value8);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value8));
}

TEST(ValueNode, ModifyValueWholeNumber)
{
  XMLBuilder::ValueNode node("test", 123);

  node.ModifyValue(456);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 456));

  node.ModifyValue(static_cast<short>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123));

  node.ModifyValue(static_cast<long>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, -123));

  node.ModifyValue(static_cast<long long>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123));

  node.ModifyValue(static_cast<int8_t>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, -123));

  node.ModifyValue(static_cast<int16_t>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123));

  node.ModifyValue(static_cast<int32_t>(-123));
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, -123));

  node.ModifyValue(static_cast<int64_t>(123));
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123));
}

TEST(ValueNode, ModifyValueFloating)
{
  XMLBuilder::ValueNode node("test", "test");

  node.ModifyValue(123.123f);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123.123f));

  node.ModifyValue(-123.123);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, -123.123));

  node.ModifyValue(123.123l);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123.123l));

  node.ModifyValue(-123.123f, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.1f}</test>\n", DEFAULT_HEADER, -123.123f));

  node.ModifyValue(123.123, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.1f}</test>\n", DEFAULT_HEADER, 123.123));

  node.ModifyValue(-123.123l, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.1f}</test>\n", DEFAULT_HEADER, -123.123l));

  node.ModifyValue(123.123f, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.6f}</test>\n", DEFAULT_HEADER, 123.123f));

  node.ModifyValue(-123.123, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.6f}</test>\n", DEFAULT_HEADER, -123.123));

  node.ModifyValue(123.123l, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.6f}</test>\n", DEFAULT_HEADER, 123.123l));
}

TEST(ValueNode, ModifyValueStringByOperator)
{
  XMLBuilder::ValueNode node("test", "value");

  node = "test1";
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, "test1"));

  char value2Arr[] = "test2";
  char* value2 = value2Arr;
  node = value2;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value2));

  const char* value3 = "test3";
  node = value3;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value3));

  node = "test4"sv;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, "test4"));

  std::string_view value5 = "test5";
  node = value5;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value5));

  const std::string_view value6 = "test6";
  node = value6;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value6));

  std::string value7 = "test7";
  node = value7;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value7));

  const std::string_view value8 = "test8";
  node = value8;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, value8));
}

TEST(ValueNode, ModifyValueWholeNumberByOperator)
{
  XMLBuilder::ValueNode node("test", 123);

  node = 456;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 456));

  node = static_cast<short>(123);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123));

  node = static_cast<long>(-123);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, -123));

  node = static_cast<long long>(123);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123));

  node = static_cast<int8_t>(-123);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, -123));

  node = static_cast<int16_t>(123);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123));

  node = static_cast<int32_t>(-123);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, -123));

  node = static_cast<int64_t>(123);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123));
}

TEST(ValueNode, ModifyValueFloatingByOperator)
{
  XMLBuilder::ValueNode node("test", "test");

  node = 123.123f;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123.123f));

  node = -123.123;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, -123.123));

  node = 123.123l;
  EXPECT_EQ(node.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, 123.123l));

  node = std::pair(-123.123f, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.1f}</test>\n", DEFAULT_HEADER, -123.123f));

  node = std::pair(123.123, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.1f}</test>\n", DEFAULT_HEADER, 123.123));

  node = std::pair(-123.123l, 1);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.1f}</test>\n", DEFAULT_HEADER, -123.123l));

  node = std::pair(123.123f, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.6f}</test>\n", DEFAULT_HEADER, 123.123f));

  node = std::pair(-123.123, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.6f}</test>\n", DEFAULT_HEADER, -123.123));

  node = std::pair(123.123l, 6);
  EXPECT_EQ(node.Generate(), std::format("{}<test>{:.6f}</test>\n", DEFAULT_HEADER, 123.123l));
}

TEST(ValueNode, ModifyValueByReference)
{
  XMLBuilder::ValueNode node1("test", "test");
  node1.Get() = "test1";

  const XMLBuilder::ValueNode node2 ("test", "test");
  node2.Get() = "test2"; // Not modified, returned by value

  EXPECT_EQ(node1.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, "test1"));
  EXPECT_EQ(node2.Generate(), std::format("{}<test>{}</test>\n", DEFAULT_HEADER, "test"));
}
