#ifndef SCREEN_DISPLAY_EXTRACT_H
#define SCREEN_DISPLAY_EXTRACT_H

#include <Arduino.h>
#include "screen_manager.h"

void showMealRecordFromJson(const String &jsonString, const AppState &state);

#endif // SCREEN_DISPLAY_EXTRACT_H
