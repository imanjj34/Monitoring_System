#include "StorageManager.h"
#include <Preferences.h>

namespace {
constexpr char kNamespace[] = "dormsys";
constexpr char kPendingKey[] = "pending";
}

static Preferences preferences;

void StorageManager::begin() {
  preferences.begin(kNamespace, false);
}

void StorageManager::savePendingEvent(const String& eventJson) {
  String queue = preferences.getString(kPendingKey, "");
  if (queue.isEmpty()) {
    queue = eventJson;
  } else {
    queue += "\n" + eventJson;
  }
  preferences.putString(kPendingKey, queue);
}

bool StorageManager::hasPendingEvents() {
  return !preferences.getString(kPendingKey, "").isEmpty();
}

String StorageManager::nextPendingEvent() {
  String queue = preferences.getString(kPendingKey, "");
  int separator = queue.indexOf('\n');
  if (separator < 0) {
    return queue;
  }
  return queue.substring(0, separator);
}

void StorageManager::removeSentEvent() {
  String queue = preferences.getString(kPendingKey, "");
  int separator = queue.indexOf('\n');
  if (separator < 0) {
    preferences.putString(kPendingKey, "");
    return;
  }
  preferences.putString(kPendingKey, queue.substring(separator + 1));
}
