/** @file
 * A Months is a numerical representation of a number of months.
 * So it could have a value between 0 and ULONG_MAX.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_MONTHS_H_
#define DATELIB_MONTHS_H_


#include <ostream>
#include <stdexcept>
#include <climits>


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
 /**
  * Value class that represents a number of months (0 - ULONG_MAX).
  */
  class Months final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] months Number of months (0 - ULONG_MAX)
       */
      constexpr explicit Months(const unsigned long months) noexcept
       : months{months}
       {
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Months object to copy from.
       */
      constexpr Months(const Months &other) noexcept = default;

      /**
       * Move constructor.
       *
       * @param[in] other Another Months object to move from.
       */
      constexpr Months(Months&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~Months() noexcept = default;

      /**
       * Assignment operator for another Months object.
       *
       * @param[in] other Another months object to be assigned to this object.
       */
     auto operator=(const Months &other) & noexcept ->  Months& = delete;

      /**
       * Move assignment operator for another Months object.
       *
       * @param[in] other Another months object to be assigned to this object.
       * @return Months&
       */
      auto operator=(Months&& other) & noexcept -> Months& = delete;


      /**
       * Get number of months as primitive data type.
       *
       * @return Months number (0 - ULONG_MAX)
       */
      [[nodiscard]] constexpr auto getMonths() const noexcept -> unsigned long
       {
        return(this->months);
       }

    private:
      const unsigned long months;
   };


  /** @relates Months
   * Operator equal to compare two Months objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const Months &lhs, const Months &rhs) noexcept -> bool
   {
    return(lhs.getMonths() == rhs.getMonths());
   }


  /** @relates Months
   * Operator not equal to compare two Months objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const Months &lhs, const Months &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates Months
   * Operator smaller to compare two Months objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const Months &lhs, const Months &rhs) noexcept -> bool
   {
    return(lhs.getMonths() < rhs.getMonths());
   }


  /** @relates Months
   * Operator greater to compare two Months objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const Months &lhs, const Months &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates Months
   * Operator smaller or equal to compare two Months objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const Months &lhs, const Months &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates Months
   * Operator greater or equal to compare two Months objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const Months &lhs, const Months &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates Months
   * Operator plus to adds two Months values (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Months object
   * @throws std::out_of_range When Months will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator+(const Months &lhs, const Months &rhs) -> Months
   {
    if (rhs.getMonths() > ULONG_MAX - lhs.getMonths())
     {
      throw std::out_of_range("months will be > ULONG_MAX");
     }
    return(Months(lhs.getMonths() + rhs.getMonths()));
   }


  /** @relates Months
   * Operator minus to get the difference of a Months value to another Months.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Months object
   */
  [[nodiscard]] constexpr auto operator-(const Months &lhs, const Months &rhs) noexcept -> Months
   {
    if (rhs > lhs)
     {
      return(Months(rhs.getMonths() - lhs.getMonths()));
     }
    return(Months(lhs.getMonths() - rhs.getMonths()));
   }


  /** @relates Months
   * Operator multiply to mutiply a Months value with a number  (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Months object
   * @throws std::out_of_range When Months will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator*(const Months &lhs, const unsigned long &rhs) -> Months
   {
    if (ULONG_MAX / lhs.getMonths() < rhs) // lhs = 0
     {
      throw std::out_of_range("months will be > ULONG_MAX");
     }
    return(Months(lhs.getMonths() * rhs));
   }


  /** @relates Months
   * Operator div to divide a Months value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Months object
   * @throws std::out_of_range When the divisor is 0
   */
  [[nodiscard]] constexpr auto operator/(const Months &lhs, const unsigned long &rhs) -> Months
   {
    if (rhs == 0)
     {
      throw std::out_of_range("Division by zero");
     }
    return(Months(lhs.getMonths() / rhs));
   }


  /** @relates Months
   * Operator remainder to remainder a Months value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Months object
   * @throws std::out_of_range When the divisor is 0
   */
  [[nodiscard]] constexpr auto operator%(const Months &lhs, const unsigned long &rhs) -> Months
   {
    if (rhs == 0)
     {
      throw std::out_of_range("Division by zero");
     }
    return(Months(lhs.getMonths() % rhs));
   }


  /** @relates Months
   * Stream operator to write a Months to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj Months object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const Months &obj) -> std::ostream&
   {
    os << "Months(" << obj.getMonths() << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_MONTHS_H_
