/*
 * Copyright (C) 2020-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <string>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "Days.h"
#include "JulianDay.h"
#include "JulianMonth.h"
#include "JulianYear.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(JulianDayTest, constructor1)
   {
    constexpr JulianDay day {1};
    ASSERT_EQ(day.getDay(), 1);
   }


  TEST(JulianDayTest, constructor2)
   {
    constexpr JulianDay day {31};
    ASSERT_EQ(day.getDay(), 31);
   }


  TEST(JulianDayTest, constructor3)
   {
    try
     {
      [[maybe_unused]] const JulianDay day {0};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"day is < 1 or > 31"}.compare(e.what()), 0);
     }
   }


  TEST(JulianDayTest, constructor4)
   {
    try
     {
      [[maybe_unused]] const JulianDay day {32};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"day is < 1 or > 31"}.compare(e.what()), 0);
     }
   }


  TEST(JulianDayTest, constructor5)
   {
    constexpr JulianDay day {JulianMonth(1), 31};
    ASSERT_EQ(day.getDay(), 31);
   }


  TEST(JulianDayTest, constructor6)
   {
    try
     {
      [[maybe_unused]] const JulianDay day {JulianMonth(1), 32};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"day is < 1 or > 31"}.compare(e.what()), 0);
     }
   }


  TEST(JulianDayTest, constructor7)
   {
    constexpr JulianDay day {JulianMonth(4), 30};
    ASSERT_EQ(day.getDay(), 30);
   }


  TEST(JulianDayTest, constructor8)
   {
    try
     {
      [[maybe_unused]] const JulianDay day {JulianMonth(4), 31};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string("day is < 1 or > 30").compare(e.what()), 0);
     }
   }


  TEST(JulianDayTest, constructor9)
   {
    constexpr JulianDay day {JulianMonth(2), 28};
    ASSERT_EQ(day.getDay(), 28);
   }


  TEST(JulianDayTest, constructor10)
   {
    constexpr JulianDay day {JulianMonth(JulianYear(8), 2), 29};
    ASSERT_EQ(day.getDay(), 29);
   }


  TEST(JulianDayTest, constructor11)
   {
    try
     {
      [[maybe_unused]] const JulianDay day {JulianMonth(JulianYear(9), 2), 29};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string("day is < 1 or > 28").compare(e.what()), 0);
     }
   }


  TEST(JulianDayTest, copyConstructor)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {day1};
    ASSERT_EQ(day2.getDay(), 12);
    ASSERT_TRUE(&day1 != &day2);
   }


  TEST(JulianDayTest, moveConstructor)
   {
    JulianDay day1 {12};
    const JulianDay day2 {std::move(day1)};
    ASSERT_EQ(day2.getDay(), 12);
   }


  TEST(JulianDayTest, equalOperator1)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {12};
    ASSERT_TRUE(day1 == day2);
   }


  TEST(JulianDayTest, equalOperator2)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {18};
    ASSERT_FALSE(day1 == day2);
   }


  TEST(JulianDayTest, notEqualOperator1)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {18};
    ASSERT_TRUE(day1 != day2);
   }


  TEST(JulianDayTest, notEqualOperator2)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {12};
    ASSERT_FALSE(day1 != day2);
   }


  TEST(JulianDayTest, smallerOperator1)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {18};
    ASSERT_TRUE(day1 < day2);
   }


  TEST(JulianDayTest, smallerOperator2)
   {
    constexpr JulianDay day1 {18};
    constexpr JulianDay day2 {12};
    ASSERT_FALSE(day1 < day2);
   }


  TEST(JulianDayTest, smallerOperator3)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {12};
    ASSERT_FALSE(day1 < day2);
   }


  TEST(JulianDayTest, greaterOperator1)
   {
    constexpr JulianDay day1 {18};
    constexpr JulianDay day2 {12};
    ASSERT_TRUE(day1 > day2);
   }


  TEST(JulianDayTest, greaterOperator2)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {18};
    ASSERT_FALSE(day1 > day2);
   }


  TEST(JulianDayTest, greaterOperator3)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {12};
    ASSERT_FALSE(day1 > day2);
   }


  TEST(JulianDayTest, smallerEqualOperator1)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {18};
    ASSERT_TRUE(day1 <= day2);
   }


  TEST(JulianDayTest, smallerEqualOperator2)
   {
    constexpr JulianDay day1 {18};
    constexpr JulianDay day2 {12};
    ASSERT_FALSE(day1 <= day2);
   }


  TEST(JulianDayTest, smallerEqualOperator3)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {12};
    ASSERT_TRUE(day1 <= day2);
   }


  TEST(JulianDayTest, greaterEqualOperator1)
   {
    constexpr JulianDay day1 {18};
    constexpr JulianDay day2 {12};
    ASSERT_TRUE(day1 >= day2);
   }


  TEST(JulianDayTest, greaterEqualOperator2)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {18};
    ASSERT_FALSE(day1 >= day2);
   }


  TEST(JulianDayTest, greaterEqualOperator3)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {12};
    ASSERT_TRUE(day1 >= day2);
   }


  TEST(JulianDayTest, plusDays1)
   {
    constexpr JulianDay day {12};
    constexpr Days days {6};
    constexpr JulianDay newDay = day + days;
    ASSERT_EQ(newDay.getDay(), 18);
   }


  TEST(JulianDayTest, plusDays2)
   {
    constexpr JulianDay day {12};
    constexpr Days days {20};
    try
     {
      [[maybe_unused]] const JulianDay newDay = day + days;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string("day will be > 31").compare(e.what()), 0);
     }
   }


  TEST(JulianDayTest, minusDays1)
   {
    constexpr JulianDay day {12};
    constexpr Days days {6};
    constexpr JulianDay newDay = day - days;
    ASSERT_EQ(newDay.getDay(), 6);
   }


  TEST(JulianDayTest, minusDays2)
   {
    constexpr JulianDay day {12};
    constexpr Days days {18};
    try
     {
      [[maybe_unused]] const JulianDay newDay = day - days;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"day will be < 1"}.compare(e.what()), 0);
     }
   }


  TEST(JulianDayTest, minusDay1)
   {
    constexpr JulianDay day1 {12};
    constexpr JulianDay day2 {6};
    constexpr Days newDays = day1 - day2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(JulianDayTest, minusDay2)
   {
    constexpr JulianDay day1 {6};
    constexpr JulianDay day2 {12};
    constexpr Days newDays = day1 - day2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(JulianDayTest, coutDay1)
   {
    constexpr JulianDay day1 {12};
    testing::internal::CaptureStdout();
    std::cout << day1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "JulianDay(12)");
   }

 }
