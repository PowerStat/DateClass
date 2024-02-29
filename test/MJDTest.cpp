/*
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <climits>
#include "MJD.h"
#include "Days.h"
#include "JD.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(MJDTest, constructor1)
   {
    constexpr MJD mjd {0};
    ASSERT_EQ(mjd.getMJD(), 0);
   }


  TEST(MJDTest, constructor2)
   {
    constexpr MJD mjd {ULONG_MAX};
    ASSERT_EQ(mjd.getMJD(), ULONG_MAX);
   }


  TEST(MJDTest, constructor3)
   {
    constexpr JD jd {2400001UL};
    constexpr MJD mjd {jd};
    ASSERT_EQ(mjd.getMJD(), 0);
   }


  TEST(MJDTest, constructor4)
   {
    constexpr JD jd {2400000UL};
    try
     {
      [[maybe_unused]] const MJD mjd {jd};
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"JD must be >= 2400001"}.compare(e.what()), 0);
     }
   }


  TEST(MJDTest, copyConstructor)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {mjd1};
    ASSERT_EQ(mjd2.getMJD(), 12);
    ASSERT_TRUE(&mjd1 != &mjd2);
   }


  TEST(MJDTest, moveConstructor)
   {
    MJD mjd1 {12};
    const MJD mjd2 {std::move(mjd1)};
    ASSERT_EQ(mjd2.getMJD(), 12);
   }


  TEST(MJDTest, getMJD)
   {
    constexpr MJD mjd {12};
    ASSERT_EQ(mjd.getMJD(), 12);
   }


  TEST(MJDTest, getJD1)
   {
    constexpr MJD mjd {0};
    ASSERT_EQ(mjd.getJD().getJD(), 2400001);
   }


  TEST(MJDTest, getJD2)
   {
    constexpr MJD mjd {ULONG_MAX};
    try
     {
      [[maybe_unused]] const JD jd {mjd.getJD()};
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"MJD must be < ULONG_MAX - 2400001"}.compare(e.what()), 0);
     }
   }


  TEST(MJDTest, equalOperator1)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {12};
    ASSERT_TRUE(mjd1 == mjd2);
   }


  TEST(MJDTest, equalOperator2)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {18};
    ASSERT_FALSE(mjd1 == mjd2);
   }


  TEST(MJDTest, notEqualOperator1)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {18};
    ASSERT_TRUE(mjd1 != mjd2);
   }


  TEST(MJDTest, notEqualOperator2)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {12};
    ASSERT_FALSE(mjd1 != mjd2);
   }


  TEST(MJDTest, smallerOperator1)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {18};
    ASSERT_TRUE(mjd1 < mjd2);
   }


  TEST(MJDTest, smallerOperator2)
   {
    constexpr MJD mjd1 {18};
    constexpr MJD mjd2 {12};
    ASSERT_FALSE(mjd1 < mjd2);
   }


  TEST(MJDTest, smallerOperator3)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {12};
    ASSERT_FALSE(mjd1 < mjd2);
   }


  TEST(MJDTest, greaterOperator1)
   {
    constexpr MJD mjd1 {18};
    constexpr MJD mjd2 {12};
    ASSERT_TRUE(mjd1 > mjd2);
   }


  TEST(MJDTest, greaterOperator2)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {18};
    ASSERT_FALSE(mjd1 > mjd2);
   }


  TEST(MJDTest, greaterOperator3)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {12};
    ASSERT_FALSE(mjd1 > mjd2);
   }


  TEST(MJDTest, smallerEqualOperator1)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {18};
    ASSERT_TRUE(mjd1 <= mjd2);
   }


  TEST(MJDTest, smallerEqualOperator2)
   {
    constexpr MJD mjd1 {18};
    constexpr MJD mjd2 {12};
    ASSERT_FALSE(mjd1 <= mjd2);
   }


  TEST(MJDTest, smallerEqualOperator3)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {12};
    ASSERT_TRUE(mjd1 <= mjd2);
   }


  TEST(MJDTest, greaterEqualOperator1)
   {
    constexpr MJD mjd1 {18};
    constexpr MJD mjd2 {12};
    ASSERT_TRUE(mjd1 >= mjd2);
   }


  TEST(MJDTest, greaterEqualOperator2)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {18};
    ASSERT_FALSE(mjd1 >= mjd2);
   }


  TEST(MJDTest, greaterEqualOperator3)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {12};
    ASSERT_TRUE(mjd1 >= mjd2);
   }


  TEST(MJDTest, plusMJDDays1)
   {
    constexpr MJD mjd {12};
    constexpr Days days {6};
    constexpr MJD newMJD = mjd + days;
    ASSERT_EQ(newMJD.getMJD(), 18);
   }


  TEST(MJDTest, plusMJDDays2)
   {
    constexpr MJD mjd {ULONG_MAX};
    constexpr Days days {20};
    try
     {
      [[maybe_unused]] const MJD newMJD = mjd + days;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"MJD will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(MJDTest, minusMJDDays1)
   {
    constexpr MJD mjd {12};
    constexpr Days days {6};
    constexpr MJD newMJD = mjd - days;
    ASSERT_EQ(newMJD.getMJD(), 6);
   }


  TEST(MJDTest, minusMJDDays2)
   {
    constexpr MJD mjd {12};
    constexpr Days days {18};
    try
     {
      [[maybe_unused]] const MJD newMJD = mjd - days;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"MJD will be < 0"}.compare(e.what()), 0);
     }
   }


  TEST(MJDTest, minusMJDMJD1)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {6};
    constexpr Days newDays = mjd1 - mjd2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(MJDTest, minusMJDMJD2)
   {
    constexpr MJD mjd1 {12};
    constexpr MJD mjd2 {18};
    constexpr Days newDays = mjd1 - mjd2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(MJDTest, coutJD1)
   {
    constexpr MJD mjd1 {12};
    testing::internal::CaptureStdout();
    std::cout << mjd1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "MJD(12)");
   }

 }
