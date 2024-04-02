/** @file
 * A ScaligerYear is a numerical representation of year.
 * So it could have a value between 0 and ULONG_MAX.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef SCALIGERYEAR_H_
#define SCALIGERYEAR_H_


#include <ostream>
#include <stdexcept>
#include <climits>
#include "Years.h"
#include "JD.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Value class that represents a ScaligerYear (4707 - 6295).
   */
  class ScaligerYear final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] year Year number (4707 - 6295)
       * @throws std::out_of_range Year is < 4707 or > 6295
       */
      constexpr explicit ScaligerYear(const long year)
       : year(year)
       {
        if (year < 4707 || year > 6295)
         {
          throw std::out_of_range("year is < 4707 or > 6295");
         }
       }


       /**
        * Constructor.
        *
        * @param[in] jd Julian date
        * @throws std::out_of_range if jd is < 1718867 or > 2298884
        */
       constexpr explicit ScaligerYear(const JD& jd)
        : year([](const JD& jd) constexpr -> const long {if (jd.getJD() < 1718867 || jd.getJD() > 2298884) {throw std::out_of_range("jd is < 1718867 or > 2298884");} unsigned long sy = (jd.getJD() / 365) - 2; if (sy > 5837) {--sy;} if (const unsigned long jd2 = (sy - 1) * 365 + (sy + 2) / 4; jd.getJD() < jd2) {--sy;} return sy;}(jd))
        {
        }


       /**
        * Copy constructor.
        *
        * @param[in] other Another Year object to copy from.
        */
      constexpr ScaligerYear(const ScaligerYear &other) noexcept = default;

      /**
       * Move constructor.
       *
       * @param[in] other Another Year object to move from.
       */
      constexpr ScaligerYear(ScaligerYear&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~ScaligerYear() noexcept = default;

      /**
       * Assignment operator for another Year object.
       *
       * @param[in] other Another year object to be assigned to this object.
       * @return ScaligerYear
       */
      auto operator=(const ScaligerYear &other) & noexcept -> ScaligerYear& = delete;

      /**
       * Move assignment operator for another Year object.
       *
       * @param[in] other Another year object to be assigned to this object.
       * @return ScaligerYear&
       */
      auto operator=(ScaligerYear&& other) & noexcept -> ScaligerYear& = delete;


      /**
       * Get year number as primitive data type.
       *
       * @return ScaligerYear number (? - ?)
       */
      [[nodiscard]] constexpr auto getYear() const noexcept -> long
       {
        return(this->year);
       }


      /**
       * Get the JD of this ScaligerYear.
       *
       * @return JD
       */
      [[nodiscard]] constexpr auto getJD() const noexcept -> JD
       {
        const unsigned long ret = (static_cast<unsigned long>(this->year) - 1) * 365 + (static_cast<unsigned long>(this->year) + 2) / 4;
        return(JD(ret));
       }

    private:
      const long year;

   };


  /** @relates ScaligerYear
   * Operator equal to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const ScaligerYear &lhs, const ScaligerYear &rhs) noexcept -> bool
   {
    return(lhs.getYear() == rhs.getYear());
   }


  /** @relates ScaligerYear
   * Operator not equal to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const ScaligerYear &lhs, const ScaligerYear &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates ScaligerYear
   * Operator smaller to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const ScaligerYear &lhs, const ScaligerYear &rhs) noexcept -> bool
   {
    return(lhs.getYear() < rhs.getYear());
   }


  /** @relates ScaligerYear
   * Operator greater to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const ScaligerYear &lhs, const ScaligerYear &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates ScaligerYear
   * Operator smaller or equal to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const ScaligerYear &lhs, const ScaligerYear &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates ScaligerYear
   * Operator greater or equal to compare two Year objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const ScaligerYear &lhs, const ScaligerYear &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates ScaligerYear
   * Operator plus to add a Years value to a Year (only if the result is smaller than 6295).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New ScaligerYear object
   * @throws std::out_of_range When Year will become > 6295
   */
  [[nodiscard]] constexpr auto operator+(const ScaligerYear &lhs, const Years &rhs) -> ScaligerYear
   {
    if (rhs.getYears() > LONG_MAX - lhs.getYear())
     {
      throw std::out_of_range("year will be > LONG_MAX");
     }
    if (lhs.getYear() + rhs.getYears() > 6295)
     {
      throw std::out_of_range("year will be > 6295");
     }
    return(ScaligerYear(lhs.getYear() + rhs.getYears()));
   }


  /** @relates ScaligerYear
   * Operator minus to subtract a Years value from a Year (only if the result is greater than 8).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New ScaligerYear object
   * @throws std::out_of_range When Year will become < 4707
   */
  [[nodiscard]] constexpr auto operator-(const ScaligerYear &lhs, const Years &rhs) -> ScaligerYear
   {
    if (lhs.getYear() < rhs.getYears())
     {
      throw std::out_of_range("year will be < 0");
     }
    if (lhs.getYear() - rhs.getYears() < 4707)
     {
      throw std::out_of_range("year will be < 4707");
     }
    return(ScaligerYear(lhs.getYear() - rhs.getYears()));
   }


  /** @relates ScaligerYear
   * Operator minus to diff a Year value from another Year.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Years object
   */
  [[nodiscard]] constexpr auto operator-(const ScaligerYear &lhs, const ScaligerYear &rhs) noexcept -> Years
   {
    if (lhs < rhs)
     {
      return(Years(rhs.getYear() - lhs.getYear()));
     }
    return(Years(lhs.getYear() - rhs.getYear()));
   }


  /** @relates ScaligerYear
   * Stream operator to write a Year to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj ScaligerYear object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const ScaligerYear& obj) -> std::ostream&
   {
    os << "ScaligerYear(" << obj.getYear() << ")";
    return os;
   }

 } // namespace

#endif // SCALIGERYEAR_H_
