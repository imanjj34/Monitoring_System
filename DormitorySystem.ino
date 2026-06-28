#include "Config.h"
#include "AttendanceManager.h"
#include "RFID.h"
#include "firmware/NetworkManager.h"
#include "firmware/StorageManager.h"

AttendanceManager attendance;
RFID rfid;

void setup() {
  pinMode(REST_BUTTON_PIN, INPUT_PULLUP);
  StorageManager::begin();
  NetworkManager::begin(WIFI_SSID, WIFI_PASSWORD);
  rfid.begin();
  attendance.begin();
}

void loop() {
  if (digitalRead(REST_BUTTON_PIN) == LOW) {
    attendance.setRestRequested(true);
    delay(200);
  }

  if (rfid.available()) {
    String cardId = rfid.readCard();
    if (!cardId.isEmpty()) {
      attendance.processCard(cardId);
    }
  }

  if (NetworkManager::connected()) {
    attendance.syncPendingEvents();
  }

  delay(50);
}
