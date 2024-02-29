/*
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */

#ifndef DATELIB_WEEKDAYS_H_
#define DATELIB_WEEKDAYS_H_


#include <ostream>
#include "Days.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Enumeration of weekdays.
   */
  enum class Weekdays : unsigned short
   {
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
    Sunday = 7
   };


  /** @relates Weekdays
   * Operator minus to get the difference of a Weekdays value to another Weekdays.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Days object
   */
  [[nodiscard]] constexpr auto operator-(const Weekdays &lhs, const Weekdays &rhs) noexcept -> Days
   {
    if (rhs > lhs)
     {
      return(Days(static_cast<unsigned short>(rhs) - static_cast<unsigned short>(lhs)));
     }
    return(Days(static_cast<unsigned short>(lhs) - static_cast<unsigned short>(rhs)));
   }


  /** @relates Weekdays
   * Operator plus to add Days to a Weekdays.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Weekdays object
   */
  [[nodiscard]] constexpr auto operator+(const Weekdays &lhs, const Days &rhs) noexcept -> Weekdays
   {
    unsigned short wd = static_cast<unsigned short>(lhs);
    wd += rhs.getDays() % 7;
    if (wd > 7)
     {
      wd -= 7;
     }
    return(Weekdays(wd));
   }


  /** @relates Weekdays
   * Operator minus to subtract Days from a Weekdays.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Weekdays object
   */
  [[nodiscard]] constexpr auto operator-(const Weekdays &lhs, const Days &rhs) noexcept -> Weekdays
   {
    short wd = static_cast<short>(lhs);
    wd -= rhs.getDays() % 7;
    if (wd <= 0)
     {
      wd += 7;
     }
    return(Weekdays(wd));
   }


  /**
   * Weekday names.
   */
  static const char *const weekdayNames[] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};


  /** @relates Weekdays
   * Stream operator to write a Weekdays to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj Weekdays enum to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const Weekdays& obj) -> std::ostream&
   {
    os << "Weekdays(" << weekdayNames[static_cast<unsigned short>(obj)] << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_WEEKDAYS_H_
