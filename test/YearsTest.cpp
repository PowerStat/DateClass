/*
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <climits>
#include "Years.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(YearsTest, constructor1)
   {
    constexpr Years years {0};
    ASSERT_EQ(years.getYears(), 0);
   }


  TEST(YearsTest, constructor2)
   {
    constexpr Years years {ULONG_MAX};
    ASSERT_EQ(years.getYears(), ULONG_MAX);
   }


  TEST(YearsTest, copyConstructor)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {years1};
    ASSERT_EQ(years2.getYears(), 12);
    ASSERT_TRUE(&years1 != &years2);
   }


  TEST(YearsTest, moveConstructor)
   {
    Years years1 {12};
    const Years years2 {std::move(years1)};
    ASSERT_EQ(years2.getYears(), 12);
   }


  TEST(YearsTest, equalOperator1)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {12};
    ASSERT_TRUE(years1 == years2);
   }


  TEST(YearsTest, equalOperator2)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {18};
    ASSERT_FALSE(years1 == years2);
   }


  TEST(YearsTest, notEqualOperator1)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {18};
    ASSERT_TRUE(years1 != years2);
   }


  TEST(YearsTest, notEqualOperator2)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {12};
    ASSERT_FALSE(years1 != years2);
   }


  TEST(YearsTest, smallerOperator1)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {18};
    ASSERT_TRUE(years1 < years2);
   }


  TEST(YearsTest, smallerOperator2)
   {
    constexpr Years years1 {18};
    constexpr Years years2 {12};
    ASSERT_FALSE(years1 < years2);
   }


  TEST(YearsTest, smallerOperator3)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {12};
    ASSERT_FALSE(years1 < years2);
   }


  TEST(YearsTest, greaterOperator1)
   {
    constexpr Years years1 {18};
    constexpr Years years2 {12};
    ASSERT_TRUE(years1 > years2);
   }


  TEST(YearsTest, greaterOperator2)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {18};
    ASSERT_FALSE(years1 > years2);
   }


  TEST(YearsTest, greaterOperator3)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {12};
    ASSERT_FALSE(years1 > years2);
   }


  TEST(YearsTest, smallerEqualOperator1)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {18};
    ASSERT_TRUE(years1 <= years2);
   }


  TEST(YearsTest, smallerEqualOperator2)
   {
    constexpr Years years1 {18};
    constexpr Years years2 {12};
    ASSERT_FALSE(years1 <= years2);
   }


  TEST(YearsTest, smallerEqualOperator3)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {12};
    ASSERT_TRUE(years1 <= years2);
   }


  TEST(YearsTest, greaterEqualOperator1)
   {
    constexpr Years years1 {18};
    constexpr Years years2 {12};
    ASSERT_TRUE(years1 >= years2);
   }


  TEST(YearsTest, greaterEqualOperator2)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {18};
    ASSERT_FALSE(years1 >= years2);
   }


  TEST(YearsTest, greaterEqualOperator3)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {12};
    ASSERT_TRUE(years1 >= years2);
   }


  TEST(YearsTest, plusYears1)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {6};
    constexpr Years newYears = years1 + years2;
    ASSERT_EQ(newYears.getYears(), 18);
   }


  TEST(YearsTest, plusYears2)
   {
    constexpr Years years1 {ULONG_MAX};
    constexpr Years years2 {20};
    try
     {
      [[maybe_unused]] const Years newDay = years1 + years2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"years will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(YearsTest, minusYears1)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {6};
    constexpr Years newYears = years1 - years2;
    ASSERT_EQ(newYears.getYears(), 6);
   }


  TEST(YearsTest, minusYears2)
   {
    constexpr Years years1 {12};
    constexpr Years years2 {18};
    constexpr Years newYears = years1 - years2;
    ASSERT_EQ(newYears.getYears(), 6);
   }


  TEST(YearsTest, multYears1)
   {
    constexpr Years years1 {12};
    constexpr Years newYears = years1 * 2;
    ASSERT_EQ(newYears.getYears(), 24);
   }


  TEST(YearsTest, multYears2)
   {
    constexpr Years years1 {ULONG_MAX};
    try
     {
      [[maybe_unused]] const Years newYear = years1 * 2;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"years will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(YearsTest, divYears1)
   {
    constexpr Years years1 {12};
    constexpr Years newYears = years1 / 2;
    ASSERT_EQ(newYears.getYears(), 6);
   }


  TEST(DaysTest, divYears2)
   {
    constexpr Years years1 {12};
    try
     {
      [[maybe_unused]] const Years newYears = years1 / 0;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"Division by zero"}.compare(e.what()), 0);
     }
   }


  TEST(YearsTest, reminderYears1)
   {
    constexpr Years years1 {12};
    constexpr Years newYears = years1 % 2;
    ASSERT_EQ(newYears.getYears(), 0);
   }


  TEST(DaysTest, reminderYears2)
   {
    constexpr Years years1 {12};
    try
     {
      [[maybe_unused]] const Years newYears = years1 % 0;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"Division by zero"}.compare(e.what()), 0);
     }
   }


  TEST(YearsTest, coutYears1)
   {
    constexpr Years years1 {12};
    testing::internal::CaptureStdout();
    std::cout << years1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Years(12)");
   }

 }
