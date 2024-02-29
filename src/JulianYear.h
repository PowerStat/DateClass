/** @file
 * A Year is a numerical representation of a year.
 * So it could have a value between 8 and 32767.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_JULIANYEAR_H_
#define DATELIB_JULIANYEAR_H_


#include <ostream>
#include <stdexcept>
#include <climits>
#include "Days.h"
#include "Years.h"
#include "Weeks.h"
#include "Weekdays.h"
#include "ScaligerYear.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Value class that represents a year number (8-32767) in the julian calendar system.
   */
  class JulianYear final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] year Year number (8-32767)
       * @throws std::out_of_range Year is < 8 or > 32767
       */
      constexpr explicit JulianYear(const long year)
       : year(year)
       {
        if (year < 8 || year > 32767)
         {
          throw std::out_of_range("year is < 8 or > 32767");
         }
       }


      /**
       * Constructor.
       *
       * @param[in] syear Scaliger year (4721 - 6295)
       */
      constexpr explicit JulianYear(const ScaligerYear& syear)
       : year([](const ScaligerYear& syear) constexpr -> const long {if (syear.getYear() < 4721) {throw std::out_of_range("syear must be >= 4721");} return (syear.getYear() - 4713);}(syear))
       {
       }


       /**
        * Copy constructor.
        *
        * @param[in] other Another Year object to copy from.
        */
      constexpr JulianYear(const JulianYear &other) noexcept = default;

      /**
       * Move constructor.
       * 
       * @param[in] other Another Year object to move from.
       */
      constexpr JulianYear(JulianYear&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~JulianYear() noexcept = default;

      /**
       * Assignment operator for another Year object.
       *
       * @param[in] other Another year object to be assigned to this object.
       * @return JulianYear
       */
      auto operator=(const JulianYear &other) noexcept -> JulianYear& = delete;

      /**
       * Move assignment operator for another Year object.
       * 
       * @param[in] other Another year object to be assigned to this object.
       * @return JulianYear& 
       */
      auto operator=(JulianYear&& other) noexcept -> JulianYear& = delete;


      /**
       * Get year number as primitive data type.
       *
       * @return JulianYear number (8-32767)
       */
      [[nodiscard]] constexpr auto getYear() const noexcept -> long
       {
        return(this->year);
       }


      /**
       * Is leap year.
       *
       * @return true: leap year, false: otherwise
       */
      [[nodiscard]] constexpr auto isLeapYear() const noexcept -> bool
       {
        if (this->year <= 0)
         {
          return((-this->year) % 4 == 1);
         }
        return(this->year % 4 == 0);
       }


      /**
       * Number of days in year.
       *
       * @return Number of days in year (365|366)
       */
      [[nodiscard]] constexpr auto getDaysInYear() const noexcept -> Days
       {
        return Days(isLeapYear() ? 366 : 365);
       }


      /**
       * Number of weeks in year.
       *
       * @return Number of weeks in year (52|53)
       */
      [[nodiscard]] constexpr auto getWeeksInYear() const noexcept -> Weeks
       {
        const long year = this->year - 1;
        const unsigned short decade = static_cast<unsigned short>(year - ((year / 100) * 100));
        // Formula from Ch. Zeller in 1877 optimized for 01.01.yyyy
        unsigned short wday = static_cast<unsigned short>((42 + decade + (decade / 4) - static_cast<unsigned short>(year / 100)) % 7);
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
        const Weekdays firstWeekday = Weekdays(wday);
        return Weeks(((firstWeekday == Weekdays::Thursday) || (isLeapYear() && (firstWeekday == Weekdays::Wednesday))) ? 53 : 52);
       }


      /**
       * ScaligerYear of this year.
       * 
       * @return ScaligerYear
       */
      [[nodiscard]] constexpr auto getScaligerYear() const -> ScaligerYear
       {
        return ScaligerYear(static_cast<long>(4713 + this->year));
       }


    private:
      const long year;

   };


  /** @relates JulianYear
   * Operator equal to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const JulianYear &lhs, const JulianYear &rhs) noexcept -> bool
   {
    return(lhs.getYear() == rhs.getYear());
   }


  /** @relates JulianYear
   * Operator not equal to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const JulianYear &lhs, const JulianYear &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates JulianYear
   * Operator smaller to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const JulianYear &lhs, const JulianYear &rhs) noexcept -> bool
   {
    return(lhs.getYear() < rhs.getYear());
   }


  /** @relates JulianYear
   * Operator greater to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const JulianYear &lhs, const JulianYear &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates JulianYear
   * Operator smaller or equal to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const JulianYear &lhs, const JulianYear &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates JulianYear
   * Operator greater or equal to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const JulianYear &lhs, const JulianYear &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates JulianYear
   * Operator plus to add a Years value to a Year (only if the result is smaller than 327671).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianYear object
   * @throws std::out_of_range When Year will become > 32767
   */
  [[nodiscard]] constexpr auto operator+(const JulianYear &lhs, const Years &rhs) -> JulianYear
   {
    if (rhs.getYears() > LONG_MAX - lhs.getYear())
     {
      throw std::out_of_range("year will be > LONG_MAX");
     }
    if (lhs.getYear() + rhs.getYears() > 32767)
     {
      throw std::out_of_range("year will be > 32767");
     }
    return(JulianYear(lhs.getYear() + rhs.getYears()));
   }


  /** @relates JulianYear
   * Operator minus to subtract a Years value from a Year (only if the result is greater than 8).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianYear object
   * @throws std::out_of_range When Year will become < 8
   */
  [[nodiscard]] constexpr auto operator-(const JulianYear &lhs, const Years &rhs) -> JulianYear
   {
    if (rhs.getYears() > lhs.getYear())
     {
      throw std::out_of_range("year will be < 0");
     }
    if (lhs.getYear() - rhs.getYears() < 8)
     {
      throw std::out_of_range("year will be < 8");
     }
    return(JulianYear(lhs.getYear() - rhs.getYears()));
   }


  /** @relates JulianYear
   * Operator minus to get the difference of a Year to another Year.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Years object
   */
  [[nodiscard]] constexpr auto operator-(const JulianYear &lhs, const JulianYear &rhs) noexcept -> Years
   {
    if (lhs < rhs)
     {
      return(Years(rhs.getYear() - lhs.getYear()));
     }
    return(Years(lhs.getYear() - rhs.getYear()));
   }


  /** @relates JulianYear
   * Stream operator to write a Year to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj JulianYear object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const JulianYear& obj) -> std::ostream&
   {
    os << "JulianYear(" << obj.getYear() << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_JULIANYEAR_H_
