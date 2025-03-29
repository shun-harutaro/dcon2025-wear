#ifndef MY_API_H
#define MY_API_H

#include <Arduino.h>


String getJsonValue(const String& jsonText, const String& part);

String getValueInJson(const String& jsonText, const String& part, const String& field);

class MyApi {
public:
  //ゲッター
  String getuserToken() const {return userToken;};

  String getTenantUid() const {return tenantUid;};

  String getResidentUid() const {return residentUid;};

  String getFoodRecordUid() const {return foodRecordUid;};

  String getmealExtract() const {return mealExtract;};

  //セッター
  void setuserToken(const String Value) {userToken = Value;};

  void settenantUid(const String Value) {tenantUid = Value;};

  void setresidentUid(const String Value) {residentUid = Value;};

  void setfoodRecordUid(const String Value) {foodRecordUid = Value;};

  void setmealExtract(const String Value) {mealExtract = Value;};

  // コンストラクタ (API のベースURLを設定)
  MyApi(const String& baseUrl = "https://nagara-care-api.onrender.com");

  //ログイン
  String loginToApi(const String& ID, const String& password);

  // テナント一覧（権限ないから実行できない）
  String get_Tenants(const String& token);

  //ユーザー情報取得
  String get_Me(const String& token);

  //チャット一覧取得
  String get_Chats(const String& token);

  //テナントレジデント取得
  String get_tenantResident(const String& token);

  //食事記録からの情報抽出
  String mealRecordInfo();

  //テナントレジデント作成
  // MyApiクラスに新しいシグネチャを追記する
String CreateResidents(const String& token,
  const String& familyName,
  const String& givenName,
  const String& familyNameFurigana,
  const String& givenNameFurigana,
  const String& dateOfBirth,
  const String& gender,
  const String& admissionDate);


//食事記録作成
String CreateFoodRecord(const String& token,
  const String& residentUid,
  const String& recordedAt,
  const String& notes,
  const String& mealTime,
  int mainCoursePercentage,
  int sideDishPercentage,
  int soupPercentage,
  const String& beverageType,
  int beverageVolume);


//食事記録追記
String foodTranscription(const String& transcription);




private:
  String _baseUrl;

  //HtTP POST　リクエストの共通関数
  String httpPostJson(const String& endpoint, const String& jsonBody, const String& token = "");

  // HTTP GET リクエストの共通関数
  String httpGet(const String& endpoint, const String& token = "");

  String httpPatchJson(const String& endpoint, const String& jsonBody, const String& token = "");

  String userToken;

  String tenantUid;

  String residentUid;

  String foodRecordUid;

  String mealExtract;
};

#endif
