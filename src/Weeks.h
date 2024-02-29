/** @file
 * A Weeks is a numerical representation of a number of weeks.
 * So it could have a value between 0 and ULONG_MAX.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_WEEKS_H_
#define DATELIB_WEEKS_H_


#include <ostream>
#include <stdexcept>
#include <climits>


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
 /**
  * Value class that represents a number of weeks (0 - ULONG_MAX).
  */
  class Weeks final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] weeks Number of weeks (0 - ULONG_MAX)
       */
      constexpr explicit Weeks(const unsigned long weeks) noexcept
       : weeks{weeks}
       {
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Weeks object to copy from.
       */
      constexpr Weeks(const Weeks &other) noexcept = default;

      /**
       * Move constructor.
       * 
       * @param[in] other Another Weeks object to move from.
       */
      constexpr Weeks(Weeks&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~Weeks() noexcept = default;

      /**
       * Assignment operator for another Weeks object.
       *
       * @param[in] other Another weeks object to be assigned to this object.
       */
      constexpr auto operator=(const Weeks &other) noexcept -> Weeks& = delete;

      /**
       * Move assignment operator for another Weeks object.
       * 
       * @param[in] other Another weeks object to be assigned to this object.
       * @return Weeks& 
       */
      constexpr auto operator=(Weeks&& other) noexcept -> Weeks& = delete;

      /**
       * Get number of weeks as primitive data type.
       *
       * @return Weeks number (0-ULONG_MAX)
       */
      [[nodiscard]] constexpr auto getWeeks() const noexcept -> unsigned long
       {
        return(this->weeks);
       }

    private:
      const unsigned long weeks;
   };


  /** @relates Weeks
   * Operator equal to compare two Weeks objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const Weeks &lhs, const Weeks &rhs) noexcept -> bool
   {
    return(lhs.getWeeks() == rhs.getWeeks());
   }


  /** @relates Weeks
   * Operator not equal to compare two Weeks objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const Weeks &lhs, const Weeks &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates Weeks
   * Operator smaller to compare two Weeks objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const Weeks &lhs, const Weeks &rhs) noexcept -> bool
   {
    return(lhs.getWeeks() < rhs.getWeeks());
   }


  /** @relates Weeks
   * Operator greater to compare two Weeks objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const Weeks &lhs, const Weeks &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates Weeks
   * Operator smaller or equal to compare two Weeks objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const Weeks &lhs, const Weeks &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates Weeks
   * Operator greater or equal to compare two Weeks objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const Weeks &lhs, const Weeks &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates Weeks
   * Operator plus to adds two Weeks values (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Weeks object
   * @throws std::out_of_range When Weeks will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator+(const Weeks &lhs, const Weeks &rhs) -> Weeks
   {
    if (rhs.getWeeks() > ULONG_MAX - lhs.getWeeks())
     {
      throw std::out_of_range("weeks will be > ULONG_MAX");
     }
    return(Weeks(lhs.getWeeks() + rhs.getWeeks()));
   }


  /** @relates Weeks
   *  Operator minus to get the difference of a Weeks value to another Weeks.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Weeks object
   */
  [[nodiscard]] constexpr auto operator-(const Weeks &lhs, const Weeks &rhs) noexcept -> Weeks
   {
    if (rhs > lhs)
     {
      return(Weeks(rhs.getWeeks() - lhs.getWeeks()));
     }
    return(Weeks(lhs.getWeeks() - rhs.getWeeks()));
   }


  /** @relates Weeks
   * Operator multiply to mutiply a Weeks value with a number  (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Weeks object
   * @throws std::out_of_range When Weeks will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator*(const Weeks &lhs, const unsigned long &rhs) -> Weeks
   {
    if (ULONG_MAX / lhs.getWeeks() < rhs) // TODO lhs = 0
     {
      throw std::out_of_range("weeks will be > ULONG_MAX");
     }
    return(Weeks(lhs.getWeeks() * rhs));
   }


  /** @relates Weeks
   * Operator div to divide a Weeks value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Weeks object
   * @throws std::out_of_range When the divisor is 0
   */
  [[nodiscard]] constexpr auto operator/(const Weeks &lhs, const unsigned long &rhs) -> Weeks
   {
    if (rhs == 0)
     {
      throw std::out_of_range("Division by zero");
     }
    return(Weeks(lhs.getWeeks() / rhs));
   }


  /** @relates Weeks
   * Operator remainder to remainder a Weeks value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Weeks object
   * @throws std::out_of_range When the divisor is 0
   */
  [[nodiscard]] constexpr auto operator%(const Weeks &lhs, const unsigned long &rhs) -> Weeks
   {
    if (rhs == 0)
     {
      throw std::out_of_range("Division by zero");
     }
    return(Weeks(lhs.getWeeks() % rhs));
   }


  /** @relates Weeks
   * Stream operator to write a Weeks to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj Weeks object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const Weeks &obj) -> std::ostream&
   {
    os << "Weeks(" << obj.getWeeks() << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_WEEKS_H_
