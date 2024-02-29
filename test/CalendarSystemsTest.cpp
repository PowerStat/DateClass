/*
 * Copyright (C) 2024 Dipl.-Inform. Kai Hofmann. All rights reserved!
 */


#include "CalendarSystems.h"
#include <gtest/gtest.h>


using namespace de::powerstat::datelib;


namespace
 {
  TEST(CalendarSystemsTest, enum1)
   {
    ASSERT_EQ((int)CalendarSystems::Julian, 1);
   }

 }
