#ifndef MY_API_H
#define MY_API_H

#include <Arduino.h>


class MyApi {
public:
  //ゲッター
  String getuserToken() const {return userToken;};

  String getTenantUid() const {return tenantUid;};

  String getResidentUid() const {return residentUid;};

  String getFoodRecordUid() const {return foodRecordUid;};

  String getmealExtract() const {return mealExtract;};

  String getBaseUrl() const {return _baseUrl;};

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
  String getTenants(const String& token);

  //ユーザー情報取得
  String getMe(const String& token);

  //チャット一覧取得
  String getChats(const String& token);

  //テナントレジデント取得
  String getTenantResident(const String& token);

  //テナントレジデント作成
  // MyApiクラスに新しいシグネチャを追記する
  String createResidents(const String& token,
    const String& familyName,
    const String& givenName,
    const String& familyNameFurigana,
    const String& givenNameFurigana,
    const String& dateOfBirth,
    const String& gender,
    const String& admissionDate);





private:
  String _baseUrl;

  String userToken;

  String tenantUid;

  String residentUid;

  String foodRecordUid;

  String mealExtract;
};

#endif
