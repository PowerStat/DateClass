/** @file
 * A Month is a numerical representation of a month within a year without being related to the year.
 * So it could have a value between 1 and 12.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_JULIANMONTH_H_
#define DATELIB_JULIANMONTH_H_


#include <ostream>
#include <stdexcept>
#include "Days.h"
#include "Months.h"
#include "JulianYear.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Value class that represents a month number (1-12) in the julian calendar system.
   */
  class JulianMonth final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] month Month number (1-12)
       * @throws std::out_of_range Month is < 1 or > 12
       */
      constexpr explicit JulianMonth(const unsigned short month)
       : leapYear(false), month(month)
       {
        if (month < 1 || month > 12)
         {
          throw std::out_of_range("month is < 1 or > 12");
         }
       }


      /**
       * Constructor.
       *
       * @param[in] year Year number (8-32767)
       * @param[in] month Month number (1-12)
       * @throws std::out_of_range Month is < 1 or > 12
       */
      constexpr explicit JulianMonth(const JulianYear year, const unsigned short month)
       : leapYear(year.isLeapYear()), month(month)
       {
        if (month < 1 || month > 12)
         {
          throw std::out_of_range("month is < 1 or > 12");
         }
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Month object to copy from.
       */
      constexpr JulianMonth(const JulianMonth &other) noexcept = default;

      /**
       * Move constructor.
       * 
       * @param[in] other Another Month object to move from.
       */
      constexpr JulianMonth(JulianMonth&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~JulianMonth() noexcept = default;

      /**
       * Assignment operator for another Month object.
       *
       * @param[in] other Another month object to be assigned to this object.
       */
      auto operator=(const JulianMonth &other) noexcept -> JulianMonth& = delete;

      /**
       * Move assignment operator for another Month object.
       * 
       * @param[in] other Another month object to be assigned to this object.
       * @return Month& 
       */
      auto operator=(JulianMonth&& other) noexcept -> JulianMonth& = delete;

      /**
       * Get month number as primitive data type.
       *
       * @return JulianMonth number (1-12)
       */
      [[nodiscard]] constexpr auto getMonth() const noexcept -> unsigned short
       {
        return(this->month);
       }


      /**
       * Get days in month.
       *
       * @return Days in month.
       */
      [[nodiscard]] constexpr auto getDaysInMonth() const -> Days
       {
        switch (month)
         {
          case  1 :
          case  3 :
          case  5 :
          case  7 :
          case  8 :
          case 10 :
          case 12 : 
            return Days(31);
          case  4 :
          case  6 :
          case  9 :
          case 11 : 
            return Days(30);
          case  2 : 
            return Days(this->leapYear ? 29 : 28);
          default:
            throw std::out_of_range("Illegal state month < 1 or month > 12");
         }
       }

    private:
      const bool leapYear;
      const unsigned short month;

   };


  /** @relates JulianMonth
   * Operator equal to compare two Month objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const JulianMonth &lhs, const JulianMonth &rhs) noexcept -> bool
   {
    return(lhs.getMonth() == rhs.getMonth());
   }


  /** @relates JulianMonth
   * Operator not equal to compare two Month objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const JulianMonth &lhs, const JulianMonth &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates JulianMonth
   * Operator smaller to compare two Month objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const JulianMonth &lhs, const JulianMonth &rhs) noexcept -> bool
   {
    return(lhs.getMonth() < rhs.getMonth());
   }


  /** @relates JulianMonth
   * Operator greater to compare two Month objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const JulianMonth &lhs, const JulianMonth &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates JulianMonth
   * Operator smaller or equal to compare two Month objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const JulianMonth &lhs, const JulianMonth &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates JulianMonth
   * Operator greater or equal to compare two Month objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const JulianMonth &lhs, const JulianMonth &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates JulianMonth
   * Operator plus to add a Months value to a Month (only if the result is smaller than 12).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianMonth object
   * @throws std::out_of_range When Month will become > 12
   */
  [[nodiscard]] constexpr auto operator+(const JulianMonth &lhs, const Months &rhs) -> JulianMonth
   {
    if (lhs.getMonth() + rhs.getMonths() > 12) // TODO overrun
     {
      throw std::out_of_range("month will be > 12");
     }
    return(JulianMonth(lhs.getMonth() + static_cast<unsigned short>(rhs.getMonths())));
   }


  /** @relates JulianMonth
   * Operator minus to subtract a Months value from a Month (only if the result is greater than 0).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JulianMonth object
   * @throws std::out_of_range When Month will become < 1
   */
  [[nodiscard]] constexpr auto operator-(const JulianMonth &lhs, const Months &rhs) -> JulianMonth
   {
    if (rhs.getMonths() >= lhs.getMonth())
     {
      throw std::out_of_range("month will be < 1");
     }
    return(JulianMonth(lhs.getMonth() - static_cast<unsigned short>(rhs.getMonths())));
   }


  /** @relates JulianMonth
   * Operator minus to get the difference of a Month value to another Month.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Months object
   */
  [[nodiscard]] constexpr auto operator-(const JulianMonth &lhs, const JulianMonth &rhs) noexcept -> Months
   {
    if (lhs < rhs)
     {
      return(Months(rhs.getMonth() - lhs.getMonth()));
     }
    return(Months(lhs.getMonth() - rhs.getMonth()));
   }


  /** @relates JulianMonth
   * Stream operator to write a Month to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj JulianMonth object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const JulianMonth& obj) -> std::ostream&
   {
    os << "JulianMonth(" << obj.getMonth() << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_JULIANMONTH_H_
