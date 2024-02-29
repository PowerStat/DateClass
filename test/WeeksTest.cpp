/*
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <climits>
#include "Weeks.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(WeeksTest, constructor1)
   {
    constexpr Weeks weeks {0};
    ASSERT_EQ(weeks.getWeeks(), 0);
   }


  TEST(WeeksTest,constructor2)
   {
    constexpr Weeks weeks {ULONG_MAX};
    ASSERT_EQ(weeks.getWeeks(), ULONG_MAX);
   }


  TEST(WeeksTest, copyConstructor)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {weeks1};
    ASSERT_EQ(weeks2.getWeeks(), 12);
    ASSERT_TRUE(&weeks1 != &weeks2);
   }


  TEST(WeeksTest, moveConstructor)
   {
    Weeks weeks1 {12};
    const Weeks weeks2 {std::move(weeks1)};
    ASSERT_EQ(weeks2.getWeeks(), 12);
   }


  TEST(WeeksTest, equalOperator1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {12};
    ASSERT_TRUE(weeks1 == weeks2);
   }


  TEST(WeeksTest, equalOperator2)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {18};
    ASSERT_FALSE(weeks1 == weeks2);
   }


  TEST(WeeksTest, notEqualOperator1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {18};
    ASSERT_TRUE(weeks1 != weeks2);
   }


  TEST(WeeksTest, notEqualOperator2)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {12};
    ASSERT_FALSE(weeks1 != weeks2);
   }


  TEST(WeeksTest, smallerOperator1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {18};
    ASSERT_TRUE(weeks1 < weeks2);
   }


  TEST(WeeksTest, smallerOperator2)
   {
    constexpr Weeks weeks1 {18};
    constexpr Weeks weeks2 {12};
    ASSERT_FALSE(weeks1 < weeks2);
   }


  TEST(WeeksTest, smallerOperator3)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {12};
    ASSERT_FALSE(weeks1 < weeks2);
   }


  TEST(WeeksTest, greaterOperator1)
   {
    constexpr Weeks weeks1 {18};
    constexpr Weeks weeks2 {12};
    ASSERT_TRUE(weeks1 > weeks2);
   }


  TEST(WeeksTest, greaterOperator2)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {18};
    ASSERT_FALSE(weeks1 > weeks2);
   }


  TEST(WeeksTest, greaterOperator3)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {12};
    ASSERT_FALSE(weeks1 > weeks2);
   }


  TEST(WeeksTest, smallerEqualOperator1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {18};
    ASSERT_TRUE(weeks1 <= weeks2);
   }


  TEST(WeeksTest, smallerEqualOperator2)
   {
    constexpr Weeks weeks1 {18};
    constexpr Weeks weeks2 {12};
    ASSERT_FALSE(weeks1 <= weeks2);
   }


  TEST(WeeksTest, smallerEqualOperator3)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {12};
    ASSERT_TRUE(weeks1 <= weeks2);
   }


  TEST(WeeksTest, greaterEqualOperator1)
   {
    constexpr Weeks weeks1 {18};
    constexpr Weeks weeks2 {12};
    ASSERT_TRUE(weeks1 >= weeks2);
   }


  TEST(WeeksTest, greaterEqualOperator2)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {18};
    ASSERT_FALSE(weeks1 >= weeks2);
   }


  TEST(WeeksTest, greaterEqualOperator3)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {12};
    ASSERT_TRUE(weeks1 >= weeks2);
   }


  TEST(WeeksTest, plusWeeks1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {6};
    constexpr Weeks newWeeks = weeks1 + weeks2;
    ASSERT_EQ(newWeeks.getWeeks(), 18);
   }


  TEST(WeeksTest, plusWeeks2)
   {
    constexpr Weeks weeks1 {ULONG_MAX};
    constexpr Weeks weeks2 {20};
    try
     {
      [[maybe_unused]] const Weeks newDay = weeks1 + weeks2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"weeks will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(WeeksTest, minusWeeks1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {6};
    constexpr Weeks newWeeks = weeks1 - weeks2;
    ASSERT_EQ(newWeeks.getWeeks(), 6);
   }


  TEST(WeeksTest, minusWeeks2)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks weeks2 {18};
    constexpr Weeks newWeeks = weeks1 - weeks2;
    ASSERT_EQ(newWeeks.getWeeks(), 6);
   }


  TEST(WeeksTest, multWeeks1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks newWeeks = weeks1 * 2;
    ASSERT_EQ(newWeeks.getWeeks(), 24);
   }


  TEST(WeeksTest, multWeeks2)
   {
    constexpr Weeks weeks1 {ULONG_MAX};
    try
     {
      [[maybe_unused]] const Weeks newWeek = weeks1 * 2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"weeks will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(WeeksTest, divWeeks1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks newWeeks = weeks1 / 2;
    ASSERT_EQ(newWeeks.getWeeks(), 6);
   }


  TEST(DaysTest, divWeeks2)
   {
    constexpr Weeks weeks1 {12};
    try
     {
      [[maybe_unused]] const Weeks newWeeks = weeks1 / 0;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"Division by zero"}.compare(e.what()), 0);
     }
   }


  TEST(WeeksTest, reminderWeeks1)
   {
    constexpr Weeks weeks1 {12};
    constexpr Weeks newWeeks = weeks1 % 2;
    ASSERT_EQ(newWeeks.getWeeks(), 0);
   }


  TEST(DaysTest, reminderWeeks2)
   {
    constexpr Weeks weeks1 {12};
    try
     {
      [[maybe_unused]] const Weeks newWeeks = weeks1 % 0;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"Division by zero"}.compare(e.what()), 0);
     }
   }


  TEST(WeeksTest, coutWeeks1)
   {
    constexpr Weeks weeks1 {12};
    testing::internal::CaptureStdout();
    std::cout << weeks1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Weeks(12)");
   }

 }
