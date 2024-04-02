/** @file
 * A Date is a representation of a year-month-day.
 * So it could have a value between 8-01-01 and 32767-12-31
 *
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_JULIANDATE_H_
#define DATELIB_JULIANDATE_H_


#include <ostream>
#include <stdexcept>
#include <string>
#include "Weekdays.h"
#include "Days.h"
#include "Months.h"
#include "Years.h"
#include "Weeks.h"
#include "Duration.h"
#include "JD.h"
#include "JulianDay.h"
#include "JulianMonth.h"
#include "JulianYear.h"
#include "JulianWeek.h"

#include <iostream>


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Value class that represents a date in the julian calendar system.
   */
  class JulianDate final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] year Year
       * @param[in] month Month depending on the year
       * @param[in] day Day depending on the month
       * @throws std::out_of_range Date is < 8-1-1 or > 32767-12-31
       */
      constexpr explicit JulianDate(const JulianYear year, const JulianMonth month, const JulianDay day)
       : year(year), month(month), day(day)
       {
        const JulianMonth checkMonth = JulianMonth(year, month.getMonth());
        const Days daysInMonth = checkMonth.getDaysInMonth();
        if (day.getDay() > daysInMonth.getDays())
         {
          throw std::out_of_range("day is > " + std::to_string(daysInMonth.getDays()));
         }
       }


      /**
       * Constructor.
       *
       * @param[in] jd JD
       */
      constexpr explicit JulianDate(const JD jd)
       : year([](const JD& jd) constexpr -> const JulianYear {const unsigned long a = jd.getJD() + 1524; const unsigned short b = static_cast<unsigned short>((a - 122.1) / 365.25); const unsigned short c = static_cast<unsigned short>(a - static_cast<unsigned long>(365.25 * b)); const unsigned short d = static_cast<unsigned short>(c / 30.6001); return JulianYear(static_cast<long>(static_cast<unsigned short>(d < 14 ? d - 1 : d - 13) > 2 ? b - 4716 : b - 4715));}(jd)),
         month([](const JD& jd) constexpr -> const JulianMonth {const unsigned long a = jd.getJD() + 1524; const unsigned short b = static_cast<unsigned short>((a - 122.1) / 365.25); const unsigned short c = static_cast<unsigned short>(a - static_cast<unsigned long>(365.25 * b)); const unsigned short d = static_cast<unsigned short>(c / 30.6001); return JulianMonth(static_cast<unsigned short>(d < 14 ? d - 1 : d - 13));}(jd)),
         day([](const JD& jd) constexpr -> const JulianDay {const unsigned long a = jd.getJD() + 1524; const unsigned short b = static_cast<unsigned short>((a - 122.1) / 365.25); const unsigned short c = static_cast<unsigned short>(a - static_cast<unsigned long>(365.25 * b)); const unsigned short d = static_cast<unsigned short>(c / 30.6001); return JulianDay(static_cast<unsigned short>(c - static_cast<unsigned short>(30.6001 * d)));}(jd))
       {
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Date object to copy from.
       */
      constexpr JulianDate(const JulianDate &other) noexcept = default;

      /**
       * Move constructor.
       *
       * @param[in] other Another Date object to move from.
       */
      constexpr JulianDate(JulianDate&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~JulianDate() noexcept = default;

      /**
       * Assignment operator for another Date object.
       *
       * @param[in] other Another date object to be assigned to this object.
       */
      auto operator=(const JulianDate &other) & noexcept -> JulianDate& = delete;

      /**
       * Move assignment operator for another Date object.
       *
       * @param[in] other Another date object to be assigned to this object.
       * @return JulianDate&
       */
      auto operator=(JulianDate&& other) & noexcept -> JulianDate& = delete;


      /**
       * Get year as data type.
       *
       * @return JulianYear (8-32767)
       */
      [[nodiscard]] constexpr auto getYear() const noexcept -> JulianYear
       {
        return(this->year);
       }


      /**
       * Get month as data type.
       *
       * @return JulianMonth (1-12)
       */
      [[nodiscard]] constexpr auto getMonth() const noexcept -> JulianMonth
       {
        return(this->month);
       }


      /**
       * Get day as data type.
       *
       * @return JulianDay (1-31)
       */
      [[nodiscard]] constexpr auto getDay() const noexcept -> JulianDay
       {
        return(this->day);
       }


      /**
       * Get weekday as data type.
       *
       * @return Weekday
       */
      [[nodiscard]] constexpr auto getWeekday() const noexcept -> Weekdays
       {
        const unsigned short day = this->day.getDay();
        unsigned short month = this->month.getMonth();
        long year = this->year.getYear();

        // January and february dates must be 13 and 14 of the year before!
        switch (month)
         {
          case 1 :
          case 2 :
            month += 12;
            --year;
            [[fallthrough]];
          default:
            ;
         }
        const unsigned short decade = static_cast<unsigned short>(year - ((year / 100) * 100));
        // Formula from Ch. Zeller in 1877
        unsigned short wday = static_cast<unsigned short>((day + (((month + 1) * 26) / 10) + decade + (decade / 4) + 5 - static_cast<unsigned short>(year / 100)) % 7);
        // Convert (1-su 2-mo 3-tu 4-we 5-th 6-fr 7/0-sa) to iso days
        if (wday == 0)
         {
          wday = 6;
         }
        else
         {
          --wday;
          if (wday == 0)
           {
            wday = 7;
           }
         }
        return(Weekdays(wday));
       }


      /**
       * Get the Day within Year
       *
       * @return Days (1-366)
       */
      [[nodiscard]] constexpr auto getDayWithinYear() const -> Days
       {
        unsigned long days = 0;
        for (unsigned short month = 1; month < this->month.getMonth(); ++month)
         {
          days += JulianMonth(this->year, month).getDaysInMonth().getDays();
         }
        days += this->day.getDay();
        return Days(days);
       }


      /**
       * Get week as data type.
       *
       * @return JulianWeek (1-53)
       */
      [[nodiscard]] constexpr auto getWeek() const -> JulianWeek
       {
        const JulianDate firstday = JulianDate(this->year, JulianMonth(1), JulianDay(1));
        Weekdays firstweekday = firstday.getWeekday();
        unsigned long week = (getDayWithinYear().getDays() - 1 + static_cast<unsigned long>(firstweekday) - 1) / 7;
        if (firstweekday > Weekdays::Thursday)
         {
          if (week == 0)
           {
            week = (this->year.getYear() == 8) ? 52 : JulianDate(JulianYear(this->year.getYear() - 1), JulianMonth(12), JulianDay(31)).getWeek().getWeek();
           }
          else if ((firstweekday == Weekdays::Sunday) && this->year.isLeapYear() && (this->month.getMonth() == 12) && (this->day.getDay() == 31))
           {
            week = 1;
           }
          return JulianWeek(week);
         }
        else if ([](long year1, unsigned short month1, unsigned day1, long year2, unsigned short month2, unsigned day2) constexpr -> short {short result = (year1 < year2) ? -1 : ((year1 > year2) ? 1 : 0); if (result != 0) {return result;} result = (month1 < month2) ? -1 : ((month1 > month2) ? 1 : 0); if (result != 0) {return result;} return (day1 < day2) ? -1 : ((day1 > day2) ? 1 : 0);}(this->year.getYear(), this->month.getMonth(), this->day.getDay(), this->year.getYear(), 12, 29) != -1)
         {
          firstweekday = JulianDate(this->year, JulianMonth(12), this->day).getWeekday();
          if (static_cast<unsigned short>(firstweekday) <= (this->day.getDay() - 28))
           {
            week = 0;
           }
         }
        return(JulianWeek(week + 1));
       }


      /**
       * Get JD as data type.
       *
       * @return JD
       */
      [[nodiscard]] constexpr auto getJD() const -> JD
       {
        return(this->year.getScaligerYear().getJD() + (getDayWithinYear() - Days(1)));
       }

    private:
      const JulianYear year;
      const JulianMonth month;
      const JulianDay day;

   };


  /** @relates JulianDate
   * Operator equal to compare two Date objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const JulianDate &lhs, const JulianDate &rhs) noexcept -> bool
   {
    return((lhs.getYear() == rhs.getYear()) && (lhs.getMonth() == rhs.getMonth()) && (lhs.getDay() == rhs.getDay()));
   }


  /** @relates JulianDate
   * Operator not equal to compare two Date objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const JulianDate &lhs, const JulianDate &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates JulianDate
   * Operator smaller to compare two Date objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const JulianDate &lhs, const JulianDate &rhs) noexcept -> bool
   {
    bool result = lhs.getYear() < rhs.getYear();
    if (!result && (lhs.getYear() == rhs.getYear()))
     {
      result = lhs.getMonth() < rhs.getMonth();
      if (!result && (lhs.getMonth() == rhs.getMonth()))
       {
        result = lhs.getDay() < rhs.getDay();
       }
     }
    return(result);
   }


  /** @relates JulianDate
   * Operator greater to compare two Date objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const JulianDate &lhs, const JulianDate &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates JulianDate
   * Operator smaller or equal to compare two Date objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const JulianDate &lhs, const JulianDate &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates JulianDate
   * Operator greater or equal to compare two Date objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const JulianDate &lhs, const JulianDate &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates JulianDate
   * Operator plus to add a Years value to a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator+(const JulianDate &lhs, const Years &rhs) -> JulianDate
   {
    return(JulianDate(lhs.getYear() + rhs, lhs.getMonth(), lhs.getDay()));
   }


  /** @relates JulianDate
   * Operator minus to subtract a Years value from a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator-(const JulianDate &lhs, const Years &rhs) -> JulianDate
   {
    return(JulianDate(lhs.getYear() - rhs, lhs.getMonth(), lhs.getDay()));
   }


  /** @relates JulianDate
   * Operator plus to add a Months value to a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator+(const JulianDate &lhs, const Months &rhs) -> JulianDate
   {
    long year = lhs.getYear().getYear();
    unsigned long month = lhs.getMonth().getMonth();
    const unsigned long months = rhs.getMonths();
    month += months;
    while (month > 12)
     {
      month -= 12;
      ++year;
     }
    return(JulianDate(JulianYear(year), JulianMonth(static_cast<unsigned short>(month)), lhs.getDay()));
   }


  /** @relates JulianDate
   * Operator minus to subtract a Months value from a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator-(const JulianDate &lhs, const Months &rhs) -> JulianDate
   {
    long year = lhs.getYear().getYear();
    long month = lhs.getMonth().getMonth();
    const unsigned long months = rhs.getMonths();
    month -= months;
    while (month < 1)
     {
      month += 12;
      --year;
     }
    return(JulianDate(JulianYear(year), JulianMonth(static_cast<unsigned short>(month)), lhs.getDay()));
   }


  /** @relates JulianDate
   * Day difference when subtract a Date value from a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Days object
   */
  [[nodiscard]] constexpr auto dayDiff(const JulianDate &lhs, const JulianDate &rhs) -> Days
   {
    long year1 = lhs.getYear().getYear();
    long year2 = rhs.getYear().getYear();
    unsigned short month1 = lhs.getMonth().getMonth();
    unsigned short month2 = rhs.getMonth().getMonth();
    const unsigned short day1 = lhs.getDay().getDay();
    const unsigned short day2 = rhs.getDay().getDay();
    long t1 = day1;
    long t2 = day2;

    while (month1 > 1)
     {// calc days left by the gone month of the year1
      --month1;
      t1 += JulianMonth(lhs.getYear(), month1).getDaysInMonth().getDays();
     }
    while (month2 > 1)
     {// calc days left by the gone month of the year2
      --month2;
      t2 += JulianMonth(rhs.getYear(), month2).getDaysInMonth().getDays();
     }
    while (year1 > year2)
     {// calc days of diff years
      --year1;
      t1 += JulianYear(year1).getDaysInYear().getDays();
     }
    while (year1 < year2)
     {// calc days of diff years
      --year2;
      t2 += JulianYear(year2).getDaysInYear().getDays();
     }
    if (t1 > t2)
     {
      return(Days(t1 - t2));
     }
    return(Days(t2 - t1));
   }


  /** @relates JulianDate
   * Operator plus to add a Days value to a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator+(const JulianDate &lhs, const Days &rhs) -> JulianDate
   {
    long dyear = lhs.getYear().getYear();
    unsigned short dmonth = lhs.getMonth().getMonth();
    unsigned short dday = lhs.getDay().getDay();
    unsigned long days = rhs.getDays();
    unsigned long ddays = dayDiff(lhs, JulianDate(JulianYear(lhs.getYear()), JulianMonth(1), JulianDay(1)) + Years(1)).getDays();
    while (days >= ddays) // years
     {
      dday = 1;
      dmonth = 1;
      ++dyear;
      days -= ddays;
      ddays = dayDiff(JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(dday)), JulianDate(JulianYear(dyear), JulianMonth(1), JulianDay(1)) + Years(1)).getDays();
     }
    ddays = dayDiff(JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(dday)), JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(1)) + Months(1)).getDays();
    while (days >= ddays) // months
     {
      dday = 1;
      ++dmonth;
      days -= ddays;
      ddays = dayDiff(JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(dday)), JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(1)) + Months(1)).getDays();
     }
    if (days > 0) // days
     {
      dday += static_cast<unsigned short>(days);
     }
    return(JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(dday)));
   }


  /** @relates JulianDate
   * Operator minus to subtract a Days value from a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator-(const JulianDate &lhs, const Days &rhs) -> JulianDate
   {
    long dyear = lhs.getYear().getYear();
    unsigned short dmonth = lhs.getMonth().getMonth();
    unsigned short dday = lhs.getDay().getDay();
    unsigned long days = rhs.getDays();
    unsigned long ddays = dayDiff(lhs, JulianDate(JulianYear(lhs.getYear()), JulianMonth(12), JulianDay(31)) - Years(1)).getDays();
    while (days >= ddays) // years
     {
      dday = 31;
      dmonth = 12;
      --dyear;
      days -= ddays;
      ddays = dayDiff(JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(dday)), JulianDate(JulianYear(dyear), JulianMonth(12), JulianDay(31)) - Years(1)).getDays();
     }
    ddays = dayDiff(JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(dday)), JulianDate(JulianYear(dyear), JulianMonth(dmonth - 1), JulianDay(JulianMonth(JulianYear(dyear), dmonth - 1).getDaysInMonth().getDays()))).getDays();
    while (days >= ddays) // months
     {
      dday = JulianMonth(JulianYear(dyear), dmonth - 1).getDaysInMonth().getDays();
      --dmonth;
      days -= ddays;
      ddays = dayDiff(JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(dday)), JulianDate(JulianYear(dyear), JulianMonth(dmonth - 1), JulianDay(JulianMonth(JulianYear(dyear), dmonth - 1).getDaysInMonth().getDays()))).getDays();
     }
    if (days > 0)
     {
      dday -= days;
     }
    return(JulianDate(JulianYear(dyear), JulianMonth(dmonth), JulianDay(dday)));
   }


  /** @relates JulianDate
   * Operator plus to add a Weeks value to a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator+(const JulianDate &lhs, const Weeks &rhs) -> JulianDate
   {
    return(lhs + Days(rhs.getWeeks() * 7));
   }


  /** @relates JulianDate
   * Operator minus to subtract a Weeks value from a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator-(const JulianDate &lhs, const Weeks &rhs) -> JulianDate
   {
    return(lhs - Days(rhs.getWeeks() * 7));
   }


  /** @relates JulianDate
   * Operator plus to add a Duration value to a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator+(const JulianDate &lhs, const Duration &rhs) -> JulianDate
   {
    long year = lhs.getYear().getYear();
    unsigned short month = lhs.getMonth().getMonth();
    unsigned short day = lhs.getDay().getDay();
    year += rhs.getYears().getYears();
    month +=  rhs.getMonths().getMonths();
    if (month > 12)
     {
      month -= 12;
      ++year;
     }
    if (JulianMonth(JulianYear(year), month).getDaysInMonth().getDays() < day)
     {
      day = 1;
      ++month;
     }
    const JulianDate newDate1 = JulianDate(JulianYear(year), JulianMonth(month), JulianDay(day));
    return(newDate1 + rhs.getDays());
   }


  /** @relates JulianDate
   * Operator minus to subtract a Duration value from a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator-(const JulianDate &lhs, const Duration &rhs) -> JulianDate
   {
    long year = lhs.getYear().getYear();
    unsigned short month = lhs.getMonth().getMonth();
    unsigned short day = lhs.getDay().getDay();
    year -= rhs.getYears().getYears();
    if (const unsigned short months = rhs.getMonths().getMonths(); month > months)
     {
      month -= months;
     }
    else
     {
      month += 12 - months;
      --year;
     }
    if (JulianMonth(JulianYear(year), month).getDaysInMonth().getDays() < day)
     {
      day = JulianMonth(JulianYear(year), month).getDaysInMonth().getDays();
     }
    const JulianDate newDate1 = JulianDate(JulianYear(year), JulianMonth(month), JulianDay(day));
    return(newDate1 - rhs.getDays());
   }


  /** @relates JulianDate
   * Operator plus to move to the next (or same) Weekday Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator+(const JulianDate &lhs, const Weekdays &rhs) -> JulianDate
   {
    const Weekdays wday = lhs.getWeekday();
    const Days days = (wday <= rhs) ? rhs - wday : Days(7 - static_cast<unsigned short>(wday) + static_cast<unsigned short>(rhs));
    return(lhs + days);
   }


  /** @relates JulianDate
   * Operator minus to move to the previous (pr same) Weekday Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDate object
   */
  [[nodiscard]] constexpr auto operator-(const JulianDate &lhs, const Weekdays &rhs) -> JulianDate
   {
    const Weekdays wday = lhs.getWeekday();
    const Days days = (wday >= rhs) ? wday - rhs : Days (7 - static_cast<unsigned short>(rhs) + static_cast<unsigned short>(wday));
    return(lhs - days);
   }


  /** @relates JulianDate
   * Operator minus to subtract a Date value from a Date.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   */
  [[nodiscard]] constexpr auto operator-(const JulianDate &lhs, const JulianDate &rhs) -> Duration
   {
    unsigned short day1 = 0;
    unsigned short day2 = 0;
    unsigned short month1 = 0;
    unsigned short month2 = 0;
    long year1 = 0;
    long year2 = 0;
    if (lhs > rhs)
     {
      day1 = rhs.getDay().getDay();
      day2 = lhs.getDay().getDay();
      month1 = rhs.getMonth().getMonth();
      month2 = lhs.getMonth().getMonth();
      year1 = rhs.getYear().getYear();
      year2 = lhs.getYear().getYear();
     }
    else
     {
      day1 = lhs.getDay().getDay();
      day2 = rhs.getDay().getDay();
      month1 = lhs.getMonth().getMonth();
      month2 = rhs.getMonth().getMonth();
      year1 = lhs.getYear().getYear();
      year2 = rhs.getYear().getYear();
     }
    long years = 0;
    while (JulianDate(JulianYear(year1), JulianMonth(month1), JulianDay(day1)) + Years(1) <= JulianDate(JulianYear(year2), JulianMonth(month2), JulianDay(day2)))
     {
      ++years;
      ++year1;
     }
    short months = 0;
    while (JulianDate(JulianYear((month1 + 1 == 13) ? year1 + 1 : year1), JulianMonth((month1 + 1 == 13) ? 1 : month1 + 1), JulianDay(day1)) <= JulianDate(JulianYear(year2), JulianMonth(month2), JulianDay(day2)))
     {
      ++months;
      ++month1;
      if (month1 == 13)
       {
        month1 = 1;
        ++year1;
       }
     }
    const JulianDate date = JulianDate(JulianYear(year1), JulianMonth(month1), JulianDay(day1));
    const Days days = dayDiff(date, JulianDate(JulianYear(year2), JulianMonth(month2), JulianDay(day2)));
    return(Duration(Years(years), Months(months), days));
   }


  /**
   * Get easter date for year.
   *
   * @param[in] year Julian year
   * @return JulianDate easter
   */
  [[nodiscard]] constexpr static auto getEaster(JulianYear year) -> JulianDate
   {
    const unsigned short a = static_cast<unsigned short>((19 * (year.getYear() % 19) + 15) % 30);
    const unsigned short b = static_cast<unsigned short>((2 * (year.getYear() % 4) + 4 * (year.getYear() % 7) - a + 34) % 7);
    const unsigned short c = static_cast<unsigned short>(a + b + 114);
    const unsigned short dday = static_cast<unsigned short>(c % 31 + 1);
    const unsigned short dmonth = static_cast<unsigned short>(c / 31);
    return JulianDate(year, JulianMonth(dmonth), JulianDay(dday));
   }


  /** @relates JulianDate
   * Stream operator to write a Date to an output stream.
   *
   * @param[in] outs Output stream
   * @param[in] obj JulianDate object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& outs, const JulianDate& obj) -> std::ostream&
   {
    outs << "JulianDate(" << obj.getYear() << ", " << obj.getMonth() << ", " << obj.getDay() << ")";
    return outs;
   }


  /**
   * Factory.
   *
   * @param[in] year Year
   * @param[in] week Week depending on the year
   * @param[in] weekday Weekday depending on the week
   * @return JulianDate
   * @throws std::out_of_range Date is < 8-1-1 or > 32767-12-31
   */
  constexpr auto factory(const JulianYear year, const JulianWeek week, const Weekdays weekday) -> JulianDate
   {
    const JulianDate firstday = JulianDate(year, JulianMonth(1), JulianDay(1));
    const JulianDate diff1 = (firstday.getWeek().getWeek() > 1) ? JulianDate(JulianYear(year), JulianMonth(1), ((firstday + Weekdays::Monday)).getDay()) : (firstday - Weekdays::Monday);
    return (diff1 + Days((week.getWeek() - 1) * 7)) + weekday;
   }

 } // namespace

#endif // JULIANDATE_H_
