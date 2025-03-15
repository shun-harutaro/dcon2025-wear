#include "wifi_manager.h"
#include <WiFi.h>
#include "config.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void connectToWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.println("WiFi Connected!");
}