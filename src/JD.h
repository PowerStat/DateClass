/** @file
 * Julian date.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_JD_H_
#define DATELIB_JD_H_


#include <ostream>
#include <stdexcept>
#include <climits>
#include "Days.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Julian date.
   *
   * Starts at 12:00 January 1, 4713 BC.
   *
   * @see https://en.wikipedia.org/wiki/Julian_day
   */
  class JD final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] jd Number of days since beginning of this calendar system
       */
      constexpr explicit JD(const unsigned long jd) noexcept
       : jd(jd)
       {
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another JD object to copy from.
       */
      constexpr JD(const JD &other) noexcept = default;

      /**
       * Move constructor.
       * 
       * @param[in] other Another JD object to move from.
       */
      constexpr JD(JD&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~JD() noexcept = default;

      /**
       * Assignment operator for another JD object.
       *
       * @param[in] other Another JD object to be assigned to this object.
       */
      auto operator=(const JD &other) noexcept -> JD& = delete;
 
      /**
       * Move assignment operator for another JD object.
       * 
       * @param[in] other Another JD object to be assigned to this object.
       * @return JD& 
       */
      auto operator=(JD&& other) noexcept -> JD& = delete;


      /**
       * Get JD as primitive data type.
       *
       * @return JD number (0-ULONG_MAX)
       */
      [[nodiscard]] constexpr auto getJD() const noexcept -> unsigned long
       {
        return(this->jd);
       }

    private:
      const unsigned long jd;

   };


  /** @relates JD
   * Operator equal to compare two JD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const JD &lhs, const JD &rhs) noexcept -> bool
   {
    return(lhs.getJD() == rhs.getJD());
   }


  /** @relates JD
   * Operator not equal to compare two JD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const JD &lhs, const JD &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates JD
   * Operator smaller to compare two JD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const JD &lhs, const JD &rhs) noexcept -> bool
   {
    return(lhs.getJD() < rhs.getJD());
   }


  /** @relates JD
   * Operator greater to compare two JD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const JD &lhs, const JD &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates JD
   * Operator smaller or equal to compare two JD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const JD &lhs, const JD &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates JD
   * Operator greater or equal to compare two JD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const JD &lhs, const JD &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates JD
   * Operator plus to adds a Days value to a JD (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JD object
   * @throws std::out_of_range When JD will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator+(const JD &lhs, const Days &rhs) -> JD
   {
    if (rhs.getDays() > ULONG_MAX - lhs.getJD())
     {
      throw std::out_of_range("JD will be > ULONG_MAX");
     }
    return(JD(lhs.getJD() + rhs.getDays()));
   }


  /** @relates JD
   * Operator minus to subtract Days from a JD (only if the result is greater or equal to 0).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New JD object
   * @throws std::out_of_range When JD will become < 0
   */
  [[nodiscard]] constexpr auto operator-(const JD &lhs, const Days &rhs) -> JD
   {
    if (rhs.getDays() > lhs.getJD())
     {
      throw std::out_of_range("JD will be < 0");
     }
    return(JD(lhs.getJD() - rhs.getDays()));
   }


  /** @relates JD
   * Operator minus to get the difference JD from another JD.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Days object
   */
  [[nodiscard]] constexpr auto operator-(const JD &lhs, const JD &rhs) noexcept -> Days
   {
    if (rhs > lhs)
     {
      return(Days(rhs.getJD() - lhs.getJD()));
     }
    return(Days(lhs.getJD() - rhs.getJD()));
   }


  /** @relates JD
   * Stream operator to write a JD to an output stream.
   *
   * @param[in] outs Output stream
   * @param[in] obj JD object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& outs, const JD &obj) -> std::ostream&
   {
    outs << "JD(" << obj.getJD() << ")";
    return outs;
   }

 } // namespace

#endif // DATELIB_JD_H_
