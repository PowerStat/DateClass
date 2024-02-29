/** @file
 * A Week is a numerical representation of a week within a year without being related to the year.
 * So it could have a value between 1 and 53.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_JULIANWEEK_H_
#define DATELIB_JULIANWEEK_H_


#include <ostream>
#include <stdexcept>
#include <string>
#include "Weeks.h"
#include "JulianYear.h"


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
  /**
   * Value class that represents a week number (1-53) in the julian calendar system.
   */
  class JulianWeek final
   {
    public:
      /**
       * Constructor.
       *
       * @param[in] week Day number (1-53)
       * @throws std::out_of_range Day is < 1 or > 53
       */
      constexpr explicit JulianWeek(const unsigned short week)
       : week(week), maxWeeks(53UL)
       {
        if (week < 1 || week > 53)
         {
          throw std::out_of_range("week is < 1 or > 53");
         }
       }


      /**
       * Constructor.
       *
       * @param[in] week Day number (1 - max weeks in year) depending on the year
       * @param[in] year Year
       * @throws std::out_of_range Week is < 1 or > max weeks in year
       */
      constexpr explicit JulianWeek(const unsigned short week, const JulianYear year)
       : week(week), maxWeeks{year.getWeeksInYear().getWeeks()}
       {
        if (week < 1 || week > this->maxWeeks)
         {
          throw std::out_of_range("week is < 1 or > " + std::to_string(this->maxWeeks));
         }
       }


      /**
       * Copy constructor.
       *
       * @param[in] other Another Week object to copy from.
       */
      constexpr JulianWeek(const JulianWeek &other) noexcept = default;

      /**
       * Move constructor.
       * 
       * @param[in] other Another Week object to move from.
       */
      constexpr JulianWeek(JulianWeek&& other) noexcept = default;

      /**
       * Destructor.
       */
      ~JulianWeek() noexcept = default;

      /**
       * Assignment operator for another Week object.
       *
       * @param[in] other Another week object to be assigned to this object.
       */
      auto operator=(const JulianWeek &other) noexcept -> JulianWeek& = delete;

      /**
       * Move assignment operator for another Week object.
       * 
       * @param[in] other Another week object to be assigned to this object.
       * @return JulianWeek& 
       */
      auto operator=(JulianWeek&& other) noexcept -> JulianWeek& = delete;


      /**
       * Get week number as primitive data type.
       *
       * @return Week number (1-53)
       */
      [[nodiscard]] constexpr auto getWeek() const noexcept -> unsigned short
       {
        return(this->week);
       }


      /**
       * Get maximum weeks as primitive data type.
       *
       * @return Maximum Weeks (52/53)
       */
      [[nodiscard]] constexpr auto getMaxWeeks() const noexcept -> unsigned long
       {
        return(this->maxWeeks);
       }

    private:
      const unsigned short week;
      const unsigned long maxWeeks;

   };


  /** @relates JulianWeek
   * Operator equal to compare two Week objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are equal in value.
   */
  [[nodiscard]] constexpr auto operator==(const JulianWeek &lhs, const JulianWeek &rhs) noexcept -> bool
   {
    return(lhs.getWeek() == rhs.getWeek());
   }


  /** @relates JulianWeek
   * Operator not equal to compare two Week objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs and rhs are not equal in value.
   */
  [[nodiscard]] constexpr auto operator!=(const JulianWeek &lhs, const JulianWeek &rhs) noexcept -> bool
   {
    return(!(lhs == rhs));
   }


  /** @relates JulianWeek
   * Operator smaller to compare two Week objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller than rhs.
   */
  [[nodiscard]] constexpr auto operator<(const JulianWeek &lhs, const JulianWeek &rhs) noexcept -> bool
   {
    return(lhs.getWeek() < rhs.getWeek());
   }


  /** @relates JulianWeek
   * Operator greater to compare two Week objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater than rhs.
   */
  [[nodiscard]] constexpr auto operator>(const JulianWeek &lhs, const JulianWeek &rhs) noexcept -> bool
   {
    return(rhs < lhs);
   }


  /** @relates JulianWeek
   * Operator smaller or equal to compare two Week objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is smaller or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator<=(const JulianWeek &lhs, const JulianWeek &rhs) noexcept -> bool
   {
    return(!(lhs > rhs));
   }


  /** @relates JulianWeek
   * Operator greater or equal to compare two Week objects.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return true when lhs is greater or equal than rhs.
   */
  [[nodiscard]] constexpr auto operator>=(const JulianWeek &lhs, const JulianWeek &rhs) noexcept -> bool
   {
    return(!(lhs < rhs));
   }


  /** @relates JulianWeek
   * Operator plus to add a Weeks value to a Week (only if the result is smaller than 53).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Week object
   * @throws std::out_of_range When Week will become > 53
   */
  [[nodiscard]] constexpr auto operator+(const JulianWeek &lhs, const Weeks &rhs) -> JulianWeek
   {
    if (lhs.getWeek() + rhs.getWeeks() > lhs.getMaxWeeks())
     {
      throw std::out_of_range("week will be > " + std::to_string(lhs.getMaxWeeks()));
     }
    return(JulianWeek(lhs.getWeek() + static_cast<unsigned short>(rhs.getWeeks())));
   }


  /** @relates JulianWeek
   * Operator minus to subtract a Weeks value from a Week (only if the result is greater than 0).
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Week object
   * @throws std::out_of_range When Week will become < 1
   */
  [[nodiscard]] constexpr auto operator-(const JulianWeek &lhs, const Weeks &rhs) -> JulianWeek
   {
    if (rhs.getWeeks() >= lhs.getWeek())
     {
      throw std::out_of_range("week will be < 1");
     }
    return(JulianWeek(lhs.getWeek() - static_cast<unsigned short>(rhs.getWeeks())));
   }


  /** @relates JulianWeek
   * Operator minus to get the difference of a Week value to another Week.
   *
   * @param[in] lhs Left hand side object
   * @param[in] rhs Right hand side object
   * @return New Weeks object
   */
  [[nodiscard]] constexpr auto operator-(const JulianWeek &lhs, const JulianWeek &rhs) noexcept -> Weeks
   {
    if (lhs < rhs)
     {
      return(Weeks(rhs.getWeek() - lhs.getWeek()));
     }
    return(Weeks(lhs.getWeek() - rhs.getWeek()));
   }


  /** @relates JulianWeek
   * Stream operator to write a JulianWeek to an output stream.
   *
   * @param[in] os Output stream
   * @param[in] obj JulianWeek object to write to the output stream
   * @return Output stream
   */
  inline auto operator<<(std::ostream& os, const JulianWeek& obj) -> std::ostream&
   {
    os << "JulianWeek(" << obj.getWeek() << ")";
    return os;
   }

 } // namespace

#endif // DATELIB_JULIANWEEK_H_
