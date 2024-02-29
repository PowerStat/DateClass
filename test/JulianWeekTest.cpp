/*
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */

#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <utility>
#include <iostream>
#include "JulianWeek.h"
#include "JulianYear.h"
#include "Weeks.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(JulianWeekTest, constructor1)
   {
    constexpr JulianWeek week {1};
    ASSERT_EQ(week.getWeek(), 1);
   }


  TEST(JulianWeekTest, constructor2)
   {
    constexpr JulianWeek week {53};
    ASSERT_EQ(week.getWeek(), 53);
   }


 TEST(JulianWeekTest, constructor3)
  {
   try
    {
     [[maybe_unused]] const JulianWeek week {0};
     FAIL();
    }
   catch (const std::out_of_range& e)
    {
     ASSERT_EQ(std::string{"week is < 1 or > 53"}.compare(e.what()), 0);
    }
  }


 TEST(JulianWeekTest, constructor4)
  {
   try
    {
     [[maybe_unused]] const JulianWeek week {54};
     FAIL();
    }
   catch (const std::out_of_range& e)
    {
     ASSERT_EQ(std::string{"week is < 1 or > 53"}.compare(e.what()), 0);
    }
  }


 TEST(JulianWeekTest, constructor5)
  {
   constexpr JulianWeek week {53, JulianYear(11)};
   ASSERT_EQ(week.getWeek(), 53);
  }


 TEST(JulianWeekTest, constructor6)
  {
   try
    {
     [[maybe_unused]] const JulianWeek week {53, JulianYear(8)};
     FAIL();
    }
   catch (const std::out_of_range& e)
    {
     ASSERT_EQ(std::string{"week is < 1 or > 52"}.compare(e.what()), 0);
    }
  }


 TEST(JulianWeekTest, copyConstructor)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {week1};
   ASSERT_EQ(week2.getWeek(), 12);
   ASSERT_TRUE(&week1 != &week2);
  }


  TEST(JulianWeekTest, moveConstructor)
   {
    JulianWeek week1 {12};
    const JulianWeek week2 {std::move(week1)};
    ASSERT_EQ(week2.getWeek(), 12);
   }


 TEST(JulianWeekTest, getMaxWeeks1)
  {
   constexpr JulianWeek week {53, JulianYear(11)};
   ASSERT_EQ(week.getMaxWeeks(), 53);
  }


 TEST(JulianWeekTest, getMaxWeeks2)
  {
   constexpr JulianWeek week {52, JulianYear(8)};
   ASSERT_EQ(week.getMaxWeeks(), 52);
  }


 TEST(JulianWeekTest, equalOperator1)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {12};
   ASSERT_TRUE(week1 == week2);
  }


 TEST(JulianWeekTest, equalOperator2)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {18};
   ASSERT_FALSE(week1 == week2);
  }


 TEST(JulianWeekTest, notEqualOperator1)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {18};
   ASSERT_TRUE(week1 != week2);
  }


 TEST(JulianWeekTest, notEqualOperator2)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {12};
   ASSERT_FALSE(week1 != week2);
  }


 TEST(JulianWeekTest, smallerOperator1)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {18};
   ASSERT_TRUE(week1 < week2);
  }


 TEST(JulianWeekTest, smallerOperator2)
  {
   constexpr JulianWeek week1 {18};
   constexpr JulianWeek week2 {12};
   ASSERT_FALSE(week1 < week2);
  }


 TEST(JulianWeekTest, smallerOperator3)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {12};
   ASSERT_FALSE(week1 < week2);
  }


 TEST(JulianWeekTest, greaterOperator1)
  {
   constexpr JulianWeek week1 {18};
   constexpr JulianWeek week2 {12};
   ASSERT_TRUE(week1 > week2);
  }


 TEST(JulianWeekTest, greaterOperator2)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {18};
   ASSERT_FALSE(week1 > week2);
  }


 TEST(JulianWeekTest, greaterOperator3)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {12};
   ASSERT_FALSE(week1 > week2);
  }


 TEST(JulianWeekTest, smallerEqualOperator1)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {18};
   ASSERT_TRUE(week1 <= week2);
  }


 TEST(JulianWeekTest, smallerEqualOperator2)
  {
   constexpr JulianWeek week1 {18};
   constexpr JulianWeek week2 {12};
   ASSERT_FALSE(week1 <= week2);
  }


 TEST(JulianWeekTest, smallerEqualOperator3)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {12};
   ASSERT_TRUE(week1 <= week2);
  }


 TEST(JulianWeekTest, greaterEqualOperator1)
  {
   constexpr JulianWeek week1 {18};
   constexpr JulianWeek week2 {12};
   ASSERT_TRUE(week1 >= week2);
  }


 TEST(JulianWeekTest, greaterEqualOperator2)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {18};
   ASSERT_FALSE(week1 >= week2);
  }


 TEST(JulianWeekTest, greaterEqualOperator3)
  {
   constexpr JulianWeek week1 {12};
   constexpr JulianWeek week2 {12};
   ASSERT_TRUE(week1 >= week2);
  }


 TEST(JulianWeekTest, plusWeeks1)
  {
   constexpr JulianWeek week {12};
   constexpr Weeks weeks {6};
   constexpr JulianWeek newWeek = week + weeks;
   ASSERT_EQ(newWeek.getWeek(), 18);
  }


 TEST(JulianWeekTest, plusWeeks2)
  {
   constexpr JulianWeek week {12};
   constexpr Weeks weeks {42};
   try
    {
     [[maybe_unused]] const JulianWeek newWeek = week + weeks;
     FAIL();
    }
   catch(const std::out_of_range& e)
    {
     ASSERT_EQ(std::string{"week will be > 53"}.compare(e.what()), 0);
    }
  }


 TEST(JulianWeekTest, minusWeeks1)
  {
   constexpr JulianWeek week {12};
   constexpr Weeks weeks {6};
   constexpr JulianWeek newWeek = week - weeks;
   ASSERT_EQ(newWeek.getWeek(), 6);
  }


 TEST(JulianWeekTest, minusWeeks2)
  {
   constexpr JulianWeek week {12};
   constexpr Weeks weeks {18};
   try
    {
     [[maybe_unused]] const JulianWeek newWeek = week - weeks;
     FAIL();
    }
   catch(const std::out_of_range& e)
    {
     ASSERT_EQ(std::string("week will be < 1").compare(e.what()), 0);
    }
  }


  TEST(JulianWeekTest, minusWeek1)
   {
    constexpr JulianWeek week1 {12};
    constexpr JulianWeek week2 {6};
    constexpr Weeks newWeeks = week1 - week2;
    ASSERT_EQ(newWeeks.getWeeks(), 6);
   }


  TEST(JulianWeekTest, minusWeek2)
   {
    constexpr JulianWeek week1 {6};
    constexpr JulianWeek week2 {12};
    constexpr Weeks newWeeks = week1 - week2;
    ASSERT_EQ(newWeeks.getWeeks(), 6);
   }


  TEST(JulianWeekTest, coutWeek1)
   {
    constexpr JulianWeek week1 {12};
    testing::internal::CaptureStdout();
    std::cout << week1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "JulianWeek(12)");
   }

 } // namespace
