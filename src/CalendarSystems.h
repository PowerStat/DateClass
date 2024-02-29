/** @file
 * Calendar systems supported by DateLib.
 *
 * Copyright (C) 2022-2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */
#ifndef DATELIB_CALENDARSYSTEMS_H_
#define DATELIB_CALENDARSYSTEMS_H_


/** @namespace de::powerstat::datelib
 * DateLib namespace was a registered trademark in Germany of Dipl.-Inform. Kai Hofmann from 1998 until 2008.
 */
namespace de::powerstat::datelib
 {
 /**
  * Enumeration of calendar systems.
  *
  * @see https://en.wikipedia.org/wiki/List_of_calendars
  * @see https://de.wikipedia.org/wiki/Liste_der_Kalendersysteme
  */
 enum class CalendarSystems : unsigned short
  {
   Julian = 1,
   Gregorian = 2,

   // Islamischer Kalender
   // Moderner japanischer Kalender
   // Indischer Nationalkalender
   // Jüdischer Kalender
   // Chinesischer Kalender

   // Berberischer Kalender
   // Suriyakati-Kalender
   // Minguo-Kalender
   // Bengalischer Solarkalender
   // Iranischer Kalender
   // Malayalam-Kalender
   // Nakaiiy-Kalender
   // Orissa-Kalender
   // Porhalaan-Kalender
   // Zoroastrischer Kalender: Fasli-Kalender (auch: Parsischer Kalender)
   // Chantarakati-Kalender
   // Vikram Sambat
   // Saka-Kalender
   // Tibetischer Kalender
  };

 } // namespace

#endif // DATELIB_CALENDARSYSTEMS_H_
