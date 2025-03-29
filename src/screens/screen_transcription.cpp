#include "screen_transcription.h"
#include <M5Core2.h>
#include "../ui/header.h"
#include "../ui/footer.h"
#include "task_manager.h"
#include "../audio/audio_recorder.h"

extern AudioRecorder recorder;

static String transcriptionText = "";
static bool isRecording = recorder.isRecording();

String mealTimeToString(MealTime mt) {
    switch (mt) {
        case BREAKFAST: return "朝食";
        case LUNCH:     return "昼食";
        case DINNER:    return "夕食";
        default:        return "";
    }
}



void updateTranscriptionText(const String& newText) {
    transcriptionText = newText;
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print(transcriptionText);
}

void toggleRecording() {
    if (!isRecording) {
        isRecording = true;
        startBackgroundTasks(); // task_managerでタスクを開始
    } else {
        isRecording = false;
        stopBackgroundTasks(); // task_managerでタスクを停止
    }
}

void showTranscriptionScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setCursor(10, 10);
    Serial.println(state.mealTime);
    showHeaderBar(mealTimeToString(state.mealTime) + "レコーディング中");
    showFooterBarRecording(state);


    toggleRecording();
}


void rebootTranscriptionScreen(const AppState &state) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.setTextColor(BLACK);
    showHeaderBar(mealTimeToString(state.mealTime) + "レコーディング中");

    showFooterBarRecording(state);
}
