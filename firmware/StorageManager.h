#pragma once

#include <Arduino.h>

class StorageManager {
public:
  static void begin();
  static void savePendingEvent(const String& eventJson);
  static bool hasPendingEvents();
  static String nextPendingEvent();
  static void removeSentEvent();
};
