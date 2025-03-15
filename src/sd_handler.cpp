#include "sd_handler.h"
#include <Arduino.h>

bool initializeSD() {
    return SD.begin();
}

void readFileFromSD(const char* filename) {
    File file = SD.open(filename, FILE_READ);
    if (!file) {
        Serial.printf("Failed to open %s\n", filename);
        return;
    }

    Serial.printf("%s File Size: %d bytes\n", filename, file.size());

    Serial.println("First 64 bytes of file (hex):");
    for (int i = 0; i < 64; i++) {
        if (file.available()) {
            Serial.printf("%02X ", file.read());
        } else {
            break;
        }
    }
    Serial.println("\nEnd of File.");
    file.close();
}