/** @file
 * A Days is a numerical representation of a number of days.
 * So it could have a value between 0 and ULONG_MAX.
 *
 * Copyright (C) 2020-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_DAYS_H_
#define DATELIB_DAYS_H_


#include <ostream>
#include <stdexcept>
#include <climits>


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Value class that represents a number of days (0 - ULONG_MAX).
   */
  class Days final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] days Number of days (0 - ULONG_MAX)
       */
      constexpr explicit Days(const unsigned long days) noexcept
       : days{days}
       {
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Days object to copy from.
       */
      constexpr Days(const Days& other) noexcept = default;

      /**
       * Move constructor.
       *
       * @param[in] other Another Days object to move from.
       */
      constexpr Days(Days&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~Days() noexcept = default;

      /**
       * Assignment operator for another Days object.
       *
       * @param[in] other Another days object to be assigned to this object.
       * @return Days
       */
      auto operator=(const Days &other) & noexcept -> Days& = delete;

      /**
       * Move assignment operator for another Days object.
       *
       * @param[in] other Another days object to be assigned to this object.
       * @return Days&
       */
      auto operator=(Days&& other) & noexcept -> Days& = delete;


      /**
       * Get number of days as primitive data type.
       *
       * @return Days number (0-ULONG_MAX)
       */
      [[nodiscard]] constexpr auto getDays() const noexcept -> unsigned long
       {
        return(this->days);
       }

    private:
      const unsigned long days;
   };


  /** @relates Days
   * Operator equal to compare two Days objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const Days &lhs, const Days &rhs) noexcept -> bool
   {
    return(lhs.getDays() == rhs.getDays());
   }


  /** @relates Days
   * Operator not equal to compare two Days objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const Days &lhs, const Days &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates Days
   * Operator smaller to compare two Days objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const Days &lhs, const Days &rhs) noexcept -> bool
   {
    return(lhs.getDays() < rhs.getDays());
   }


  /** @relates Days
   * Operator greater to compare two Days objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const Days &lhs, const Days &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates Days
   * Operator smaller or equal to compare two Days objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const Days &lhs, const Days &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates Days
   * Operator greater or equal to compare two Days objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const Days &lhs, const Days &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /* C++20
  std::strong_ordering operator<=>(const Days &lhs, const Days &rhs) noexcept;
  */


  /** @relates Days
   * Operator plus to adds two Days values (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Days object
   * @throws std::out_of_range When Days will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator+(const Days &lhs, const Days &rhs) -> Days
   {
    if (rhs.getDays() > ULONG_MAX - lhs.getDays())
     {
      throw std::out_of_range("days will be > ULONG_MAX");
     }
    return(Days(lhs.getDays() + rhs.getDays()));
   }


  /** @relates Days
   * Operator minus to get the difference of a Days value to another Days.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Days object
   */
  [[nodiscard]] constexpr auto operator-(const Days &lhs, const Days &rhs) noexcept -> Days
   {
    if (rhs > lhs)
     {
      return(Days(rhs.getDays() - lhs.getDays()));
     }
    return(Days(lhs.getDays() - rhs.getDays()));
   }


  /** @relates Days
   * Operator multiply to mutiply a Days value with a number  (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Days object
   * @throws std::out_of_range When Days will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator*(const Days &lhs, const unsigned long &rhs) -> Days
   {
    if (ULONG_MAX / lhs.getDays() < rhs) // TODO lhs = 0
     {
      throw std::out_of_range("days will be > ULONG_MAX");
     }
    return(Days(lhs.getDays() * rhs));
   }


  /** @relates Days
   * Operator div to divide a Days value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object > 0
   * @return New Days object
   * @throws std::out_of_range When the divisor is 0
   */
  [[nodiscard]] constexpr auto operator/(const Days &lhs, const unsigned long &rhs) -> Days
   {
    if (rhs == 0)
     {
      throw std::out_of_range("Division by zero");
     }
    return(Days(lhs.getDays() / rhs));
   }


  /** @relates Days
   * Operator remainder to remainder a Days value with a number.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object > 0
   * @return New Days object
   * @throws std::out_of_range When the divisor is 0
   */
  [[nodiscard]] constexpr auto operator%(const Days &lhs, const unsigned long &rhs) -> Days
   {
    if (rhs == 0)
     {
      throw std::out_of_range("Division by zero");
     }
    return(Days(lhs.getDays() % rhs));
   }


  /** @relates Days
   * Stream operator to write a Days to an output stream.
   *
   * @param[in] outs Output stream
   * @param[in] obj Days object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& outs, const Days &obj) -> std::ostream&
   {
    outs << "Days(" << obj.getDays() << ")";
    return outs;
   }


  // TODO static Days read(std::istream& is);

 } // namespace

#endif // DATELIB_DAYS_H_
