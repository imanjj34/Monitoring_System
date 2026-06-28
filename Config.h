#pragma once

#include <Arduino.h>

constexpr bool SMS_FEATURE_ENABLED = false;
constexpr int MAX_EVENT_SYNC_RETRIES = 3;
constexpr unsigned long DUPLICATE_SCAN_DEBOUNCE_MS = 5000UL;
constexpr unsigned long CARD_SCAN_TIMEOUT_MS = 10000UL;
constexpr int REST_BUTTON_PIN = 0; // TODO: set actual pin
constexpr char WIFI_SSID[] = "YOUR_SSID";
constexpr char WIFI_PASSWORD[] = "YOUR_PASSWORD";
constexpr char WORKER_URL[] = "https://your-worker.example.com";
