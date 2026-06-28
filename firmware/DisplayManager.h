#pragma once

class DisplayManager {
public:
  static void begin();
  static void showStatus(const char* line1, const char* line2 = nullptr);
};
