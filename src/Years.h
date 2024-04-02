/** @file
 * A Years is a numerical representation of a number of years.
 * So it could have a value between 0 and ULONG_MAX.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_YEARS_H_
#define DATELIB_YEARS_H_


#include <ostream>
#include <stdexcept>
#include <climits>


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
 /**
  * Value class that represents a number of years (0 - ULONG_MAX).
  */
  class Years final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] years Number of years (0 - ULONG_MAX)
       */
      constexpr explicit Years(const unsigned long years) noexcept
       : years{years}
       {
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Years object to copy from.
       */
      constexpr Years(const Years &other) noexcept = default;

      /**
       * Move constructor.
       *
       * @param[in] other Another Years object to move from.
       */
      constexpr Years(Years&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~Years() noexcept = default;

      /**
       * Assignment operator for another Years object.
       *
       * @param[in] other Another years object to be assigned to this object.
       */
      auto operator=(const Years &other) & noexcept -> Years& = delete;

      /**
       * Move assignment operator for another Years object.
       *
       * @param[in] other Another years object to be assigned to this object.
       * @return Years&
       */
      auto operator=(Years&& other) & noexcept -> Years& = delete;


      /**
       * Get number of years as primitive data type.
       *
       * @return Years number (0-ULONG_MAX)
       */
      [[nodiscard]] constexpr auto getYears() const noexcept -> unsigned long
       {
        return(this->years);
       }

    private:
      const unsigned long years;
   };


  /** @relates Years
   * Operator equal to compare two Years objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const Years &lhs, const Years &rhs) noexcept -> bool
   {
    return(lhs.getYears() == rhs.getYears());
   }


  /** @relates Years
   * Operator not equal to compare two Years objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const Years &lhs, const Years &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates Years
   * Operator smaller to compare two Years objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const Years &lhs, const Years &rhs) noexcept -> bool
   {
    return(lhs.getYears() < rhs.getYears());
   }


  /** @relates Years
   * Operator greater to compare two Years objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const Years &lhs, const Years &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates Years
   * Operator smaller or equal to compare two Years objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const Years &lhs, const Years &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates Years
   * Operator greater or equal to compare two Years objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const Years &lhs, const Years &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates Years
   * Operator plus to adds two Years values (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Years object
   * @throws std::out_of_range When Years will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator+(const Years &lhs, const Years &rhs) -> Years
   {
    if (rhs.getYears() > ULONG_MAX - lhs.getYears())
     {
      throw std::out_of_range("years will be > ULONG_MAX");
     }
    return(Years(lhs.getYears() + rhs.getYears()));
   }


  /** @relates Years
   * Operator minus to subtract a Years value from another Years (only if the result is greater or equal to 0).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Years object
   */
  [[nodiscard]] constexpr auto operator-(const Years &lhs, const Years &rhs) noexcept -> Years
   {
    if (rhs > lhs)
     {
      return(Years(rhs.getYears() - lhs.getYears()));
     }
    return(Years(lhs.getYears() - rhs.getYears()));
   }


  /** @relates Years
   * Operator multiply to mutiply a Years value with a number  (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Years object
   * @throws std::out_of_range When Years will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator*(const Years &lhs, const unsigned long &rhs) -> Years
   {
    if (ULONG_MAX / lhs.getYears() < rhs) // TODO lhs = 0
     {
      throw std::out_of_range("years will be > ULONG_MAX");
     }
    return(Years(lhs.getYears() * rhs));
   }


  /** @relates Years
   * Operator div to divide a Years value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Years object
   * @throws std::out_of_range When the divisor is 0
   */
  [[nodiscard]] constexpr auto operator/(const Years &lhs, const unsigned long &rhs) -> Years
   {
    if (rhs == 0)
     {
      throw std::out_of_range("Division by zero");
     }
    return(Years(lhs.getYears() / rhs));
   }


  /** @relates Years
   * Operator remainder to remainder a Years value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Years object
   * @throws std::out_of_range When the divisor is 0
   */
  [[nodiscard]] constexpr auto operator%(const Years &lhs, const unsigned long &rhs) -> Years
   {
    if (rhs == 0)
     {
      throw std::out_of_range("Division by zero");
     }
    return(Years(lhs.getYears() % rhs));
   }


  /** @relates Years
   * Stream operator to write a Years to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj Years object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const Years &obj) -> std::ostream&
   {
    os << "Years(" << obj.getYears() << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_YEARS_H_
