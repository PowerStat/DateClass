/*
 * Copyright (C) 2020-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <climits>
#include <utility>
#include <stdexcept>
#include <iostream>
#include "Days.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(DaysTest, constructor1)
   {
    constexpr Days days {0};
    ASSERT_EQ(days.getDays(), 0);
   }


  TEST(DaysTest, constructor2)
   {
    constexpr Days days {ULONG_MAX};
    ASSERT_EQ(days.getDays(), ULONG_MAX);
   }


  TEST(DaysTest, copyConstructor)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {days1};
    ASSERT_EQ(days2.getDays(), 12);
    ASSERT_TRUE(&days1 != &days2);
   }


  TEST(DaysTest, moveConstructor)
   {
    Days days1 {12};
    const Days days2 {std::move(days1)};
    ASSERT_EQ(days2.getDays(), 12);
   }


  TEST(DaysTest, equalOperator1)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {12};
    ASSERT_TRUE(days1 == days2);
   }


  TEST(DaysTest, equalOperator2)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {18};
    ASSERT_FALSE(days1 == days2);
   }


  TEST(DaysTest, notEqualOperator1)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {18};
    ASSERT_TRUE(days1 != days2);
   }


  TEST(DaysTest, notEqualOperator2)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {12};
    ASSERT_FALSE(days1 != days2);
   }


  TEST(DaysTest, smallerOperator1)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {18};
    ASSERT_TRUE(days1 < days2);
   }


  TEST(DaysTest, smallerOperator2)
   {
    constexpr Days days1 {18};
    constexpr Days days2 {12};
    ASSERT_FALSE(days1 < days2);
   }


  TEST(DaysTest, smallerOperator3)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {12};
    ASSERT_FALSE(days1 < days2);
   }


  TEST(DaysTest, greaterOperator1)
   {
    constexpr Days days1 {18};
    constexpr Days days2 {12};
    ASSERT_TRUE(days1 > days2);
   }


  TEST(DaysTest, greaterOperator2)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {18};
    ASSERT_FALSE(days1 > days2);
   }


  TEST(DaysTest, greaterOperator3)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {12};
    ASSERT_FALSE(days1 > days2);
   }


  TEST(DaysTest, smallerEqualOperator1)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {18};
    ASSERT_TRUE(days1 <= days2);
   }


  TEST(DaysTest, smallerEqualOperator2)
   {
    constexpr Days days1 {18};
    constexpr Days days2 {12};
    ASSERT_FALSE(days1 <= days2);
   }


  TEST(DaysTest, smallerEqualOperator3)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {12};
    ASSERT_TRUE(days1 <= days2);
   }


  TEST(DaysTest, greaterEqualOperator1)
   {
    constexpr Days days1 {18};
    constexpr Days days2 {12};
    ASSERT_TRUE(days1 >= days2);
   }


  TEST(DaysTest, greaterEqualOperator2)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {18};
    ASSERT_FALSE(days1 >= days2);
   }


  TEST(DaysTest, greaterEqualOperator3)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {12};
    ASSERT_TRUE(days1 >= days2);
   }


  TEST(DaysTest, plusDays1)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {6};
    constexpr Days newDays = days1 + days2;
    ASSERT_EQ(newDays.getDays(), 18);
   }


  TEST(DaysTest, plusDays2)
   {
    constexpr Days days1 {ULONG_MAX};
    constexpr Days days2 {20};
    try
     {
      [[maybe_unused]] const Days newDay = days1 + days2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"days will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(DaysTest, minusDays1)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {6};
    constexpr Days newDays = days1 - days2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(DaysTest, minusDays2)
   {
    constexpr Days days1 {12};
    constexpr Days days2 {18};
    constexpr Days newDays = days1 - days2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(DaysTest, multDays1)
   {
    constexpr Days days1 {12};
    constexpr Days newDays = days1 * 2;
    ASSERT_EQ(newDays.getDays(), 24);
   }


  TEST(DaysTest, multDays2)
   {
    constexpr Days days1 {ULONG_MAX};
    try
     {
      [[maybe_unused]] const Days newDay = days1 * 2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"days will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(DaysTest, divDays1)
   {
    constexpr Days days1 {12};
    constexpr Days newDays = days1 / 2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(DaysTest, divDays2)
   {
    constexpr Days days1 {12};
    try
     {
      [[maybe_unused]] const Days newDays = days1 / 0;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"Division by zero"}.compare(e.what()), 0);
     }
   }


  TEST(DaysTest, reminderDays1)
   {
    constexpr Days days1 {12};
    constexpr Days newDays = days1 % 2;
    ASSERT_EQ(newDays.getDays(), 0);
   }


  TEST(DaysTest, reminderDays2)
   {
    constexpr Days days1 {12};
    try
     {
      [[maybe_unused]] const Days newDay = days1 % 0;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"Division by zero"}.compare(e.what()), 0);
     }
   }


  TEST(DaysTest, coutDays1)
   {
    constexpr Days days1 {12};
    testing::internal::CaptureStdout();
    std::cout << days1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Days(12)");
   }

 }
