#include "RFID.h"

void RFID::begin() {
  Serial.begin(115200);
}

bool RFID::available() {
  return Serial.available() > 0;
}

String RFID::readCard() {
  String cardId;
  while (Serial.available() > 0) {
    char c = static_cast<char>(Serial.read());
    if (c == '\n' || c == '\r') {
      if (!cardId.isEmpty()) {
        break;
      }
      continue;
    }
    cardId += c;
  }
  return cardId;
}
