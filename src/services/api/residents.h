#ifndef RESIDENTS_H
#define RESIDENTS_H

#include <Arduino.h>
#include "api.h"

String getTenantResident(MyApi& api,const String& token);

String createResidents(
    MyApi& api,
    const String& token,
    const String& familyName,
    const String& givenName,
    const String& familyNameFurigana,
    const String& givenNameFurigana,
    const String& dateOfBirth,
    const String& gender,
    const String& admissionDate);

struct Residents {
    String residentUid;
    String familyName;
    String givenName;
    
    // 引数ありコンストラクタ
    Residents(const String& uid, const String& fam, const String& given)
        : residentUid(uid), familyName(fam), givenName(given) {}
    
    // デフォルトコンストラクタも定義
    Residents() : residentUid(""), familyName(""), givenName("") {}
    };
    
#endif