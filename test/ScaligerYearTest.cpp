/*
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <climits>
#include "ScaligerYear.h"
#include "Years.h"
#include "JD.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(ScaligerYearTest, constructor1)
   {
    constexpr ScaligerYear syear {4707};
    ASSERT_EQ(syear.getYear(), 4707);
   }


  TEST(ScaligerYearTest, constructor2)
   {
    constexpr ScaligerYear syear {6295};
    ASSERT_EQ(syear.getYear(), 6295);
   }


  TEST(ScaligerYearTest, constructor3)
   {
    try
     {
      [[maybe_unused]] const ScaligerYear year {4706};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year is < 4707 or > 6295"}.compare(e.what()), 0);
     }
   }


  TEST(ScaligerYearTest, constructor4)
   {
    try
     {
      [[maybe_unused]] const ScaligerYear year {6296};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year is < 4707 or > 6295"}.compare(e.what()), 0);
     }
   }


  TEST(ScaligerYearTest, constructor5)
   {
    constexpr JD jd {1718867};
    constexpr ScaligerYear syear {jd};
    ASSERT_EQ(syear.getJD().getJD(), 1718867);
   }


  TEST(ScaligerYearTest, constructor6)
   {
    constexpr JD jd {2298884};
    constexpr ScaligerYear syear {jd};
    ASSERT_EQ(syear.getJD().getJD(), 2298884);
   }


  TEST(ScaligerYearTest, constructor7)
   {
    constexpr JD jd {1718866};
    try
     {
      [[maybe_unused]] const ScaligerYear year {jd};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"jd is < 1718867 or > 2298884"}.compare(e.what()), 0);
     }
   }


  TEST(ScaligerYearTest, constructor8)
   {
    constexpr JD jd {2298885};
    try
     {
      [[maybe_unused]] const ScaligerYear year {jd};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"jd is < 1718867 or > 2298884"}.compare(e.what()), 0);
     }
   }


  TEST(ScaligerYearTest, copyConstructor)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {year1};
    ASSERT_EQ(year2.getYear(), 4707);
    ASSERT_TRUE(&year1 != &year2);
   }


  TEST(ScaligerYearTest, moveConstructor)
   {
    ScaligerYear year1 {4707};
    const ScaligerYear year2 {std::move(year1)};
    ASSERT_EQ(year2.getYear(), 4707);
   }


  TEST(ScaligerYearTest, getJD1)
   {
    constexpr ScaligerYear year {4721};
    constexpr JD jd = year.getJD();
    ASSERT_EQ(jd.getJD(), 1723980);
   }


  TEST(ScaligerYearTest, equalOperator1)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4707};
    ASSERT_TRUE(year1 == year2);
   }


  TEST(ScaligerYearTest, equalOperator2)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4708};
    ASSERT_FALSE(year1 == year2);
   }


  TEST(ScaligerYearTest, notEqualOperator1)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4708};
    ASSERT_TRUE(year1 != year2);
   }


  TEST(ScaligerYearTest, notEqualOperator2)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4707};
    ASSERT_FALSE(year1 != year2);
   }


  TEST(ScaligerYearTest, smallerOperator1)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4708};
    ASSERT_TRUE(year1 < year2);
   }


  TEST(ScaligerYearTest, smallerOperator2)
   {
    constexpr ScaligerYear year1 {4708};
    constexpr ScaligerYear year2 {4707};
    ASSERT_FALSE(year1 < year2);
   }


  TEST(ScaligerYearTest, smallerOperator3)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4707};
    ASSERT_FALSE(year1 < year2);
   }


  TEST(ScaligerYearTest, greaterOperator1)
   {
    constexpr ScaligerYear year1 {4708};
    constexpr ScaligerYear year2 {4707};
    ASSERT_TRUE(year1 > year2);
   }


  TEST(ScaligerYearTest, greaterOperator2)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4708};
    ASSERT_FALSE(year1 > year2);
   }


  TEST(ScaligerYearTest, greaterOperator3)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4707};
    ASSERT_FALSE(year1 > year2);
   }


  TEST(ScaligerYearTest, smallerEqualOperator1)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4708};
    ASSERT_TRUE(year1 <= year2);
   }


  TEST(ScaligerYearTest, smallerEqualOperator2)
   {
    constexpr ScaligerYear year1 {4708};
    constexpr ScaligerYear year2 {4707};
    ASSERT_FALSE(year1 <= year2);
   }


  TEST(ScaligerYearTest, smallerEqualOperator3)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4707};
    ASSERT_TRUE(year1 <= year2);
   }


  TEST(ScaligerYearTest, greaterEqualOperator1)
   {
    constexpr ScaligerYear year1 {4708};
    constexpr ScaligerYear year2 {4707};
    ASSERT_TRUE(year1 >= year2);
   }


  TEST(ScaligerYearTest, greaterEqualOperator2)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4708};
    ASSERT_FALSE(year1 >= year2);
   }


  TEST(ScaligerYearTest, greaterEqualOperator3)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4707};
    ASSERT_TRUE(year1 >= year2);
   }


  TEST(ScaligerYearTest, plusYears1)
   {
    constexpr ScaligerYear year {4707};
    constexpr Years years {6};
    constexpr ScaligerYear newYear = year + years;
    ASSERT_EQ(newYear.getYear(), 4713);
   }


  TEST(ScaligerYearTest, plusYears2)
   {
    constexpr ScaligerYear year {6295};
    constexpr Years years {1};
    try
     {
      [[maybe_unused]] const ScaligerYear newYear = year + years;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year will be > 6295"}.compare(e.what()), 0);
     }
   }


  TEST(ScaligerYearTest, plusYears3)
   {
    constexpr ScaligerYear year {6295};
    constexpr Years years {LONG_MAX};
    try
     {
      [[maybe_unused]] const ScaligerYear newYear = year + years;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year will be > LONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(ScaligerYearTest, minusYears1)
   {
    constexpr ScaligerYear year {4713};
    constexpr Years years {6};
    constexpr ScaligerYear newYear = year - years;
    ASSERT_EQ(newYear.getYear(), 4707);
   }


  TEST(ScaligerYearTest, minusYears2)
   {
    constexpr ScaligerYear year {4707};
    constexpr Years years {1};
    try
     {
      [[maybe_unused]] const ScaligerYear newYear = year - years;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year will be < 4707"}.compare(e.what()), 0);
     }
   }


  TEST(ScaligerYearTest, minusYears3)
   {
    constexpr ScaligerYear year {4707};
    constexpr Years years {4708};
    try
     {
      [[maybe_unused]] const ScaligerYear newYear = year - years;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"year will be < 0"}.compare(e.what()), 0);
     }
   }


  TEST(ScaligerYearTest, minusYear1)
   {
    constexpr ScaligerYear year1 {4713};
    constexpr ScaligerYear year2 {4707};
    constexpr Years newYears = year1 - year2;
    ASSERT_EQ(newYears.getYears(), 6);
   }


  TEST(ScaligerYearTest, minusYear2)
   {
    constexpr ScaligerYear year1 {4707};
    constexpr ScaligerYear year2 {4713};
    constexpr Years newYears = year1 - year2;
    ASSERT_EQ(newYears.getYears(), 6);
   }


  TEST(ScaligerYearTest, coutYear1)
   {
    constexpr ScaligerYear year1 {4707};
    testing::internal::CaptureStdout();
    std::cout << year1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "ScaligerYear(4707)");
   }

 } // namespace DateLib
