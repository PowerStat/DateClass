/*
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <climits>
#include <utility>
#include <stdexcept>
#include <iostream>
#include "Duration.h"
#include "Days.h"
#include "Months.h"
#include "Years.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(DurationTest, constructor1)
   {
    constexpr Duration duration {Years(0), Months(0), Days(0)};
    ASSERT_EQ(duration.getYears().getYears(), 0);
    ASSERT_EQ(duration.getMonths().getMonths(), 0);
    ASSERT_EQ(duration.getDays().getDays(), 0);
   }


  TEST(DurationTest, constructor2)
   {
    constexpr Duration duration {Years(ULONG_MAX), Months(11), Days(30)};
    ASSERT_EQ(duration.getYears().getYears(), ULONG_MAX);
    ASSERT_EQ(duration.getMonths().getMonths(), 11);
    ASSERT_EQ(duration.getDays().getDays(), 30);
   }


  TEST(DurationTest, constructor3)
   {
    try
     {
      [[maybe_unused]] const Duration duration {Years(0), Months(0), Days(31)};
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      // std::cout << e.what() << std::endl;
      ASSERT_EQ(std::string{"days must be < 31"}.compare(e.what()), 0);
     }
   }


  TEST(DurationTest, constructor4)
   {
    try
     {
      [[maybe_unused]] const Duration duration {Years(ULONG_MAX), Months(12), Days(0)};
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      // std::cout << e.what() << std::endl;
      ASSERT_EQ(std::string{"years must be <= ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(DurationTest, copyConstructor)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {duration1};
    ASSERT_EQ(duration2.getYears().getYears(), 12);
    ASSERT_EQ(duration2.getMonths().getMonths(), 11);
    ASSERT_EQ(duration2.getDays().getDays(), 12);
    ASSERT_TRUE(&duration1 != &duration2);
   }


  TEST(DurationTest, moveConstructor)
   {
    Duration duration1 {Years(12), Months(11), Days(12)};
    const Duration duration2 {std::move(duration1)};
    ASSERT_EQ(duration2.getYears().getYears(), 12);
    ASSERT_EQ(duration2.getMonths().getMonths(), 11);
    ASSERT_EQ(duration2.getDays().getDays(), 12);
   }


  TEST(DurationTest, equalOperator1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_TRUE(duration1 == duration2);
   }


  TEST(DurationTest, equalOperator2)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(18), Months(11), Days(18)};
    ASSERT_FALSE(duration1 == duration2);
   }


  TEST(DurationTest, notEqualOperator1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(18), Months(11), Days(18)};
    ASSERT_TRUE(duration1 != duration2);
   }


  TEST(DurationTest, notEqualOperator2)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_FALSE(duration1 != duration2);
   }


  TEST(DurationTest, smallerOperator1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(18), Months(11), Days(18)};
    ASSERT_TRUE(duration1 < duration2);
   }


  TEST(DurationTest, smallerOperator2)
   {
    constexpr Duration duration1 {Years(18), Months(11), Days(18)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_FALSE(duration1 < duration2);
   }


  TEST(DurationTest, smallerOperator3)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_FALSE(duration1 < duration2);
   }


  TEST(DurationTest, greaterOperator1)
   {
    constexpr Duration duration1 {Years(18), Months(11), Days(18)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_TRUE(duration1 > duration2);
   }


  TEST(DurationTest, greaterOperator2)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(18), Months(11), Days(18)};
    ASSERT_FALSE(duration1 > duration2);
   }


  TEST(DurationTest, greaterOperator3)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_FALSE(duration1 > duration2);
   }


  TEST(DurationTest, smallerEqualOperator1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(18), Months(11), Days(18)};
    ASSERT_TRUE(duration1 <= duration2);
   }


  TEST(DurationTest, smallerEqualOperator2)
   {
    constexpr Duration duration1 {Years(18), Months(11), Days(18)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_FALSE(duration1 <= duration2);
   }


  TEST(DurationTest, smallerEqualOperator3)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_TRUE(duration1 <= duration2);
   }


  TEST(DurationTest, greaterEqualOperator1)
   {
    constexpr Duration duration1 {Years(18), Months(11), Days(18)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_TRUE(duration1 >= duration2);
   }


  TEST(DurationTest, greaterEqualOperator2)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(18), Months(11), Days(18)};
    ASSERT_FALSE(duration1 >= duration2);
   }


  TEST(DurationTest, greaterEqualOperator3)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(12), Months(11), Days(12)};
    ASSERT_TRUE(duration1 >= duration2);
   }


  TEST(DurationTest, plusDuration1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(6), Months(6), Days(6)};
    constexpr Duration newDuration = duration1 + duration2;
    ASSERT_EQ(newDuration.getYears().getYears(), 19);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 5);
    ASSERT_EQ(newDuration.getDays().getDays(), 18);
   }


  TEST(DurationTest, plusDuration2)
   {
    constexpr Duration duration1 {Years(ULONG_MAX), Months(11), Days(30)};
    constexpr Duration duration2 {Years(1), Months(0), Days(1)};
    try
     {
      [[maybe_unused]] const Duration newDuration = duration1 + duration2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      // std::cout << e.what() << std::endl;
      ASSERT_EQ(std::string{"years will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(DurationTest, minusDuration1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(6), Months(6), Days(6)};
    constexpr Duration newDuration = duration1 - duration2;
    ASSERT_EQ(newDuration.getYears().getYears(), 6);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 5);
    ASSERT_EQ(newDuration.getDays().getDays(), 6);
   }


  TEST(DurationTest, minusDuration2)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration duration2 {Years(18), Months(11), Days(18)};
    constexpr Duration newDuration = duration1 - duration2;
    ASSERT_EQ(newDuration.getYears().getYears(), 6);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 0);
    ASSERT_EQ(newDuration.getDays().getDays(), 6);
   }


  TEST(DurationTest, multDuration1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration newDuration = duration1 * 2;
    ASSERT_EQ(newDuration.getYears().getYears(), 25);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 10);
    ASSERT_EQ(newDuration.getDays().getDays(), 24);
   }


  TEST(DurationTest, multDuration2)
   {
    constexpr Duration duration1 {Years(ULONG_MAX), Months(11), Days(30)};
    try
     {
      [[maybe_unused]] const Duration newDuration = duration1 * 2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"years will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(DurationTest, divDuration1)
   {
    constexpr Duration duration1 {Years(12), Months(10), Days(12)};
    constexpr Duration newDuration = duration1 / 2;
    ASSERT_EQ(newDuration.getYears().getYears(), 6);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 5);
    ASSERT_EQ(newDuration.getDays().getDays(), 6);
   }


  TEST(DurationTest, reminderDuration1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Duration newDuration = duration1 % 2;
    ASSERT_EQ(newDuration.getYears().getYears(), 0);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 1);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(DurationTest, plusDays1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Days days1 {Days(6)};
    constexpr Duration newDuration = duration1 + days1;
    ASSERT_EQ(newDuration.getYears().getYears(), 12);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 11);
    ASSERT_EQ(newDuration.getDays().getDays(), 18);
   }


  TEST(DurationTest, plusDays2)
   {
    constexpr Duration duration1 {Years(ULONG_MAX), Months(11), Days(30)};
    constexpr Days days1 {Days(1)};
    try
     {
      [[maybe_unused]] const Duration newDuration = duration1 + days1;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      // std::cout << e.what() << std::endl;
      ASSERT_EQ(std::string{"days must be < 31"}.compare(e.what()), 0);
     }
   }


  TEST(DurationTest, minusDays1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Days days1 {Days(6)};
    constexpr Duration newDuration = duration1 - days1;
    ASSERT_EQ(newDuration.getYears().getYears(), 12);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 11);
    ASSERT_EQ(newDuration.getDays().getDays(), 6);
   }


  TEST(DurationTest, minusDays2)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Days days1 {Days(18)};
    constexpr Duration newDuration = duration1 - days1;
    ASSERT_EQ(newDuration.getYears().getYears(), 12);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 11);
    ASSERT_EQ(newDuration.getDays().getDays(), 6);
   }


  TEST(DurationTest, plusMonths1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Months months1 {Months(6)};
    constexpr Duration newDuration = duration1 + months1;
    ASSERT_EQ(newDuration.getYears().getYears(), 13);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 5);
    ASSERT_EQ(newDuration.getDays().getDays(), 12);
   }


  TEST(DurationTest, plusMonths2)
   {
    constexpr Duration duration1 {Years(ULONG_MAX), Months(11), Days(30)};
    constexpr Months months1 {Months(1)};
    try
     {
      [[maybe_unused]] const Duration newDuration = duration1 + months1;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      // std::cout << e.what() << std::endl;
      ASSERT_EQ(std::string{"years must be <= ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(DurationTest, minusMonths1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Months months1 {Months(6)};
    constexpr Duration newDuration = duration1 - months1;
    ASSERT_EQ(newDuration.getYears().getYears(), 12);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 5);
    ASSERT_EQ(newDuration.getDays().getDays(), 12);
   }


  TEST(DurationTest, minusMonths2)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Months months1 {Months(18)};
    constexpr Duration newDuration = duration1 - months1;
    ASSERT_EQ(newDuration.getYears().getYears(), 11);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 5);
    ASSERT_EQ(newDuration.getDays().getDays(), 12);
   }


  TEST(DurationTest, minusMonths3)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(0)};
    constexpr Months months1 {Months(13)};
    constexpr Duration newDuration = duration1 - months1;
    ASSERT_EQ(newDuration.getYears().getYears(), 11);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 10);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(DurationTest, minusMonths4)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(0)};
    constexpr Months months1 {Months(11)};
    constexpr Duration newDuration = duration1 - months1;
    ASSERT_EQ(newDuration.getYears().getYears(), 12);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 0);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(DurationTest, minusMonths5)
   {
    constexpr Duration duration1 {Years(0), Months(11), Days(0)};
    constexpr Months months1 {Months(12)};
    constexpr Duration newDuration = duration1 - months1;
    ASSERT_EQ(newDuration.getYears().getYears(), 0);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 1);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(DurationTest, minusMonths6)
   {
    constexpr Duration duration1 {Years(0), Months(11), Days(0)};
    constexpr Months months1 {Months(22)};
    constexpr Duration newDuration = duration1 - months1;
    ASSERT_EQ(newDuration.getYears().getYears(), 0);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 11);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(DurationTest, minusMonths7)
   {
    constexpr Duration duration1 {Years(0), Months(11), Days(0)};
    constexpr Months months1 {Months(23)};
    constexpr Duration newDuration = duration1 - months1;
    ASSERT_EQ(newDuration.getYears().getYears(), 1);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 0);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(DurationTest, plusYears1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Years years1 {Years(6)};
    constexpr Duration newDuration = duration1 + years1;
    ASSERT_EQ(newDuration.getYears().getYears(), 18);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 11);
    ASSERT_EQ(newDuration.getDays().getDays(), 12);
   }


  TEST(DurationTest, plusYears2)
   {
    constexpr Duration duration1 {Years(ULONG_MAX), Months(11), Days(30)};
    constexpr Years years1 {Years(1)};
    try
     {
      [[maybe_unused]] const Duration newDuration = duration1 + years1;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      // std::cout << e.what() << std::endl;
      ASSERT_EQ(std::string{"years will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(DurationTest, minusYears1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Years years1 {Years(6)};
    constexpr Duration newDuration = duration1 - years1;
    ASSERT_EQ(newDuration.getYears().getYears(), 6);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 11);
    ASSERT_EQ(newDuration.getDays().getDays(), 12);
   }


  TEST(DurationTest, minusYears2)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Years years1 {Years(12)};
    constexpr Duration newDuration = duration1 - years1;
    ASSERT_EQ(newDuration.getYears().getYears(), 0);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 11);
    ASSERT_EQ(newDuration.getDays().getDays(), 12);
   }


  TEST(DurationTest, minusYears3)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    constexpr Years years1 {Years(13)};
    try
     {
      [[maybe_unused]] const Duration newDuration = duration1 - years1;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      // std::cout << e.what() << std::endl;
      ASSERT_EQ(std::string{"years will be < 0"}.compare(e.what()), 0);
     }
   }


  TEST(DurationTest, coutDuration1)
   {
    constexpr Duration duration1 {Years(12), Months(11), Days(12)};
    testing::internal::CaptureStdout();
    std::cout << duration1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Duration(Years(12), Months(11), Days(12))");
   }

 }
