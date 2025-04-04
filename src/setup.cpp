#include <M5Core2.h>
#include "setup.h"
#include "config.h"
#include "screen_manager.h"
#include "system/sd_handler.h"
#include "system/wifi_manager.h"
//#include "audio/audio_buffer.h"
#include "services/api/api.h"
#include "tools/json.h"
#include <WiFiClientSecure.h>
#include "services/api/residents.h"
#include <vector>

AppState appState;

MyApi api;  // `MyApi` クラスのインスタンスを作成

// **HTTP リクエストの送信**
WiFiClientSecure client;

void initializeSystem() {
  //M5スタックイニシャライズ
  M5.begin();
  M5.Axp.SetLDOEnable(2, true);
  M5.Lcd.setTextFont(4);
  M5.Lcd.setFreeFont(&unicode_24px);

  appState.currentScreen = USER_PICKER;
  appState.screenHistory.push(appState.currentScreen);
  showUserPickerScreen(appState);

  //SDカード初期化
  if (!initializeSD()) {
    Serial.println("SD Card init failed!");
    return;
  }
  //Wi-Fi接続
  connectToWiFi();
  client.setInsecure();  // SSL 証明書の検証を無効化
  //ログイン
  String loginResponse = api.loginToApi("hardware-test", "password");
  Serial.println("Login Response:");
  Serial.println(loginResponse);
  String token = getJsonValue(loginResponse,"token");
  api.setuserToken(token);
  //ユーザ情報獲得
  String userinfo = api.getMe(token);
  Serial.println("userinfo:");
  Serial.println(userinfo);
  String tenantUid = getJsonValue(userinfo,"tenantUid");
  api.settenantUid(tenantUid);
  Serial.println(tenantUid);
  //テナントレジデント一覧取得
  String tenantResident = getTenantResident(api,token);
  Serial.println("tenantUser:");
  Serial.println(tenantResident);
  //抽出する値の設定
  std::vector<String> fields = { "uid", "familyName", "givenName"};
  std::vector<Residents> residents = getValueAllInJson(tenantResident,"items",fields);
  // シリアルで中身を表示する例
  Serial.println("=== Residents List ===");

  for (size_t i = 0; i < residents.size(); i++) {
    Serial.print("[" + String(i) + "] uid: ");
    Serial.println(residents[i].residentUid);

    Serial.print("        familyName: ");
    Serial.println(residents[i].familyName);

    Serial.print("        givenName : ");
    Serial.println(residents[i].givenName);

    Serial.println("----------------------");
  }
  //api.setresidentUid(residentUid);
  //Serial.println(residentUid);
  //テナントレジデント作成
  /*
  String result = createResidents(
    api,
    token, 
    "髙木",          // familyName
    "透",          // givenName
    "タカギ",        // familyNameFurigana
    "トオル",        // givenNameFurigana
    "2003-11-19",    // dateOfBirth
    "MALE",          // gender
    "2025-04-02"     // admissionDate
  );

  // 結果確認
  Serial.println("CreateResidents response:");
  Serial.println(result);
  */


}