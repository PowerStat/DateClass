/*
 * Copyright (C) 2020-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <climits>
#include "JulianYear.h"
#include "Years.h"
#include "ScaligerYear.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(JulianYearTest, constructor1)
   {
    constexpr JulianYear year {8};
    ASSERT_EQ(year.getYear(), 8);
   }


  TEST(JulianYearTest, constructor2)
   {
    constexpr JulianYear year {32767};
    ASSERT_EQ(year.getYear(), 32767);
   }


  TEST(JulianYearTest, constructor3)
   {
    try
     {
      [[maybe_unused]] const JulianYear year {7};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year is < 8 or > 32767"}.compare(e.what()), 0);
     }
   }


  TEST(JulianYearTest, constructor4)
   {
    try
     {
      [[maybe_unused]] const JulianYear year {32768};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year is < 8 or > 32767"}.compare(e.what()), 0);
     }
   }


  TEST(JulianYearTest, constructor5)
   {
    constexpr ScaligerYear syear {6295};
    constexpr JulianYear year {syear};
    ASSERT_EQ(year.getYear(), 1582);
   }


  TEST(JulianYearTest, constructor6)
   {
    constexpr ScaligerYear syear {4721};
    constexpr JulianYear year {syear};
    ASSERT_EQ(year.getYear(), 8);
   }


  TEST(JulianYearTest, constructor7)
   {
    constexpr ScaligerYear syear {4720};
    try
     {
      [[maybe_unused]] const JulianYear year {syear};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"syear must be >= 4721"}.compare(e.what()), 0);
     }
   }


  TEST(JulianYearTest, copyConstructor)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {year1};
    ASSERT_EQ(year2.getYear(), 12);
    ASSERT_TRUE(&year1 != &year2);
   }


  TEST(JulianYearTest, moveConstructor)
   {
    JulianYear year1 {12};
    const JulianYear year2 {std::move(year1)};
    ASSERT_EQ(year2.getYear(), 12);
   }


  TEST(JulianYearTest, isLeapYear1)
   {
    constexpr JulianYear year {8};
    ASSERT_TRUE(year.isLeapYear());
   }


  TEST(JulianYearTest, isLeapYear2)
   {
    constexpr JulianYear year {9};
    ASSERT_FALSE(year.isLeapYear());
   }


  TEST(JulianYearTest, getDaysInYear1)
   {
    constexpr JulianYear year {8};
    ASSERT_EQ(year.getDaysInYear().getDays(), 366);
   }


  TEST(JulianYearTest, getDaysInYear2)
   {
    constexpr JulianYear year {9};
    ASSERT_EQ(year.getDaysInYear().getDays(), 365);
   }


  TEST(JulianYearTest, getWeeksInYear1)
   {
    constexpr JulianYear year {8};
    ASSERT_EQ(year.getWeeksInYear().getWeeks(), 52);
   }


  TEST(JulianYearTest, getWeeksInYear2)
   {
    constexpr JulianYear year {11};
    ASSERT_EQ(year.getWeeksInYear().getWeeks(), 53);
   }


  TEST(JulianYearTest, getScaligerYear1)
   {
    constexpr JulianYear year {8};
    ASSERT_EQ(year.getScaligerYear().getYear(), 4721);
   }


  TEST(JulianYearTest, getScaligerYear2)
   {
    constexpr JulianYear year {1582};
    ASSERT_EQ(year.getScaligerYear().getYear(), 6295);
   }


  TEST(JulianYearTest, equalOperator1)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {12};
    ASSERT_TRUE(year1 == year2);
   }


  TEST(JulianYearTest, equalOperator2)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {18};
    ASSERT_FALSE(year1 == year2);
   }


  TEST(JulianYearTest, notEqualOperator1)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {18};
    ASSERT_TRUE(year1 != year2);
   }


  TEST(JulianYearTest, notEqualOperator2)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {12};
    ASSERT_FALSE(year1 != year2);
   }


  TEST(JulianYearTest, smallerOperator1)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {18};
    ASSERT_TRUE(year1 < year2);
   }


  TEST(JulianYearTest, smallerOperator2)
   {
    constexpr JulianYear year1 {18};
    constexpr JulianYear year2 {12};
    ASSERT_FALSE(year1 < year2);
   }


  TEST(JulianYearTest, smallerOperator3)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {12};
    ASSERT_FALSE(year1 < year2);
   }


  TEST(JulianYearTest, greaterOperator1)
   {
    constexpr JulianYear year1 {18};
    constexpr JulianYear year2 {12};
    ASSERT_TRUE(year1 > year2);
   }


  TEST(JulianYearTest, greaterOperator2)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {18};
    ASSERT_FALSE(year1 > year2);
   }


  TEST(JulianYearTest, greaterOperator3)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {12};
    ASSERT_FALSE(year1 > year2);
   }


  TEST(JulianYearTest, smallerEqualOperator1)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {18};
    ASSERT_TRUE(year1 <= year2);
   }


  TEST(JulianYearTest, smallerEqualOperator2)
   {
    constexpr JulianYear year1 {18};
    constexpr JulianYear year2 {12};
    ASSERT_FALSE(year1 <= year2);
   }


  TEST(JulianYearTest, smallerEqualOperator3)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {12};
    ASSERT_TRUE(year1 <= year2);
   }


  TEST(JulianYearTest, greaterEqualOperator1)
   {
    constexpr JulianYear year1 {18};
    constexpr JulianYear year2 {12};
    ASSERT_TRUE(year1 >= year2);
   }


  TEST(JulianYearTest, greaterEqualOperator2)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {18};
    ASSERT_FALSE(year1 >= year2);
   }


  TEST(JulianYearTest, greaterEqualOperator3)
   {
    constexpr JulianYear year1 {12};
    constexpr JulianYear year2 {12};
    ASSERT_TRUE(year1 >= year2);
   }


  TEST(JulianYearTest, plusYears1)
   {
    constexpr JulianYear year {12};
    constexpr Years years {6};
    constexpr JulianYear newYear = year + years;
    ASSERT_EQ(newYear.getYear(), 18);
   }


  TEST(JulianYearTest, plusYears2)
   {
    constexpr JulianYear year {32000};
    constexpr Years years {768};
    try
     {
      [[maybe_unused]] const JulianYear newYear = year + years;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year will be > 32767"}.compare(e.what()), 0);
     }
   }


  TEST(JulianYearTest, plusYears3)
   {
    constexpr JulianYear year {32000};
    constexpr Years years {LONG_MAX};
    try
     {
      [[maybe_unused]] const JulianYear newYear = year + years;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year will be > LONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(JulianYearTest, minusYears1)
   {
    constexpr JulianYear year {18};
    constexpr Years years {6};
    constexpr JulianYear newYear = year - years;
    ASSERT_EQ(newYear.getYear(), 12);
   }


  TEST(JulianYearTest, minusYears2)
   {
    constexpr JulianYear year {12};
    constexpr Years years {5};
    try
     {
      [[maybe_unused]] const JulianYear newYear = year - years;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year will be < 8"}.compare(e.what()), 0);
     }
   }


  TEST(JulianYearTest, minusYears3)
   {
    constexpr JulianYear year {12};
    constexpr Years years {13};
    try
     {
      [[maybe_unused]] const JulianYear newYear = year - years;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year will be < 0"}.compare(e.what()), 0);
     }
   }


  TEST(JulianYearTest, minusYear1)
   {
    constexpr JulianYear year1 {18};
    constexpr JulianYear year2 {8};
    constexpr Years newYears = year1 - year2;
    ASSERT_EQ(newYears.getYears(), 10);
   }


  TEST(JulianYearTest, minusYear2)
   {
    constexpr JulianYear year1 {8};
    constexpr JulianYear year2 {18};
    constexpr Years newYears = year1 - year2;
    ASSERT_EQ(newYears.getYears(), 10);
   }


  TEST(JulianYearTest, coutYear1)
   {
    constexpr JulianYear year1 {12};
    testing::internal::CaptureStdout();
    std::cout << year1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "JulianYear(12)");
   }

 } // namespace DateLib
