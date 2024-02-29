/*
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <climits>
#include <utility>
#include <stdexcept>
#include <iostream>
#include "JD.h"
#include "Days.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(JDTest, constructor1)
   {
    constexpr JD jd {0};
    ASSERT_EQ(jd.getJD(), 0);
   }


  TEST(JDTest, constructor2)
   {
    constexpr JD jd {ULONG_MAX};
    ASSERT_EQ(jd.getJD(), ULONG_MAX);
   }


  TEST(JDTest, copyConstructor)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {jd1};
    ASSERT_EQ(jd2.getJD(), 12);
    ASSERT_TRUE(&jd1 != &jd2);
   }


  TEST(JDTest, moveConstructor)
   {
    JD jd1 {12};
    const JD jd2 {std::move(jd1)};
    ASSERT_EQ(jd2.getJD(), 12);
   }


  TEST(JDTest, equalOperator1)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {12};
    ASSERT_TRUE(jd1 == jd2);
   }


  TEST(JDTest, equalOperator2)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {18};
    ASSERT_FALSE(jd1 == jd2);
   }


  TEST(JDTest, notEqualOperator1)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {18};
    ASSERT_TRUE(jd1 != jd2);
   }


  TEST(JDTest, notEqualOperator2)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {12};
    ASSERT_FALSE(jd1 != jd2);
   }


  TEST(JDTest, smallerOperator1)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {18};
    ASSERT_TRUE(jd1 < jd2);
   }


  TEST(JDTest, smallerOperator2)
   {
    constexpr JD jd1 {18};
    constexpr JD jd2 {12};
    ASSERT_FALSE(jd1 < jd2);
   }


  TEST(JDTest, smallerOperator3)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {12};
    ASSERT_FALSE(jd1 < jd2);
   }


  TEST(JDTest, greaterOperator1)
   {
    constexpr JD jd1 {18};
    constexpr JD jd2 {12};
    ASSERT_TRUE(jd1 > jd2);
   }


  TEST(JDTest, greaterOperator2)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {18};
    ASSERT_FALSE(jd1 > jd2);
   }


  TEST(JDTest, greaterOperator3)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {12};
    ASSERT_FALSE(jd1 > jd2);
   }


  TEST(JDTest, smallerEqualOperator1)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {18};
    ASSERT_TRUE(jd1 <= jd2);
   }


  TEST(JDTest, smallerEqualOperator2)
   {
    constexpr JD jd1 {18};
    constexpr JD jd2 {12};
    ASSERT_FALSE(jd1 <= jd2);
   }


  TEST(JDTest, smallerEqualOperator3)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {12};
    ASSERT_TRUE(jd1 <= jd2);
   }


  TEST(JDTest, greaterEqualOperator1)
   {
    constexpr JD jd1 {18};
    constexpr JD jd2 {12};
    ASSERT_TRUE(jd1 >= jd2);
   }


  TEST(JDTest, greaterEqualOperator2)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {18};
    ASSERT_FALSE(jd1 >= jd2);
   }


  TEST(JDTest, greaterEqualOperator3)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {12};
    ASSERT_TRUE(jd1 >= jd2);
   }


  TEST(JDTest, plusJDDays1)
   {
    constexpr JD jd {12};
    constexpr Days days {6};
    constexpr JD newJD = jd + days;
    ASSERT_EQ(newJD.getJD(), 18);
   }


  TEST(JDTest, plusJDDays2)
   {
    constexpr JD jd {ULONG_MAX};
    constexpr Days days {20};
    try
     {
      [[maybe_unused]] const JD newJD = jd + days;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"JD will be > ULONG_MAX"}.compare(e.what()), 0);
     }
   }


  TEST(JDTest, minusJDDays1)
   {
    constexpr JD jd {12};
    constexpr Days days {6};
    constexpr JD newJD = jd - days;
    ASSERT_EQ(newJD.getJD(), 6);
   }


  TEST(JDTest, minusJDDays2)
   {
    constexpr JD jd {12};
    constexpr Days days {18};
    try
     {
      [[maybe_unused]] const JD newJD = jd - days;
      FAIL();
     }
    catch(const std::out_of_range& e)
     {
      ASSERT_EQ(std::string{"JD will be < 0"}.compare(e.what()), 0);
     }
   }


  TEST(JDTest, minusJDJD1)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {6};
    constexpr Days newDays = jd1 - jd2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(JDTest, minusJDJD2)
   {
    constexpr JD jd1 {12};
    constexpr JD jd2 {18};
    constexpr Days newDays = jd1 - jd2;
    ASSERT_EQ(newDays.getDays(), 6);
   }


  TEST(JDTest, coutJD1)
   {
    constexpr JD jd1 {12};
    testing::internal::CaptureStdout();
    std::cout << jd1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "JD(12)");
   }

 }
