#include "header.h"

void showHeaderBar(const String &title) {
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawLine(10, 30, 310, 30, WHITE);
    M5.Lcd.setTextDatum(4);
    M5.Lcd.drawString(title, 160, 15);
}