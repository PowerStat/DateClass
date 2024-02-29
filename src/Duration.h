/** @file
 * A Duration is a numerical representation of Days, Months and Years.
 *
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_DURATION_H_
#define DATELIB_DURATION_H_


#include <ostream>
#include <stdexcept>
#include <climits>
#include "Days.h"
#include "Months.h"
#include "Years.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Value class that represents a duration in days, months and years.
   */
  class Duration final
   {
    public:
      /**
       * Constructor.
       *
       * Optimizes months > 12 to years.
       *
       * @param[in] years Years (0 - ULONG_MAX)
       * @param[in] months Months (0-11)
       * @param[in] days Days (0-30)
       * @throws std::out_of_range When days > 31 or years will become > ULONG_MAX
       */
      constexpr explicit Duration(const Years years, const Months months, const Days days)
       : years{[](const Months months, const Years years) constexpr -> const Years {unsigned long newYears = years.getYears(); unsigned long newMonths = months.getMonths(); while (newMonths >= 12) {newMonths -= 12; if (newYears == ULONG_MAX) {throw std::out_of_range("years must be <= ULONG_MAX");} ++newYears;} return Years(newYears);}(months, years)},
         months{[](const Months months) constexpr -> const Months {unsigned long newMonths = months.getMonths(); while (newMonths >= 12) {newMonths -= 12;} return Months(newMonths);}(months)}, 
         days{[](const Days days) constexpr -> const Days {if (days.getDays() >= 31) {throw std::out_of_range("days must be < 31");} return days;}(days)}
       {
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Duration object to copy from.
       */
      constexpr Duration(const Duration &other) noexcept = default;

      /**
       * Move constructor.
       * 
       * @param[in] other Another Duration object to move from.
       */
      constexpr Duration(Duration&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~Duration() noexcept = default;

      /**
       * Assignment operator for another Duration object.
       *
       * @param[in] other Another duration object to be assigned to this object.
       */
      auto operator=(const Duration &other) noexcept -> Duration& = delete;

      /**
       * Move assignment operator for another Duration object.
       * 
       * @param[in] other Another duration object to be assigned to this object.
       * @return Duration& 
       */
      auto operator=(Duration&& other) noexcept -> Duration& = delete;


      /**
       * Get years as data type.
       *
       * @return Years
       */
      [[nodiscard]] constexpr auto getYears() const noexcept -> Years
       {
        return(this->years);
       }


      /**
       * Get months as data type.
       *
       * @return Months
       */
      [[nodiscard]] constexpr auto getMonths() const noexcept -> Months
       {
        return(this->months);
       }


      /**
       * Get days as data type.
       *
       * @return Days
       */
      [[nodiscard]] constexpr auto getDays() const noexcept -> Days
       {
        return(this->days);
       }

    private:
      const Years years;
      const Months months;
      const Days days;
   };


  /** @relates Duration
   * Operator equal to compare two Duration objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  constexpr auto operator==(const Duration &lhs, const Duration &rhs) noexcept -> bool
   {
    return((lhs.getYears() == rhs.getYears()) && (lhs.getMonths() == rhs.getMonths()) && (lhs.getDays() == rhs.getDays()));
   }


  /** @relates Duration
   * Operator not equal to compare two Duration objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  constexpr auto operator!=(const Duration &lhs, const Duration &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates Duration
   * Operator smaller to compare two Duration objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  constexpr auto operator<(const Duration &lhs, const Duration &rhs) noexcept -> bool
   {
    bool result = lhs.getYears() < rhs.getYears();
    if (!result)
     {
      result = lhs.getMonths() < rhs.getMonths();
      if (!result)
       {
        result = lhs.getDays() < rhs.getDays();
       }
     }
    return(result);
   }


  /** @relates Duration
   * Operator greater to compare two Duration objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  constexpr auto operator>(const Duration &lhs, const Duration &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates Duration
   * Operator smaller or equal to compare two Duration objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  constexpr auto operator<=(const Duration &lhs, const Duration &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates Duration
   * Operator greater or equal to compare two Duration objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  constexpr auto operator>=(const Duration &lhs, const Duration &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates Duration
   * Operator plus to adds two Duration values.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   * @throws std::out_of_range When Duration will become out of range in any of it's parts
   */
  constexpr auto operator+(const Duration &lhs, const Duration &rhs) -> Duration
   {
    return(Duration(lhs.getYears() + rhs.getYears(), lhs.getMonths() + rhs.getMonths(), lhs.getDays() + rhs.getDays()));
   }


  /** @relates Duration
   * Operator minus to subtract a Duration value from another Duration.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   */
  constexpr auto operator-(const Duration &lhs, const Duration &rhs) -> Duration
   {
    return(Duration(lhs.getYears() - rhs.getYears(), lhs.getMonths() - rhs.getMonths(), lhs.getDays() - rhs.getDays()));
   }


  /** @relates Duration
   * Operator multiply to mutiply a Duration value with a number  (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   * @throws std::out_of_range When one Duration value will become > ULONG_MAX
   */
  constexpr auto operator*(const Duration &lhs, const unsigned long &rhs) -> Duration
   {
    return(Duration(lhs.getYears() * rhs, lhs.getMonths() * rhs, lhs.getDays() * rhs));
   }


  /** @relates Duration
   * Operator div to divide a Duration value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   */
  constexpr auto operator/(const Duration &lhs, const unsigned long &rhs) -> Duration
   {
    return(Duration(lhs.getYears() / rhs, lhs.getMonths() / rhs, lhs.getDays() / rhs));
   }


  /** @relates Duration
   * Operator remainder to remainder a Duration value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   */
  constexpr auto operator%(const Duration &lhs, const unsigned long &rhs) -> Duration
   {
    return(Duration(lhs.getYears() % rhs, lhs.getMonths() % rhs, lhs.getDays() % rhs));
   }


  /** @relates Duration
   * Operator plus to adds Days to a Duration.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   * @throws std::out_of_range When the Days of the Duration will be > 31
   */
  constexpr auto operator+(const Duration &lhs, const Days &rhs) -> Duration
   {
    return(Duration(lhs.getYears(), lhs.getMonths(), lhs.getDays() + rhs));
   }


  /** @relates Duration
   * Operator minus to subtract a Days value from a Duration.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   */
  constexpr auto operator-(const Duration &lhs, const Days &rhs) -> Duration
   {
    return(Duration(lhs.getYears(), lhs.getMonths(), lhs.getDays() - rhs));
   }


  /** @relates Duration
   * Operator plus to adds Months to a Duration.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   * @throws std::out_of_range When the Years will become > ULONG_MAX
   */
  constexpr auto operator+(const Duration &lhs, const Months &rhs) -> Duration
   {
    return(Duration(lhs.getYears(), lhs.getMonths() + rhs, lhs.getDays()));
   }


  /** @relates Duration
   * Operator minus to subtract a Months value from a Duration.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   */
  constexpr auto operator-(const Duration &lhs, const Months &rhs) -> Duration
   {
    if (lhs.getMonths() < rhs)
     {
      const Months tempMonths = rhs - lhs.getMonths();
      unsigned long months =  tempMonths.getMonths();
      unsigned long years = lhs.getYears().getYears();
      unsigned long newYears = 1;
      while (months > 12)
       {
        months -= 12;
        ++newYears;
       }
      if (years < newYears)
       {
        years = newYears - years - 1;
       }
      else
       {
        years -= newYears;
        months = 12 - months;
       }
      return(Duration(Years(years), Months(months), lhs.getDays()));
     }
    return(Duration(lhs.getYears(), lhs.getMonths() - rhs, lhs.getDays()));
   }


  /** @relates Duration
   * Operator plus to adds Years to a Duration.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   * @throws std::out_of_range When the Years will become > ULONG_MAX
   */
  constexpr auto operator+(const Duration &lhs, const Years &rhs) -> Duration
   {
    return(Duration(lhs.getYears() + rhs, lhs.getMonths(), lhs.getDays()));
   }


  /** @relates Duration
   * Operator minus to subtract Years from a Duration.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Duration object
   * @throws std::out_of_range When Years will become < 0
   */
  constexpr auto operator-(const Duration &lhs, const Years &rhs) -> Duration
   {
    if (lhs.getYears() < rhs)
     {
      throw std::out_of_range("years will be < 0");
     }
    return(Duration(lhs.getYears() - rhs, lhs.getMonths(), lhs.getDays()));
   }


  /** @relates Duration
   * Stream operator to write a Duration to an output stream.
   *
   * @param[in] outs Output stream
   * @param[in] obj Duration object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& outs, const Duration &obj) -> std::ostream&
   {
    outs << "Duration(" << obj.getYears() << ", " << obj.getMonths() << ", " << obj.getDays() << ")";
    return outs;
   }

 } // namespace

#endif // DATELIB_DURATION_H_
