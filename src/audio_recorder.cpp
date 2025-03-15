#include "audio_recorder.h"
#include <M5Core2.h>
#include <Arduino.h>
#include "sd_handler.h"

#define BUFFER_SIZE (16000 * 2 * 10) 

static uint8_t* audioRingBuffer = nullptr;
static uint8_t* tempBuffer = nullptr;
static volatile size_t writeIndex = 0;
static volatile size_t readIndex  = 0;
static SemaphoreHandle_t ringBufferMutex;
static bool isRecording = false;
File recordingFile;

static const i2s_port_t I2S_PORT = I2S_NUM_0;

void initializeAudioRecorder() {
    audioRingBuffer = (uint8_t*) ps_malloc(BUFFER_SIZE);
    tempBuffer = (uint8_t*) ps_malloc(BUFFER_SIZE);

    ringBufferMutex = xSemaphoreCreateMutex();

    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
        .sample_rate = 16000,                      
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, 
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 4,
        .dma_buf_len = 1024,
        .use_apll = false
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = 12,   
        .ws_io_num = 0,     
        .data_out_num = -1,
        .data_in_num = 34  
    };

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pin_config);
    i2s_set_clk(I2S_PORT, 16000, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

void toggleRecording() {
    isRecording = !isRecording;
    if (isRecording) {
        SD.remove("/recording.wav");
        recordingFile = SD.open("/recording.wav", FILE_APPEND);
    } else {
        recordingFile.close();
    }
}