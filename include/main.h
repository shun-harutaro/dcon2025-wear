#ifndef MAIN_H
#define MAIN_H

#define LCDWIDE 320
#define LCDHEIGHT 240

#include <Arduino.h>

// 画面を識別する列挙型
enum Screen { 
    USER_PICKER, 
    RECEIVER_PICKER, 
    STANDBY,
    RECORDING,
    FINAL_SCREEN,
    TRANSCRIPTION,
};

// アプリケーション全体で使用する状態管理構造体
struct AppState {
    String selectedUser;     // 選択されたユーザー名
    String selectedReceiver; // 選択された相手の名前
    Screen currentScreen;
};

#endif
