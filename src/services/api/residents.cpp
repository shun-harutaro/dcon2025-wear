#include "residents.h"
#include <ArduinoJson.h>
#include "api.h"
#include "general.h"

//テナントユーザ一覧を取得
String getTenantResident(MyApi& api,const String& token){
    return httpGet(api, "/tenants/" + api.getTenantUid() + "/residents", token);
  }
  
  //レジデント作成
  // MyApi.cpp
  
String createResidents(
    MyApi& api,
    const String& token,
    const String& familyName,
    const String& givenName,
    const String& familyNameFurigana,
    const String& givenNameFurigana,
    const String& dateOfBirth,
    const String& gender,
    const String& admissionDate) 
  {
  // 1) 送信するJSONボディを組み立てる
  String jsonBody = "{";
  jsonBody += "\"familyName\":\"" + familyName + "\",";
  jsonBody += "\"givenName\":\"" + givenName + "\",";
  jsonBody += "\"familyNameFurigana\":\"" + familyNameFurigana + "\",";
  jsonBody += "\"givenNameFurigana\":\"" + givenNameFurigana + "\",";
  jsonBody += "\"dateOfBirth\":\"" + dateOfBirth + "\",";
  jsonBody += "\"gender\":\"" + gender + "\",";
  jsonBody += "\"admissionDate\":\"" + admissionDate + "\"";
  jsonBody += "}";
  
  // 2) POSTリクエストを送る
  return httpPostJson(api, "/tenants/" + api.getTenantUid() + "/residents", jsonBody, token);
  }

  