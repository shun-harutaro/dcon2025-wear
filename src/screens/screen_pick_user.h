#ifndef SCREEN_PICK_USER_H
#define SCREEN_PICK_USER_H

#include <M5Core2.h>
#include "main.h" // AppState を参照
#include "config.h"
#include "../ui/header.h"
#include "../ui/footer.h"

void showUserPickerScreen(const AppState &state);
bool handleUserPickerTouch(const TouchPoint_t &touch, AppState &state);

#endif
