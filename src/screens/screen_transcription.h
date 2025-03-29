#ifndef SCREEN_TRANSCRIPTION_H
#define SCREEN_TRANSCRIPTION_H

#include <M5Core2.h>
#include "main.h" // AppState を参照
#include "config.h"
#include "../ui/header.h"
#include "../ui/footer.h"
//#include "../audio_recorder.h"

void showTranscriptionScreen(const AppState &state);
void toggleRecording();
void rebootTranscriptionScreen(const AppState &state);
String mealTimeToString(MealTime mt);
#endif
