/*
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "Weekdays.h"
#include "Days.h"

using namespace de::powerstat::datelib;


namespace
 {
  TEST(WeekdaysTest, enum1)
   {
    ASSERT_EQ(static_cast<unsigned short>(Weekdays::Monday), 1);
    ASSERT_EQ(static_cast<unsigned short>(Weekdays::Tuesday), 2);
    ASSERT_EQ(static_cast<unsigned short>(Weekdays::Wednesday), 3);
    ASSERT_EQ(static_cast<unsigned short>(Weekdays::Thursday), 4);
    ASSERT_EQ(static_cast<unsigned short>(Weekdays::Friday), 5);
    ASSERT_EQ(static_cast<unsigned short>(Weekdays::Saturday), 6);
    ASSERT_EQ(static_cast<unsigned short>(Weekdays::Sunday), 7);
   }


  TEST(WeekdaysTest, equal1)
   {
    ASSERT_TRUE(Weekdays::Monday == Weekdays::Monday);
   }


  TEST(WeekdaysTest, notequal1)
   {
    ASSERT_TRUE(Weekdays::Monday != Weekdays::Tuesday);
   }


  TEST(WeekdaysTest, less1)
   {
    ASSERT_TRUE(Weekdays::Monday < Weekdays::Tuesday);
   }


  TEST(WeekdaysTest, lessequal1)
   {
    ASSERT_TRUE(Weekdays::Monday <= Weekdays::Tuesday);
   }


  TEST(WeekdaysTest, greeater1)
   {
    ASSERT_TRUE(Weekdays::Tuesday > Weekdays::Monday);
   }


  TEST(WeekdaysTest, greaterequal1)
   {
    ASSERT_TRUE(Weekdays::Tuesday >= Weekdays::Monday);
   }


  TEST(WeekdaysTest, minusww1)
   {
    ASSERT_EQ(Weekdays::Monday - Weekdays::Monday, Days(0));
   }


  TEST(WeekdaysTest, minusww2)
   {
    ASSERT_EQ(Weekdays::Tuesday - Weekdays::Monday, Days(1));
   }


  TEST(WeekdaysTest, minusww3)
   {
    ASSERT_EQ(Weekdays::Monday - Weekdays::Tuesday, Days(1));
   }


  TEST(WeekdaysTest, plusDays1)
   {
    constexpr Days days {0};
    ASSERT_EQ(Weekdays::Monday + days, Weekdays::Monday);
   }


  TEST(WeekdaysTest, plusDays2)
   {
    constexpr Days days {1};
    ASSERT_EQ(Weekdays::Monday + days, Weekdays::Tuesday);
   }


  TEST(WeekdaysTest, plusDays3)
   {
    constexpr Days days {7};
    ASSERT_EQ(Weekdays::Monday + days, Weekdays::Monday);
   }


  TEST(WeekdaysTest, plusDays4)
   {
    constexpr Days days {8};
    ASSERT_EQ(Weekdays::Monday + days, Weekdays::Tuesday);
   }


  TEST(WeekdaysTest, plusDays5)
   {
    constexpr Days days {6};
    ASSERT_EQ(Weekdays::Sunday + days, Weekdays::Saturday);
   }


  TEST(WeekdaysTest, minusDays1)
   {
    constexpr Days days {0};
    ASSERT_EQ(Weekdays::Monday - days, Weekdays::Monday);
   }


  TEST(WeekdaysTest, minusDays2)
   {
    constexpr Days days {1};
    ASSERT_EQ(Weekdays::Monday - days, Weekdays::Sunday);
   }


  TEST(WeekdaysTest, minusDays3)
   {
    constexpr Days days {7};
    ASSERT_EQ(Weekdays::Monday - days, Weekdays::Monday);
   }


  TEST(WeekdaysTest, minusDays4)
   {
    constexpr Days days {8};
    ASSERT_EQ(Weekdays::Monday - days, Weekdays::Sunday);
   }


  TEST(WeekdaysTest, minusDays5)
   {
    constexpr Days days {6};
    ASSERT_EQ(Weekdays::Sunday - days, Weekdays::Monday);
   }


  TEST(WeekdaysTest, coutWeekdays1)
   {
    constexpr Weekdays wdays1 {Weekdays::Monday};
    testing::internal::CaptureStdout();
    std::cout << wdays1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Weekdays(Monday)");
   }

 }
