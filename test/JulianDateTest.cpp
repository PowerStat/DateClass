/*
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "JulianDate.h"


using namespace de::powerstat::datelib;


namespace
 {
  TEST(JulianDateTest, constructor1)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(1), JulianDay(1)};
    ASSERT_EQ(date.getDay().getDay(), 1);
    ASSERT_EQ(date.getMonth().getMonth(), 1);
    ASSERT_EQ(date.getYear().getYear(), 8);
   }


  TEST(JulianDateTest, constructor2)
   {
    constexpr JulianDate date {JulianYear(32767), JulianMonth(12), JulianDay(31)};
    ASSERT_EQ(date.getDay().getDay(), 31);
    ASSERT_EQ(date.getMonth().getMonth(), 12);
    ASSERT_EQ(date.getYear().getYear(), 32767);
   }


  TEST(JulianDateTest, constructor3)
   {
    try
     {
      [[maybe_unused]] JulianDate date {JulianYear(7), JulianMonth(1), JulianDay(1)};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      // std::cout << e.what() << "\n";
      ASSERT_EQ(std::string("year is < 8 or > 32767").compare(e.what()), 0);
     }
   }


  TEST(JulianDateTest, constructor4)
   {
    try
     {
      [[maybe_unused]] JulianDate date {JulianYear(32768), JulianMonth(1), JulianDay(1)};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      // std::cout << e.what() << "\n";
      ASSERT_EQ(std::string("year is < 8 or > 32767").compare(e.what()), 0);
     }
   }


  TEST(JulianDateTest, constructor5)
   {
    constexpr JD jd {1723980};
    constexpr JulianDate date {jd};
    ASSERT_EQ(date.getDay().getDay(), 1);
    ASSERT_EQ(date.getMonth().getMonth(), 1);
    ASSERT_EQ(date.getYear().getYear(), 8);
   }


  TEST(JulianDateTest, constructor6)
   {
    constexpr JD jd {2299160};
    constexpr JulianDate date {jd};
    ASSERT_EQ(date.getDay().getDay(), 4);
    ASSERT_EQ(date.getMonth().getMonth(), 10);
    ASSERT_EQ(date.getYear().getYear(), 1582);
   }


  TEST(JulianDateTest, constructor7)
   {
    try
     {
      [[maybe_unused]] const JulianDate date {JulianYear(8), JulianMonth(2), JulianDay(30)};
      FAIL();
     }
    catch (const std::out_of_range& e)
     {
      // std::cout << e.what() << "\n";
      ASSERT_EQ(std::string("day is > 29").compare(e.what()), 0);
     }
   }


  TEST(JulianDateTest, copyConstructor)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {date1};
    ASSERT_EQ(date2.getDay().getDay(), 12);
    ASSERT_EQ(date2.getMonth().getMonth(), 12);
    ASSERT_EQ(date2.getYear().getYear(), 12);
    ASSERT_TRUE(&date1 != &date2);
   }


  TEST(JulianDateTest, moveConstructor)
   {
    JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    const JulianDate date2 {std::move(date1)};
    ASSERT_EQ(date2.getDay().getDay(), 12);
    ASSERT_EQ(date2.getMonth().getMonth(), 12);
    ASSERT_EQ(date2.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, getDay)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(2), JulianDay(1)};
    ASSERT_EQ(date.getDay().getDay(), 1);
   }


  TEST(JulianDateTest, getMonth)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(2), JulianDay(1)};
    ASSERT_EQ(date.getMonth().getMonth(), 2);
   }


  TEST(JulianDateTest, getYear)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(2), JulianDay(1)};
    ASSERT_EQ(date.getYear().getYear(), 8);
   }


  TEST(JulianDateTest, getWeekday1)
   {
    constexpr JulianDate date {JulianYear(1582), JulianMonth(10), JulianDay(4)};
    ASSERT_EQ(date.getWeekday(), Weekdays::Thursday);
   }


  TEST(JulianDateTest, getWeekday2)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(1), JulianDay(7)};
    ASSERT_EQ(date.getWeekday(), Weekdays::Saturday);
   }


  TEST(JulianDateTest, getDayWithinYear1)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(1), JulianDay(1)};
    ASSERT_EQ(date.getDayWithinYear().getDays(), 1);
   }


  TEST(JulianDateTest, getDayWithinYear2)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(12), JulianDay(31)};
    ASSERT_EQ(date.getDayWithinYear().getDays(), 366);
   }


  TEST(JulianDateTest, getDayWithinYear3)
   {
    constexpr JulianDate date {JulianYear(9), JulianMonth(12), JulianDay(31)};
    ASSERT_EQ(date.getDayWithinYear().getDays(), 365);
   }


  TEST(JulianDateTest, getWeek1)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(1), JulianDay(1)};
    ASSERT_EQ(date.getWeek().getWeek(), 52);
   }


  TEST(JulianDateTest, getWeek2)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(12), JulianDay(30)};
    ASSERT_EQ(date.getWeek().getWeek(), 52);
   }


  TEST(JulianDateTest, getWeek3)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(12), JulianDay(31)};
    ASSERT_EQ(date.getWeek().getWeek(), 1);
   }


  TEST(JulianDateTest, getWeek4)
   {
    constexpr JulianDate date {JulianYear(9), JulianMonth(1), JulianDay(1)};
    ASSERT_EQ(date.getWeek().getWeek(), 1);
   }


  TEST(JulianDateTest, getJD1)
   {
    constexpr JulianDate date {JulianYear(8), JulianMonth(1), JulianDay(1)};
    ASSERT_EQ(date.getJD().getJD(), 1723980);
   }


  TEST(JulianDateTest, getJD2)
   {
    constexpr JulianDate date {JulianYear(1582), JulianMonth(10), JulianDay(4)};
    ASSERT_EQ(date.getJD().getJD(), 2299160);
   }


  TEST(JulianDateTest, equalOperator1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_TRUE(date1 == date2);
   }


  TEST(JulianDateTest, equalOperator2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    ASSERT_FALSE(date1 == date2);
   }


  TEST(JulianDateTest, notEqualOperator1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    ASSERT_TRUE(date1 != date2);
   }


  TEST(JulianDateTest, notEqualOperator2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_FALSE(date1 != date2);
   }


  TEST(JulianDateTest, smallerOperator1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    ASSERT_TRUE(date1 < date2);
   }


  TEST(JulianDateTest, smallerOperator2)
   {
    constexpr JulianDate date1 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_FALSE(date1 < date2);
   }


  TEST(JulianDateTest, smallerOperator3)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_FALSE(date1 < date2);
   }


  TEST(JulianDateTest, greaterOperator1)
   {
    constexpr JulianDate date1 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_TRUE(date1 > date2);
   }


  TEST(JulianDateTest, greaterOperator2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    ASSERT_FALSE(date1 > date2);
   }


  TEST(JulianDateTest, greaterOperator3)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_FALSE(date1 > date2);
   }


  TEST(JulianDateTest, smallerEqualOperator1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    ASSERT_TRUE(date1 <= date2);
   }


  TEST(JulianDateTest, smallerEqualOperator2)
   {
    constexpr JulianDate date1 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_FALSE(date1 <= date2);
   }


  TEST(JulianDateTest, smallerEqualOperator3)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_TRUE(date1 <= date2);
   }


  TEST(JulianDateTest, greaterEqualOperator1)
   {
    constexpr JulianDate date1 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_TRUE(date1 >= date2);
   }


  TEST(JulianDateTest, greaterEqualOperator2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(18), JulianMonth(12), JulianDay(18)};
    ASSERT_FALSE(date1 >= date2);
   }


  TEST(JulianDateTest, greaterEqualOperator3)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    ASSERT_TRUE(date1 >= date2);
   }


  TEST(JulianDateTest, plusDays1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr Days days {6};
    constexpr JulianDate newDate = date1 + days;
    ASSERT_EQ(newDate.getDay().getDay(), 18);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, plusDays2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr Days days {20};
    constexpr JulianDate newDate = date1 + days;
    ASSERT_EQ(newDate.getDay().getDay(), 1);
    ASSERT_EQ(newDate.getMonth().getMonth(), 1);
    ASSERT_EQ(newDate.getYear().getYear(), 13);
   }


  TEST(JulianDateTest, minusDays1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr Days days {6};
    constexpr JulianDate newDate = date1 - days;
    ASSERT_EQ(newDate.getDay().getDay(), 6);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, minusDays2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12),JulianDay(12) };
    constexpr Days days {18};
    constexpr JulianDate newDate = date1 - days;
    ASSERT_EQ(newDate.getDay().getDay(), 24);
    ASSERT_EQ(newDate.getMonth().getMonth(), 11);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, plusMonths1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(6), JulianDay(12)};
    constexpr Months months {6};
    constexpr JulianDate newDate = date1 + months;
    ASSERT_EQ(newDate.getDay().getDay(), 12);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, plusMonths2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(6), JulianDay(12)};
    constexpr Months months {12};
    constexpr JulianDate newDate = date1 + months;
    ASSERT_EQ(newDate.getDay().getDay(), 12);
    ASSERT_EQ(newDate.getMonth().getMonth(), 6);
    ASSERT_EQ(newDate.getYear().getYear(), 13);
   }


  TEST(JulianDateTest, minusMonths1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(6), JulianDay(12)};
    constexpr Months months {3};
    constexpr JulianDate newDate = date1 - months;
    ASSERT_EQ(newDate.getDay().getDay(), 12);
    ASSERT_EQ(newDate.getMonth().getMonth(), 3);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, minusMonths2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(6), JulianDay(12)};
    constexpr Months months {6};
    constexpr JulianDate newDate = date1 - months;
    ASSERT_EQ(newDate.getDay().getDay(), 12);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 11);
   }


  TEST(JulianDateTest, plusYears1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr Years years {6};
    constexpr JulianDate newDate = date1 + years;
    ASSERT_EQ(newDate.getDay().getDay(), 12);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 18);
   }


  TEST(JulianDateTest, minusYears1)
   {
    constexpr JulianDate date1 {JulianYear(14), JulianMonth(12), JulianDay(12)};
    constexpr Years years {6};
    constexpr JulianDate newDate = date1 - years;
    ASSERT_EQ(newDate.getDay().getDay(), 12);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 8);
   }


  TEST(JulianDateTest, plusWeeks1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Weeks weeks {2};
    constexpr JulianDate newDate = date1 + weeks;
    ASSERT_EQ(newDate.getDay().getDay(), 15);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, minusWeeks1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(20)};
    constexpr Weeks weeks {2};
    constexpr JulianDate newDate = date1 - weeks;
    ASSERT_EQ(newDate.getDay().getDay(), 6);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, plusDuration1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Duration duration {Years(0), Months(0), Days(0)};
    constexpr JulianDate newDate = date1 + duration;
    ASSERT_EQ(newDate.getDay().getDay(), 1);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, plusDuration2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Duration duration {Years(0), Months(1), Days(0)};
    constexpr JulianDate newDate = date1 + duration;
    ASSERT_EQ(newDate.getDay().getDay(), 1);
    ASSERT_EQ(newDate.getMonth().getMonth(), 1);
    ASSERT_EQ(newDate.getYear().getYear(), 13);
   }


  TEST(JulianDateTest, plusDuration3)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Duration duration {Years(1), Months(0), Days(0)};
    constexpr JulianDate newDate = date1 + duration;
    ASSERT_EQ(newDate.getDay().getDay(), 1);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 13);
   }


  TEST(JulianDateTest, plusDuration4)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Duration duration {Years(0), Months(0), Days(1)};
    constexpr JulianDate newDate = date1 + duration;
    ASSERT_EQ(newDate.getDay().getDay(), 2);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, plusDuration5)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(31)};
    constexpr Duration duration {Years(0), Months(2), Days(0)};
    constexpr JulianDate newDate = date1 + duration;
    ASSERT_EQ(newDate.getDay().getDay(), 1);
    ASSERT_EQ(newDate.getMonth().getMonth(), 3);
    ASSERT_EQ(newDate.getYear().getYear(), 13);
   }


  TEST(JulianDateTest, minusDuration1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Duration duration {Years(0), Months(0), Days(0)};
    constexpr JulianDate newDate = date1 - duration;
    ASSERT_EQ(newDate.getDay().getDay(), 1);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, minusDuration2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Duration duration {Years(0), Months(1), Days(0)};
    constexpr JulianDate newDate = date1 - duration;
    ASSERT_EQ(newDate.getDay().getDay(), 1);
    ASSERT_EQ(newDate.getMonth().getMonth(), 11);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, minusDuration3)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Duration duration {Years(1), Months(0), Days(0)};
    constexpr JulianDate newDate = date1 - duration;
    ASSERT_EQ(newDate.getDay().getDay(), 1);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 11);
   }


  TEST(JulianDateTest, minusDuration4)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)};
    constexpr Duration duration {Years(0), Months(0), Days(1)};
    constexpr JulianDate newDate = date1 - duration;
    ASSERT_EQ(newDate.getDay().getDay(), 30);
    ASSERT_EQ(newDate.getMonth().getMonth(), 11);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, minusDuration5)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(31)};
    constexpr Duration duration {Years(0), Months(1), Days(0)};
    constexpr JulianDate newDate = date1 - duration;
    ASSERT_EQ(newDate.getDay().getDay(), 30);
    ASSERT_EQ(newDate.getMonth().getMonth(), 11);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, plusWeekdays1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)}; // Thursday
    constexpr Weekdays wdays {Weekdays::Monday};
    constexpr JulianDate newDate = date1 + wdays;
    ASSERT_EQ(newDate.getDay().getDay(), 5);
    ASSERT_EQ(newDate.getMonth().getMonth(), 12);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }
 

  TEST(JulianDateTest, minusWeekdays1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(1)}; // Thursday
    constexpr Weekdays wdays {Weekdays::Monday};
    constexpr JulianDate newDate = date1 - wdays;
    ASSERT_EQ(newDate.getDay().getDay(), 28);
    ASSERT_EQ(newDate.getMonth().getMonth(), 11);
    ASSERT_EQ(newDate.getYear().getYear(), 12);
   }


  TEST(JulianDateTest, dayDiff1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(1), JulianDay(1)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(1), JulianDay(2)};
    constexpr Days newDays = dayDiff(date1, date2);
    ASSERT_EQ(newDays.getDays(), 1);
   }


  TEST(JulianDateTest, dayDiff2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(1), JulianDay(2)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(1), JulianDay(1)};
    constexpr Days newDays = dayDiff(date1, date2);
    ASSERT_EQ(newDays.getDays(), 1);
   }


  TEST(JulianDateTest, dayDiff3)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    constexpr JulianDate date2 {JulianYear(13), JulianMonth(1), JulianDay(1)};
    constexpr Days newDays = dayDiff(date1, date2);
    ASSERT_EQ(newDays.getDays(), 20);
   }


  TEST(JulianDateTest, minusJulianDateJulianDate1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(1), JulianDay(1)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(1), JulianDay(2)};
    constexpr Duration newDuration = date1 - date2;
    ASSERT_EQ(newDuration.getYears().getYears(), 0);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 0);
    ASSERT_EQ(newDuration.getDays().getDays(), 1);
   }


  TEST(JulianDateTest, minusJulianDateJulianDate2)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(1), JulianDay(2)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(1), JulianDay(1)};
    constexpr Duration newDuration = date1 - date2;
    ASSERT_EQ(newDuration.getYears().getYears(), 0);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 0);
    ASSERT_EQ(newDuration.getDays().getDays(), 1);
   }


  TEST(JulianDateTest, minusJulianDateJulianDate3)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(1), JulianDay(1)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(2), JulianDay(1)};
    constexpr Duration newDuration = date1 - date2;
    ASSERT_EQ(newDuration.getYears().getYears(), 0);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 1);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(JulianDateTest, minusJulianDateJulianDate4)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(2), JulianDay(1)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(1), JulianDay(1)};
    constexpr Duration newDuration = date1 - date2;
    ASSERT_EQ(newDuration.getYears().getYears(), 0);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 1);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(JulianDateTest, minusJulianDateJulianDate5)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(1), JulianDay(1)};
    constexpr JulianDate date2 {JulianYear(13), JulianMonth(1), JulianDay(1)};
    constexpr Duration newDuration = date1 - date2;
    ASSERT_EQ(newDuration.getYears().getYears(), 1);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 0);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(JulianDateTest, minusJulianDateJulianDate6)
   {
    constexpr JulianDate date1 {JulianYear(13), JulianMonth(1), JulianDay(1)};
    constexpr JulianDate date2 {JulianYear(12), JulianMonth(1), JulianDay(1)};
    constexpr Duration newDuration = date1 - date2;
    ASSERT_EQ(newDuration.getYears().getYears(), 1);
    ASSERT_EQ(newDuration.getMonths().getMonths(), 0);
    ASSERT_EQ(newDuration.getDays().getDays(), 0);
   }


  TEST(JulianDateTest, getEaster1)
   {
    constexpr JulianYear year {1582};
    constexpr JulianDate easter = getEaster(year);
    ASSERT_EQ(easter.getMonth().getMonth(), 4);
    ASSERT_EQ(easter.getDay().getDay(), 15);
   }


  TEST(JulianDateTest, coutDay1)
   {
    constexpr JulianDate date1 {JulianYear(12), JulianMonth(12), JulianDay(12)};
    testing::internal::CaptureStdout();
    std::cout << date1;
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "JulianDate(JulianYear(12), JulianMonth(12), JulianDay(12))");
   }


  TEST(JulianDateTest, factory1)
   {
    constexpr JulianDate date = factory(JulianYear(8), JulianWeek(1), Weekdays::Monday);
    ASSERT_EQ(date.getYear().getYear(), 8);
    ASSERT_EQ(date.getMonth().getMonth(), 1);
    ASSERT_EQ(date.getDay().getDay(), 2);
   }


  TEST(JulianDateTest, factory2)
   {
    constexpr JulianDate date = factory(JulianYear(8), JulianWeek(52), Weekdays::Sunday);
    ASSERT_EQ(date.getYear().getYear(), 8);
    ASSERT_EQ(date.getMonth().getMonth(), 12);
    ASSERT_EQ(date.getDay().getDay(), 30);
   }


  TEST(JulianDateTest, factory3)
   {
    constexpr JulianDate date = factory(JulianYear(8), JulianWeek(2), Weekdays::Monday);
    ASSERT_EQ(date.getYear().getYear(), 8);
    ASSERT_EQ(date.getMonth().getMonth(), 1);
    ASSERT_EQ(date.getDay().getDay(), 9);
   }

 }
