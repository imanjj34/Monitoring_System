#pragma once

#include <Arduino.h>
#include "Config.h"
#include "firmware/NetworkManager.h"
#include "firmware/StorageManager.h"

class AttendanceManager {
public:
  void begin();
  void setRestRequested(bool requested);
  bool processCard(const String& cardId);
  void syncPendingEvents();
  bool isInsideDorm() const;
  bool isResting() const;

private:
  bool insideDorm_;
  bool restActive_;
  bool restRequested_;
  bool firstEntryToday_;
  String lastCardId_;
  unsigned long lastCardTime_;
  int eventSequence_;

  bool writeEvent(const String& eventType, const String& cardId);
  bool sendEventToCloud(const String& payload);
};
