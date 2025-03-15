#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include <driver/i2s.h>

void initializeAudioRecorder();
void toggleRecording();
void task0(void* arg);
void task1(void* arg);

#endif