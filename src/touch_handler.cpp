#define FOOTER_HOME_MIN_X 109
#define FOOTER_HOME_MAX_X 218

#include <M5Core2.h>
#include "touch_handler.h"
#include "screen_manager.h"
#include "screens/screen_transcription.h"

extern AppState appState;

void handleTouchEvents() {
  TouchPoint_t touch;
  
  if (!M5.Touch.ispressed()) {
    return;
  }

  touch = M5.Touch.getPressPoint();

  // メインコンテンツのタッチ
  if (touch.y < 200) {
    switch (appState.currentScreen) {
      case USER_PICKER:
        if (handleUserPickerTouch(touch, appState)) {
          changeScreen(RECORD_TYPE_PICKER);
        }
        break;
      case STANDBY:
        if (handleRecBtnTouch(touch, appState)) {
          changeScreen(TRANSCRIPTION);
        }
        break;
      case RECORD_TYPE_PICKER:
        if(handleRecordTypeTouch(touch,appState)){
          changeScreen(STANDBY);
        }
    }
  } 
  // フッター部分のタッチ
  else {
    handleFooterTouch(touch);
  }
}

void handleFooterTouch(TouchPoint_t touch) {
  if(appState.currentScreen == TRANSCRIPTION){
    Serial.println("currentScreen is TRANSCRIPTION");
    M5.Axp.SetLDOEnable(3, true);
    delay(75);
    M5.Axp.SetLDOEnable(3, false);
    if (touch.x >= FOOTER_HOME_MIN_X && touch.x <= FOOTER_HOME_MAX_X) {
      changeScreen(USER_PICKER);
    } else if (touch.x < FOOTER_HOME_MIN_X) {
      toggleRecording();
    }
  }
  else{
    M5.Axp.SetLDOEnable(3, true);
    delay(75);
    M5.Axp.SetLDOEnable(3, false);
    if (touch.x >= FOOTER_HOME_MIN_X && touch.x <= FOOTER_HOME_MAX_X) {
      changeScreen(USER_PICKER);
    } else if (touch.x < FOOTER_HOME_MIN_X) {
      popScreen();
    } else if (touch.x >= FOOTER_HOME_MAX_X){
      changeScreen(MEAL_EXTRACT);
    }
  }
}