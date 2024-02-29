/*
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <utility>
#include <iostream>
#include "JulianMonth.h"
#include "Months.h"
#include "JulianYear.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(JulianMonthTest, constructor1)
   {
    constexpr JulianMonth month {1};
    ASSERT_EQ(month.getMonth(), 1);
   }


  TEST(JulianMonthTest, constructor2)
   {
    constexpr JulianMonth month {12};
    ASSERT_EQ(month.getMonth(), 12);
   }


  TEST(JulianMonthTest, constructor3)
   {
    try
     {
      [[maybe_unused]] const JulianMonth month {0};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"month is < 1 or > 12"}.compare(e.what()), 0);
     }
   }


  TEST(JulianMonthTest, constructor4)
   {
    try
     {
      [[maybe_unused]] const JulianMonth month {13};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"month is < 1 or > 12"}.compare(e.what()), 0);
     }
   }


  TEST(JulianMonthTest, constructor5)
   {
    const JulianYear year {8};
    const JulianMonth month {year, 1};
    ASSERT_EQ(month.getMonth(), 1);
   }


  TEST(JulianMonthTest, constructor6)
   {
    try
     {
      const JulianYear year {8};
      [[maybe_unused]] const JulianMonth month {year, 0};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"month is < 1 or > 12"}.compare(e.what()), 0);
     }
   }


  TEST(JulianMonthTest, copyConstructor)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {month1};
    ASSERT_EQ(month2.getMonth(), 6);
    ASSERT_TRUE(&month1 != &month2);
   }


  TEST(JulianMonthTest, moveConstructor)
   {
    JulianMonth month1 {12};
    const JulianMonth month2 {std::move(month1)};
    ASSERT_EQ(month2.getMonth(), 12);
   }


  TEST(JulianMonthTest, getMonth)
   {
    constexpr JulianMonth month1 {12};
    ASSERT_EQ(month1.getMonth(), 12);
   }


  TEST(JulianMonthTest, getDaysInMonth1)
   {
    constexpr JulianMonth month1 {1};
    ASSERT_EQ(month1.getDaysInMonth().getDays(), 31);
   }


  TEST(JulianMonthTest, getDaysInMonth2)
   {
    constexpr JulianMonth month1 {4};
    ASSERT_EQ(month1.getDaysInMonth().getDays(), 30);
   }


  TEST(JulianMonthTest, getDaysInMonth3)
   {
    constexpr JulianMonth month1 {2};
    ASSERT_EQ(month1.getDaysInMonth().getDays(), 28);
   }


  TEST(JulianMonthTest, getDaysInMonth4)
   {
    constexpr JulianMonth month1 {JulianYear(8), 2};
    ASSERT_EQ(month1.getDaysInMonth().getDays(), 29);
   }


  TEST(JulianMonthTest, equalOperator1)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {6};
    ASSERT_TRUE(month1 == month2);
   }


  TEST(JulianMonthTest, equalOperator2)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {8};
    ASSERT_FALSE(month1 == month2);
   }


  TEST(JulianMonthTest, notEqualOperator1)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {8};
    ASSERT_TRUE(month1 != month2);
   }


  TEST(JulianMonthTest, notEqualOperator2)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {6};
    ASSERT_FALSE(month1 != month2);
   }


  TEST(JulianMonthTest, smallerOperator1)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {8};
    ASSERT_TRUE(month1 < month2);
   }


  TEST(JulianMonthTest, smallerOperator2)
   {
    constexpr JulianMonth month1 {8};
    constexpr JulianMonth month2 {6};
    ASSERT_FALSE(month1 < month2);
   }


  TEST(JulianMonthTest, smallerOperator3)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {6};
    ASSERT_FALSE(month1 < month2);
   }


  TEST(JulianMonthTest, greaterOperator1)
   {
    constexpr JulianMonth month1 {8};
    constexpr JulianMonth month2 {6};
    ASSERT_TRUE(month1 > month2);
   }


  TEST(JulianMonthTest, greaterOperator2)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {8};
    ASSERT_FALSE(month1 > month2);
   }


  TEST(JulianMonthTest, greaterOperator3)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {6};
    ASSERT_FALSE(month1 > month2);
   }


  TEST(JulianMonthTest, smallerEqualOperator1)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {8};
    ASSERT_TRUE(month1 <= month2);
   }


  TEST(JulianMonthTest, smallerEqualOperator2)
   {
    constexpr JulianMonth month1 {8};
    constexpr JulianMonth month2 {6};
    ASSERT_FALSE(month1 <= month2);
   }


  TEST(JulianMonthTest, smallerEqualOperator3)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {6};
    ASSERT_TRUE(month1 <= month2);
   }


  TEST(JulianMonthTest, greaterEqualOperator1)
   {
    constexpr JulianMonth month1 {8};
    constexpr JulianMonth month2 {6};
    ASSERT_TRUE(month1 >= month2);
   }


  TEST(JulianMonthTest, greaterEqualOperator2)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {8};
    ASSERT_FALSE(month1 >= month2);
   }


  TEST(JulianMonthTest, greaterEqualOperator3)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {6};
    ASSERT_TRUE(month1 >= month2);
   }


  TEST(JulianMonthTest, plusMonths1)
   {
    constexpr JulianMonth month {6};
    constexpr Months months {2};
    constexpr JulianMonth newMonth = month + months;
    ASSERT_EQ(newMonth.getMonth(), 8);
   }


  TEST(JulianMonthTest, plusMonths2)
   {
    constexpr JulianMonth month {3};
    constexpr Months months {10};
    try
     {
      [[maybe_unused]] const JulianMonth newMonth = month + months;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"month will be > 12"}.compare(e.what()), 0);
     }
   }


  TEST(JulianMonthTest, minusMonths1)
   {
    constexpr JulianMonth month {6};
    constexpr Months months {2};
    constexpr JulianMonth newMonth = month - months;
    ASSERT_EQ(newMonth.getMonth(), 4);
   }


  TEST(JulianMonthTest, minusMonths2)
   {
    constexpr JulianMonth month {6};
    constexpr Months months {8};
    try
     {
      [[maybe_unused]] const JulianMonth newMonth = month - months;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string("month will be < 1").compare(e.what()), 0);
     }
   }


  TEST(JulianMonthTest, minusMonth1)
   {
    constexpr JulianMonth month1 {12};
    constexpr JulianMonth month2 {6};
    constexpr Months newMonths = month1 - month2;
    ASSERT_EQ(newMonths.getMonths(), 6);
   }


  TEST(JulianMonthTest, minusMonth2)
   {
    constexpr JulianMonth month1 {6};
    constexpr JulianMonth month2 {12};
    constexpr Months newMonths = month1 - month2;
    ASSERT_EQ(newMonths.getMonths(), 6);
   }


  TEST(JulianMonthTest, coutMonth1)
   {
    constexpr JulianMonth month1 {12};
    testing::internal::CaptureStdout();
    std::cout << month1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "JulianMonth(12)");
   }

 }
