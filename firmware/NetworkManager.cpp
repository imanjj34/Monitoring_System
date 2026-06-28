#include "NetworkManager.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "StorageManager.h"
#include "Config.h"

void NetworkManager::begin(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    delay(250);
  }
}

bool NetworkManager::connected() {
  return WiFi.status() == WL_CONNECTED;
}

bool NetworkManager::postJson(const String& url, const String& payload) {
  if (!connected()) {
    return false;
  }

  HTTPClient http;
  if (!http.begin(url)) {
    return false;
  }

  http.addHeader("Content-Type", "application/json");
  int code = http.POST(payload);
  http.end();
  return code >= 200 && code < 300;
}

bool NetworkManager::syncPendingEvents() {
  if (!connected()) {
    return false;
  }

  while (StorageManager::hasPendingEvents()) {
    String payload = StorageManager::nextPendingEvent();
    bool ok = postJson(String(WORKER_URL) + "/events", payload);
    if (!ok) {
      return false;
    }
    StorageManager::removeSentEvent();
  }

  return true;
}
