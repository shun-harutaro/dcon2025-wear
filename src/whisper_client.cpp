#include "whisper_client.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include "SD.h"

const char* host = "api.openai.com";
const int httpsPort = 443;
const char* api_key = "YOUR_API_KEY";

void transcribeAudio() {
    WiFiClientSecure client;
    client.setInsecure();

    if (!client.connect(host, httpsPort)) {
        Serial.println("OpenAI APIへの接続に失敗しました");
        return;
    }

    File recordingFile = SD.open("/recording.wav", FILE_READ);
    if (!recordingFile) {
        Serial.println("録音ファイルを開けませんでした");
        return;
    }

    String boundary = "----M5StackBoundary";
    String partModel = "--" + boundary + "\r\n" +
                       "Content-Disposition: form-data; name=\"model\"\r\n\r\n" +
                       "whisper-1\r\n";

    String request =
        String("POST ") + "/v1/audio/transcriptions" + " HTTP/1.1\r\n" +
        "Host: " + host + "\r\n" +
        "Authorization: Bearer " + String(api_key) + "\r\n" +
        "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n" +
        "Connection: close\r\n\r\n";

    client.print(request);
    recordingFile.close();
}