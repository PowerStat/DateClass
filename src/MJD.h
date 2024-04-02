/** @file
 * Modified julian date.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_MJD_H_
#define DATELIB_MJD_H_


#include <ostream>
#include <stdexcept>
#include <climits>
#include "Days.h"
#include "JD.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Modified julian date.
   *
   * Starts at 0:00 November 17, 1858.
   *
   * @see https://en.wikipedia.org/wiki/Julian_day
   */
  class MJD final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] mjd Number of days since beginning of MJD
       */
      constexpr explicit MJD(const unsigned long mjd) noexcept
       : mjd(mjd)
       {
       }


      /**
       * Constructor.
       *
       * @param[in] jd Number of days since beginning of JD
       * @throws std::out_of_range When jd is < 2400001
       */
      constexpr explicit MJD(const JD& jd)
       : mjd([](const JD& jd) constexpr -> const unsigned long {if (jd.getJD() < 2400001UL) {throw std::out_of_range("JD must be >= 2400001");} return (jd.getJD() - 2400001UL);}(jd))
       {
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another MJD object to copy from.
       */
      constexpr MJD(const MJD &other) noexcept = default;

      /**
       * Move constructor.
       *
       * @param[in] other Another MJD object to move from.
       */
      constexpr MJD(MJD&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~MJD() noexcept = default;

      /**
       * Assignment operator for another MJD object.
       *
       * @param[in] other Another MJD object to be assigned to this object.
       */
      auto operator=(const MJD &other) & -> MJD& = delete;

      /**
       * Move assignment operator for another MJD object.
       *
       * @param[in] other Another MJD object to be assigned to this object.
       * @return MJD&
       */
      auto operator=(MJD&& other) & noexcept -> MJD& = delete;

      /**
       * Get MJD as primitive data type.
       *
       * @return MJD number (0-ULONG_MAX)
       */
      [[nodiscard]] constexpr auto getMJD() const noexcept -> unsigned long
       {
        return(this->mjd);
       }


      /**
       * Get JD datat type.
       *
       * @return JD
       * @throws std::out_of_range When mjd is >= ULONG_MAX - 2400001
       */
      [[nodiscard]] constexpr auto getJD() const -> JD
       {
        if (this->mjd > ULONG_MAX - 2400001UL)
         {
          throw std::out_of_range("MJD must be < ULONG_MAX - 2400001");
         }
        return JD(this->mjd + 2400001UL);
       }

    private:
      const unsigned long mjd;

   };


  /** @relates MJD
   * Operator equal to compare two MJD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const MJD &lhs, const MJD &rhs)  -> bool
   {
    return(lhs.getMJD() == rhs.getMJD());
   }


  /** @relates MJD
   * Operator not equal to compare two MJD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const MJD &lhs, const MJD &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates MJD
   * Operator smaller to compare two MJD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const MJD &lhs, const MJD &rhs) noexcept -> bool
   {
    return(lhs.getMJD() < rhs.getMJD());
   }


  /** @relates MJD
   * Operator greater to compare two MJD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const MJD &lhs, const MJD &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates MJD
   * Operator smaller or equal to compare two MJD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const MJD &lhs, const MJD &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates MJD
   * Operator greater or equal to compare two MJD objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const MJD &lhs, const MJD &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates MJD
   * Operator plus to adds a Days value to a MJD (only if the result is smaller than ULONG_MAX).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New MJD object
   * @throws std::out_of_range When MJD will become > ULONG_MAX
   */
  [[nodiscard]] constexpr auto operator+(const MJD &lhs, const Days &rhs) -> MJD
   {
    if (rhs.getDays() > ULONG_MAX - lhs.getMJD())
     {
      throw std::out_of_range("MJD will be > ULONG_MAX");
     }
    return(MJD(lhs.getMJD() + rhs.getDays()));
   }


  /** @relates MJD
   * Operator minus to subtract Days from a MJD (only if the result is greater or equal to 0).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New MJD object
   * @throws std::out_of_range When MJD will become < 0
   */
  [[nodiscard]] constexpr auto operator-(const MJD &lhs, const Days &rhs) -> MJD
   {
    if (rhs.getDays() > lhs.getMJD())
     {
      throw std::out_of_range("MJD will be < 0");
     }
    return(MJD(lhs.getMJD() - rhs.getDays()));
   }


  /** @relates MJD
   * Operator minus to get the diff between a MJD and another MJD.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Days object
   */
  [[nodiscard]] constexpr auto operator-(const MJD &lhs, const MJD &rhs) noexcept -> Days
   {
    if (rhs > lhs)
     {
      return(Days(rhs.getMJD() - lhs.getMJD()));
     }
    return(Days(lhs.getMJD() - rhs.getMJD()));
   }


  /** @relates MJD
   * Stream operator to write a MJD to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj JD object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const MJD &obj) -> std::ostream&
   {
    os << "MJD(" << obj.getMJD() << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_MJD_H_
