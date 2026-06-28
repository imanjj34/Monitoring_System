#pragma once

#include <Arduino.h>

class RFID {
public:
  void begin();
  bool available();
  String readCard();
};
