#include "GSMManager.h"

static HardwareSerial* _simSerial = nullptr;

void GSMManager::begin(HardwareSerial& simSerial, int baudRate) {
  _simSerial = &simSerial;
  _simSerial->begin(baudRate);
}

bool GSMManager::sendSMS(const char* number, const char* message) {
  if (!_simSerial) {
    return false;
  }
  // TODO: implement SIM800 SMS send sequence
  return true;
}

bool GSMManager::ready() {
  return _simSerial != nullptr;
}
