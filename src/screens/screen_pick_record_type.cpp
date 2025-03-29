#include "screen_pick_record_type.h"

void showRecordTypeScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);
    String user = state.selectedUser;
    showHeaderBar("利用者:"+ user);

    M5.Lcd.drawRect(69,  40, 86, 75, BLACK);   // 上段 左
    M5.Lcd.drawRect(165, 40, 86, 75, BLACK);  // 上段 右
    M5.Lcd.drawRect(21,  125, 86, 75, BLACK); // 下段 左
    M5.Lcd.drawRect(117, 125, 86, 75, BLACK); // 下段 中
    M5.Lcd.drawRect(213, 125, 86, 75, BLACK); // 下段 右
    M5.Lcd.setTextDatum(MC_DATUM); // Middle-Center
    M5.Lcd.drawString("食事", 112, 77);
    M5.Lcd.drawString("飲料", 208, 77);
    M5.Lcd.drawString("排泄", 64, 162);
    M5.Lcd.drawString("入浴", 160, 162);
    M5.Lcd.drawString("日常", 256, 162);

    showFooterBar(state);
}


bool handleRecordTypeTouch(const TouchPoint_t &touch, AppState &state) {
    if (touch.x > 69 && touch.x < 69+86 && touch.y > 40 && touch.y < 40+75) {
        state.selectedRecordType = MEAL;
        return true;
    } else if (touch.x > 165 && touch.x < 165+86 && touch.y > 40 && touch.y < 40+75) {
        state.selectedRecordType = DRINK;
        return true;
    }else if (touch.x > 21 && touch.x < 21+86 && touch.y > 125 && touch.y < 125+75) {
        state.selectedRecordType = EXCRETION;
        return true;
    }else if (touch.x > 117 && touch.x < 117+86 && touch.y > 125 && touch.y < 125+75) {
        state.selectedRecordType = BATH;
        return true;
    }else if (touch.x > 213 && touch.x < 213+86 && touch.y > 125 && touch.y < 125+75) {
        state.selectedRecordType = EVERYDAY;

        return true;
    }
    return false;
}