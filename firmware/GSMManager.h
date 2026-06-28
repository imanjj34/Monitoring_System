#pragma once

#include <HardwareSerial.h>

class GSMManager {
public:
  static void begin(HardwareSerial& simSerial, int baudRate);
  static bool sendSMS(const char* number, const char* message);
  static bool ready();
};
