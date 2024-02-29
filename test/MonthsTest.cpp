/*
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <climits>
#include "Months.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(MonthsTest, constructor1)
   {
    constexpr Months months {0};
    ASSERT_EQ(months.getMonths(), 0);
   }


  TEST(MonthsTest,constructor2)
   {
    constexpr Months months {ULONG_MAX};
    ASSERT_EQ(months.getMonths(), ULONG_MAX);
   }


  TEST(MonthsTest, copyConstructor)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {months1};
    ASSERT_EQ(months2.getMonths(), 12);
    ASSERT_TRUE(&months1 != &months2);
   }


  TEST(MonthsTest, moveConstructor)
   {
    Months months1 {12};
    const Months months2 {std::move(months1)};
    ASSERT_EQ(months2.getMonths(), 12);
   }


  TEST(MonthsTest, equalOperator1)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {12};
    ASSERT_TRUE(months1 == months2);
   }


  TEST(MonthsTest, equalOperator2)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {18};
    ASSERT_FALSE(months1 == months2);
   }


  TEST(MonthsTest, notEqualOperator1)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {18};
    ASSERT_TRUE(months1 != months2);
   }


  TEST(MonthsTest, notEqualOperator2)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {12};
    ASSERT_FALSE(months1 != months2);
   }


  TEST(MonthsTest, smallerOperator1)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {18};
    ASSERT_TRUE(months1 < months2);
   }


  TEST(MonthsTest, smallerOperator2)
   {
    constexpr Months months1 {18};
    constexpr Months months2 {12};
    ASSERT_FALSE(months1 < months2);
   }


  TEST(MonthsTest, smallerOperator3)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {12};
    ASSERT_FALSE(months1 < months2);
   }


  TEST(MonthsTest, greaterOperator1)
   {
    constexpr Months months1 {18};
    constexpr Months months2 {12};
    ASSERT_TRUE(months1 > months2);
   }


  TEST(MonthsTest, greaterOperator2)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {18};
    ASSERT_FALSE(months1 > months2);
   }


  TEST(MonthsTest, greaterOperator3)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {12};
    ASSERT_FALSE(months1 > months2);
   }


  TEST(MonthsTest, smallerEqualOperator1)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {18};
    ASSERT_TRUE(months1 <= months2);
   }


  TEST(MonthsTest, smallerEqualOperator2)
   {
    constexpr Months months1 {18};
    constexpr Months months2 {12};
    ASSERT_FALSE(months1 <= months2);
   }


  TEST(MonthsTest, smallerEqualOperator3)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {12};
    ASSERT_TRUE(months1 <= months2);
   }


  TEST(MonthsTest, greaterEqualOperator1)
   {
    constexpr Months months1 {18};
    constexpr Months months2 {12};
    ASSERT_TRUE(months1 >= months2);
   }


  TEST(MonthsTest, greaterEqualOperator2)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {18};
    ASSERT_FALSE(months1 >= months2);
   }


  TEST(MonthsTest, greaterEqualOperator3)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {12};
    ASSERT_TRUE(months1 >= months2);
   }


  TEST(MonthsTest, plusMonths1)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {6};
    constexpr Months newMonths = months1 + months2;
    ASSERT_EQ(newMonths.getMonths(), 18);
   }


  TEST(MonthsTest, plusMonths2)
   {
    constexpr Months months1 {ULONG_MAX};
    constexpr Months months2 {20};
    try
     {
      [[maybe_unused]] const Months newDay = months1 + months2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"months will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(MonthsTest, minusMonths1)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {6};
    constexpr Months newMonths = months1 - months2;
    ASSERT_EQ(newMonths.getMonths(), 6);
   }


  TEST(MonthsTest, minusMonths2)
   {
    constexpr Months months1 {12};
    constexpr Months months2 {18};
    constexpr Months newMonths = months1 - months2;
    ASSERT_EQ(newMonths.getMonths(), 6);
   }


  TEST(MonthsTest, multMonths1)
   {
    constexpr Months months1 {12};
    constexpr Months newMonths = months1 * 2;
    ASSERT_EQ(newMonths.getMonths(), 24);
   }


  TEST(MonthsTest, multMonths2)
   {
    constexpr Months months1 {ULONG_MAX};
    try
     {
      [[maybe_unused]] const Months newMonth = months1 * 2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"months will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(MonthsTest, divMonths1)
   {
    constexpr Months months1 {12};
    constexpr Months newMonths = months1 / 2;
    ASSERT_EQ(newMonths.getMonths(), 6);
   }


  TEST(DaysTest, divMonths2)
   {
    constexpr Months months1 {12};
    try
     {
      [[maybe_unused]] const Months newMonths = months1 / 0;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"Division by zero"}.compare(e.what()), 0);
     }
   }


  TEST(MonthsTest, reminderMonths1)
   {
    constexpr Months months1 {12};
    constexpr Months newMonths = months1 % 2;
    ASSERT_EQ(newMonths.getMonths(), 0);
   }


  TEST(DaysTest, reminderMonths2)
   {
    constexpr Months months1 {12};
    try
     {
      [[maybe_unused]] const Months newMonths = months1 % 0;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"Division by zero"}.compare(e.what()), 0);
     }
   }


  TEST(MonthsTest, coutMonths1)
   {
    constexpr Months months1 {12};
    testing::internal::CaptureStdout();
    std::cout << months1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Months(12)");
   }

 }
