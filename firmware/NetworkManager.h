#pragma once

#include <Arduino.h>

class NetworkManager {
public:
  static void begin(const char* ssid, const char* password);
  static bool connected();
  static bool postJson(const String& url, const String& payload);
  static bool syncPendingEvents();
};
