//
// Created by Martin on 25. 3. 2025.
//

#include "common.hpp"

#include <cmath>

using namespace std::string_view_literals;

#define GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(name, type_s, type_us) \
TEST(Utility_Converters_ToString, name)\
{\
    EXPECT_EQ(XMLBuilder::types::converters::toString(static_cast<type_s>(123)), "123");\
    EXPECT_EQ(XMLBuilder::types::converters::toString(static_cast<type_s>(-123)), "-123");\
    EXPECT_EQ(XMLBuilder::types::converters::toString(static_cast<type_us>(123)), "123");\
}

TEST(Utility_Converters_ToString, CharArrays)
{
    EXPECT_EQ(XMLBuilder::types::converters::toString("test1"), "test1");

    char value2Arr[] = "test2";
    char* value2 = value2Arr;
    EXPECT_EQ(XMLBuilder::types::converters::toString(value2), "test2");

    const char* value3 = "test3";
    EXPECT_EQ(XMLBuilder::types::converters::toString(value3), "test3");

    char value4[] = "test4";
    EXPECT_EQ(XMLBuilder::types::converters::toString(value4), "test4");

    const char value5[] = "test5";
    EXPECT_EQ(XMLBuilder::types::converters::toString(value5), "test5");

    EXPECT_EQ(XMLBuilder::types::converters::toString(""), "");
}

TEST(Utility_Converters_ToString, String)
{
    EXPECT_EQ(XMLBuilder::types::converters::toString(std::string("test1")), "test1");

    std::string value2 = "test2";
    EXPECT_EQ(XMLBuilder::types::converters::toString(value2), "test2");

    const std::string value3 = "test3";
    EXPECT_EQ(XMLBuilder::types::converters::toString(value3), "test3");

    EXPECT_EQ(XMLBuilder::types::converters::toString(std::string("")), "");
}

TEST(Utility_Converters_ToString, StringView)
{
    EXPECT_EQ(XMLBuilder::types::converters::toString(std::string_view("test1")), "test1");
    EXPECT_EQ(XMLBuilder::types::converters::toString("test2"sv), "test2");

    std::string_view value3 = "test3"sv;
    EXPECT_EQ(XMLBuilder::types::converters::toString(value3), "test3");

    const std::string_view value4 = "test4"sv;
    EXPECT_EQ(XMLBuilder::types::converters::toString(value4), "test4");

    EXPECT_EQ(XMLBuilder::types::converters::toString(std::string_view("")), "");
    EXPECT_EQ(XMLBuilder::types::converters::toString(""sv), "");
}

TEST(Utility_Converters_ToString, Bool)
{
    EXPECT_EQ(XMLBuilder::types::converters::toString(true), "true");
    EXPECT_EQ(XMLBuilder::types::converters::toString(false), "false");
}

GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(Short, short, unsigned short);
GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(Int, int, unsigned int);
GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(Long, long, unsigned long);
GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(LongLong, long long, unsigned long long);
GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(Int8_t, int8_t, uint8_t);
GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(Int16_t, int16_t, uint16_t);
GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(Int32_t, int32_t, uint32_t);
GENERATE_STRING_TEST_FOR_NUMERIC_TYPE(Int64_t, int64_t, uint64_t);

TEST(Utility_Converters_ToString, Float)
{
    EXPECT_EQ(XMLBuilder::types::converters::toString(123.456f), std::format("{}", 123.456f));
    EXPECT_EQ(XMLBuilder::types::converters::toString(-123.456f), std::format("{}", -123.456f));
    EXPECT_EQ(XMLBuilder::types::converters::toString(std::nanf("1")), "nan");
}

TEST(Utility_Converters_ToString, Double)
{
    EXPECT_EQ(XMLBuilder::types::converters::toString(123.456), std::format("{}", 123.456));
    EXPECT_EQ(XMLBuilder::types::converters::toString(-123.456), std::format("{}", -123.456));
    EXPECT_EQ(XMLBuilder::types::converters::toString(std::nan("1")), "nan");
}

TEST(Utility_Converters_ToString, LongDouble)
{
    EXPECT_EQ(XMLBuilder::types::converters::toString(123.456l), std::format("{}", 123.456l));
    EXPECT_EQ(XMLBuilder::types::converters::toString(-123.456l), std::format("{}", -123.456l));
    EXPECT_EQ(XMLBuilder::types::converters::toString(std::nanl("1")), "nan");
}

TEST(Utility_Converters_FloatingToString, FloatLimitPrecision)
{
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(123.456f, 2), std::format("{:.2f}", 123.456f));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(-123.456f, 2), std::format("{:.2f}", -123.456f));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(std::nanf("1"), 2), "nan");
}

TEST(Utility_Converters_FloatingToString, DoubleLimitPrecision)
{
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(123.456, 2), std::format("{:.2f}", 123.456));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(-123.456, 2), std::format("{:.2f}", -123.456));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(std::nan("1"), 2), "nan");
}

TEST(Utility_Converters_FloatingToString, LongDoubleLimitPrecision)
{
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(123.456l, 2), std::format("{:.2f}", 123.456l));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(-123.456l, 2), std::format("{:.2f}", -123.456l));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(std::nanl("1"), 2), "nan");
}

TEST(Utility_Converters_FloatingToString, FloatExtendPrecision)
{
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(123.456f, 6), std::format("{:.6f}", 123.456f));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(-123.456f, 6), std::format("{:.6f}", -123.456f));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(std::nanf("1"), 6), "nan");
}

TEST(Utility_Converters_FloatingToString, DoubleExtendPrecision)
{
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(123.456, 6), std::format("{:.6f}", 123.456));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(-123.456, 6), std::format("{:.6f}", -123.456));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(std::nan("1"), 6), "nan");
}

TEST(Utility_Converters_FloatingToString, LongDoubleExtendPrecision)
{
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(123.456l, 6), std::format("{:.6f}", 123.456l));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(-123.456l, 6), std::format("{:.6f}", -123.456l));
    EXPECT_EQ(XMLBuilder::types::converters::floatingToString(std::nanl("1"), 6), "nan");
}
