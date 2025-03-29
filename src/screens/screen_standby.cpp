#include "screen_standby.h"


String recordTypeToString(RecordType type) {
    switch (type) {
        case MEAL:       return "食事";
        case DRINK:      return "水分";
        case EXCRETION:  return "排泄";
        case BATH:       return "入浴";
        case EVERYDAY:   return "日常";
        default:         return "";
    }
}



void showStandbyScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);
    String user = state.selectedUser;
    String type = recordTypeToString(state.selectedRecordType);
    showHeaderBar("利用者:" + user + "  記録:" + type);
    M5.Lcd.setTextDatum(3);



    // テキストを中央揃えするための Datum 設定
    M5.Lcd.setTextDatum(MC_DATUM); // 中心を基準にテキストを描画

    // 1つ目の四角
    int x1 = startX;
    M5.Lcd.drawRect(x1, startY, rectWidth, rectHeight, BLACK);
    M5.Lcd.drawString("朝食", x1 + rectWidth/2, startY + rectHeight/2);

    // 2つ目の四角
    int x2 = x1 + rectWidth + gap;
    M5.Lcd.drawRect(x2, startY, rectWidth, rectHeight, BLACK);
    M5.Lcd.drawString("昼食", x2 + rectWidth/2, startY + rectHeight/2);

    // 3つ目の四角
    int x3 = x2 + rectWidth + gap;
    M5.Lcd.drawRect(x3, startY, rectWidth, rectHeight, BLACK);
    M5.Lcd.drawString("夕食", x3 + rectWidth/2, startY + rectHeight/2);


    showFooterBar(state);
}

bool handleRecBtnTouch(const TouchPoint_t &touch, AppState &state) {
    // ボタン共通のサイズと配置

    // 各ボタンの範囲
    int x1 = startX;
    int x2 = x1 + rectWidth + gap;
    int x3 = x2 + rectWidth + gap;

    // REC1 の判定
    if (touch.x > x1 && touch.x < x1 + rectWidth &&
        touch.y > startY && touch.y < startY + rectHeight) {
        state.mealTime = BREAKFAST;
        return true;
    }

    // REC2 の判定
    if (touch.x > x2 && touch.x < x2 + rectWidth &&
        touch.y > startY && touch.y < startY + rectHeight) {
        state.mealTime = LUNCH;
        return true;
    }

    // REC3 の判定
    if (touch.x > x3 && touch.x < x3 + rectWidth &&
        touch.y > startY && touch.y < startY + rectHeight) {
        state.mealTime = DINNER;
        return true;
    }

    // どのボタンも押されていない
    return false;
}