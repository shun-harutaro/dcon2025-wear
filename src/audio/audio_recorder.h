#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include <Arduino.h>
#include <driver/i2s.h>
#include "../system/sd_handler.h"

#define BUFFER_SIZE (16000 * 2 * 20)

class AudioRecorder {
public:
    AudioRecorder();
    ~AudioRecorder();

    void startRecording();
    void stopRecording();
    bool isRecording() const{return recording;};
    void initialize();
    static void recordTask(void* param);
    SemaphoreHandle_t getRingBufferMutex() const {return ringBufferMutex;}
    volatile size_t getwriteIndex() const {return writeIndex;};
    volatile size_t getreadIndex() const {return readIndex;};
    void setReadIndex(size_t value) { readIndex = value; };
    uint8_t* getaudioRingBuffer() const {return audioRingBuffer;};
    uint8_t* gettempBuffer() const {return tempBuffer;};
    void settempBuffer(uint8_t* buffer) { tempBuffer = buffer; };
    size_t getCursol() const {return cursol;};
    void setCursol(size_t value) {cursol = value;};
    size_t getCursolX() const {return cursolx;};
    void setCursolx(size_t value) {cursolx = value;};
    


    

private:
    uint8_t* audioRingBuffer;
    uint8_t* tempBuffer;
    volatile size_t writeIndex;
    volatile size_t readIndex;
    SemaphoreHandle_t ringBufferMutex;
    bool recording;
    File recordingFile;
    TaskHandle_t recordingTaskHandle;
    static const i2s_port_t I2S_PORT = I2S_NUM_0;
    size_t cursol = 40;
    size_t cursolx = 10;
};

#endif