#include <ArduinoJson.h>
#include "json.h"
#include "../services/api/residents.h"
#include <vector>

//JSONパース関数(HTTPを考慮しない)
//JSONから任意のパーツを取り出す
String getJsonValue(const String& jsonText, const String& part) {
    // 1) JSON解析用のドキュメントを用意（バッファサイズ 1024）
    DynamicJsonDocument doc(1024);
  
    // 2) JSON文字列をdocにパース
    DeserializationError error = deserializeJson(doc, jsonText);
    if (error) {
      // パース失敗時はログを出して空文字を返す
      Serial.println("[Error] Failed to parse JSON");
      return "";
    }
  
    // 3) doc[part] から値を取得
    //    ここで .as<String>() を使って Arduino String に変換
    if (doc[part].isNull()) {
      // 指定したキーがJSONに含まれていない場合も空文字を返す
      return "";
    }
  
    // キーが存在すれば文字列として取得
    String value = doc[part].as<String>();
    return value;
  }
  
  
  String getValueInJson(const String& jsonText, const String& part, const String& field) {
    // 1) JSONをパースする
    DynamicJsonDocument doc(2048); // 必要に応じて容量調整
    DeserializationError error = deserializeJson(doc, jsonText);
    if (error) {
      Serial.print("[Error] Failed to parse JSON: ");
      Serial.println(error.c_str());
      return "";
    }
  
    // 2) "items" が配列か確認
    if (!doc[part].is<JsonArray>()) {
      Serial.println("[Error] 'items' is not an array or not found");
      return "";
    }
    JsonArray itemsArray = doc[part].as<JsonArray>();
    if (itemsArray.size() == 0) {
      Serial.println("[Error] 'items' array is empty");
      return "";
    }
  
    // 3) 配列の先頭要素(0番目)から、指定したキーの値を取得
    //    もしキーが存在しなければ空文字を返す
    String result = itemsArray[0][field] | "";
  
    return result;
  }




// すべての要素から field に対応する値を取得する関数
// 第3引数の "fields" は、{ "uid", "familyName", "givenName" } のような配列・リストを想定
std::vector<Residents> getValueAllInJson(
    const String& jsonStr,
    const String& arrayKey,
    const std::vector<String>& fields  // 例：["uid", "familyName", "givenName"]
) {
    // 戻り値用のコンテナ
    std::vector<Residents> residentsList;

    // ArduinoJsonでパース用のDynamicJsonDocumentを準備 (容量は適宜調整)
    DynamicJsonDocument doc(4096);
    DeserializationError err = deserializeJson(doc, jsonStr);
    if (err) {
        // JSONパース失敗時は空のリストを返すなど
        return residentsList;
    }

    // 配列キー(arrayKey)があるかチェック
    JsonArray arr = doc[arrayKey].as<JsonArray>();
    if (arr.isNull()) {
        // 指定した配列キーが見つからない or 配列でない場合
        return residentsList;
    }

    // 配列を走査
    for (JsonObject obj : arr) {
        // fields[0], fields[1], fields[2] をそれぞれ取り出す想定
        // 例: fields[0] = "uid", fields[1] = "familyName", fields[2] = "givenName"
        String uid   = obj[fields[0]] | "";
        String fname = obj[fields[1]] | "";
        String gname = obj[fields[2]] | "";

        // Residents 構造体に入れてプッシュ
        Residents r(uid, fname, gname);
        residentsList.push_back(r);
    }

    return residentsList;
}
