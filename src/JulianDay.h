/** @file
 * A Day is a numerical representation of a day within a month without being related to month/year.
 * So it could have a value between 1 and 31.
 *
 * Copyright (C) 2020-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_JULIANDAY_H_
#define DATELIB_JULIANDAY_H_


#include <ostream>
#include <stdexcept>
#include <string>
#include "Days.h"
#include "JulianMonth.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Value class that represents a day number (1-31) in the julian calendar system.
   */
  class JulianDay final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] day Day number (1-31)
       * @throws std::out_of_range Day is < 1 or > 31
       */
      constexpr explicit JulianDay(const unsigned short day)
       : day{day}
       {
        if (day < 1 || day > 31)
         {
          throw std::out_of_range("day is < 1 or > 31");
         }
       }


      /**
       * Constructor.
       *
       * @param[in] month Month number (1 - 12)
       * @param[in] day Day number (1 - max days in month) depending on the month
       * @throws std::out_of_range Day is < 1 or > max days in month
       */
      constexpr explicit JulianDay(const JulianMonth month, const unsigned short day)
       : day{day}
       {
        const Days daysInMonth = month.getDaysInMonth();
        if (day < 1 || day > daysInMonth.getDays())
         {
          throw std::out_of_range("day is < 1 or > " + std::to_string(daysInMonth.getDays()));
         }
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Day object to copy from.
       */
      constexpr JulianDay(const JulianDay &other) noexcept = default;

      /**
       * Move constructor.
       *
       * @param[in] other Another Day object to move from.
       */
      constexpr JulianDay(JulianDay&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~JulianDay() noexcept = default;

      /**
       * Assignment operator for another Day object.
       *
       * @param[in] other Another day object to be assigned to this object.
       * @return JulianDay
       */
      auto operator=(const JulianDay &other) & noexcept -> JulianDay& = delete;

      /**
       * Move assignment operator for another Day object.
       *
       * @param[in] other Another day object to be assigned to this object.
       * @return JulianDay&
       */
      auto operator=(JulianDay&& other) & noexcept -> JulianDay& = delete;


      /**
       * Get day number as primitive data type.
       *
       * @return JulianDay number (1-31)
       */
      [[nodiscard]] constexpr auto getDay() const noexcept -> unsigned short
       {
        return(this->day);
       }

    private:
      const unsigned short day;

   };


  /** @relates JulianDay
   * Operator equal to compare two Day objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const JulianDay &lhs, const JulianDay &rhs) noexcept -> bool
   {
    return(lhs.getDay() == rhs.getDay());
   }


  /** @relates JulianDay
   * Operator not equal to compare two Day objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const JulianDay &lhs, const JulianDay &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates JulianDay
   * Operator smaller to compare two Day objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const JulianDay &lhs, const JulianDay &rhs) noexcept -> bool
   {
    return(lhs.getDay() < rhs.getDay());
   }


  /** @relates JulianDay
   * Operator greater to compare two Day objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const JulianDay &lhs, const JulianDay &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates JulianDay
   * Operator smaller or equal to compare two Day objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const JulianDay &lhs, const JulianDay &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates JulianDay
   * Operator greater or equal to compare two Day objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const JulianDay &lhs, const JulianDay &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates JulianDay
   * Operator plus to add a Days value to a Day (only if the result is smaller than 31).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDay object
   * @throws std::out_of_range When Day will become > 31
   */
  [[nodiscard]] constexpr auto operator+(const JulianDay &lhs, const Days &rhs) -> JulianDay
   {
    if (rhs.getDays() > 30)
     {
      throw std::out_of_range("days is > 30");
     }
    if (lhs.getDay() + rhs.getDays() > 31)
     {
      throw std::out_of_range("day will be > 31");
     }
    return(JulianDay(lhs.getDay() + static_cast<unsigned short>(rhs.getDays())));
   }


  /** @relates JulianDay
   * Operator minus to subtract a Days value from a Day (only if the result is greater than 0).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianDay object
   * @throws std::out_of_range When Day will become < 1
   */
  [[nodiscard]] constexpr auto operator-(const JulianDay &lhs, const Days &rhs) -> JulianDay
   {
    if (rhs.getDays() >= lhs.getDay())
     {
      throw std::out_of_range("day will be < 1");
     }
    return(JulianDay(lhs.getDay() - static_cast<unsigned short>(rhs.getDays())));
   }


  /** @relates JulianDay
   * Operator minus to get the difference of a Day value to another Day.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Days object
   */
  [[nodiscard]] constexpr auto operator-(const JulianDay &lhs, const JulianDay &rhs) noexcept -> Days
   {
    if (lhs < rhs)
     {
      return(Days(rhs.getDay() - lhs.getDay()));
     }
    return(Days(lhs.getDay() - rhs.getDay()));
   }


  /** @relates JulianDay
   * Stream operator to write a Day to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj JulianDay object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const JulianDay& obj) -> std::ostream&
   {
    os << "JulianDay(" << obj.getDay() << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_JULIANDAY_H_
