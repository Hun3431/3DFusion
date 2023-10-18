/* 
 * Boards: ESP32-WROOM-DA Module
 * Library: DHT, ArduinoJson
 * 내용 : ESP32 보드를 이용하여 온습도 확인
*/

#include <DHT.h>
#include <ArduinoJson.h>

#define   DHT_PIN   33
#define   DHT_TYPE  DHT11

// 온습도센서 객체 생성
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  // 온습도센서 객체 사용
  dht.begin();
}

void loop() {
  String dhtValue = readDHT();

  // JSON 온습도 데이터 출력
  Serial.println(dhtValue);

  delay(1000);
}

String readDHT() {
  String response = "";

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // 온습도 값을 읽지 못했을 경우 "nan"을 반환
  if(isnan(h) || isnan(h)) {
    return "nan";
  }

  // JSON 객체 선언
  DynamicJsonDocument doc(200);
  
  doc["humidity"] = String(int(h));
  doc["temperature"] = String(t);
  
  serializeJson(doc, response);

  return response;
}