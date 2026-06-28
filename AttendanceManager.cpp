#include "AttendanceManager.h"

void AttendanceManager::begin() {
  insideDorm_ = false;
  restActive_ = false;
  restRequested_ = false;
  firstEntryToday_ = true;
  lastCardId_ = "";
  lastCardTime_ = 0;
  eventSequence_ = 1;
}

void AttendanceManager::setRestRequested(bool requested) {
  restRequested_ = requested;
}

bool AttendanceManager::processCard(const String& cardId) {
  if (cardId.isEmpty()) {
    return false;
  }

  unsigned long now = millis();
  if (!lastCardId_.isEmpty() && lastCardId_ == cardId && (now - lastCardTime_) < DUPLICATE_SCAN_DEBOUNCE_MS) {
    return false;
  }

  lastCardId_ = cardId;
  lastCardTime_ = now;

  String eventType;
  if (restRequested_ && !restActive_) {
    eventType = "Rest Start";
    restActive_ = true;
    restRequested_ = false;
  } else if (restActive_) {
    eventType = "Rest End";
    restActive_ = false;
  } else if (insideDorm_) {
    eventType = "Dorm Out";
    insideDorm_ = false;
  } else {
    eventType = "Dorm In";
    insideDorm_ = true;
    firstEntryToday_ = false;
  }

  return writeEvent(eventType, cardId);
}

void AttendanceManager::syncPendingEvents() {
  if (StorageManager::hasPendingEvents()) {
    NetworkManager::syncPendingEvents();
  }
}

bool AttendanceManager::isInsideDorm() const {
  return insideDorm_;
}

bool AttendanceManager::isResting() const {
  return restActive_;
}

bool AttendanceManager::writeEvent(const String& eventType, const String& cardId) {
  String payload = String("{\"studentId\":\"") + cardId +
                   String("\",\"type\":\"") + eventType +
                   String("\",\"timestamp\":") + String(millis()) +
                   String(",\"deviceId\":\"ESP32\",\"sequence\":") + String(eventSequence_++) + "}";

  bool synced = false;
  if (NetworkManager::connected()) {
    synced = sendEventToCloud(payload);
  }

  if (!synced) {
    StorageManager::savePendingEvent(payload);
  }

  return true;
}

bool AttendanceManager::sendEventToCloud(const String& payload) {
  bool ok = false;
  for (int attempt = 0; attempt < MAX_EVENT_SYNC_RETRIES; ++attempt) {
    if (NetworkManager::postJson(String(WORKER_URL) + "/events", payload)) {
      ok = true;
      break;
    }
    delay(1000 * (attempt + 1));
  }
  return ok;
}
