/* 
 * Boards: ESP32-WROOM-DA Module
 * Library: Adafruit_NeoPixel
 * 내용 : ESP32 보드를 이용하여 NeoPixel LED Strip 점등
*/

#include <Adafruit_NeoPixel.h>

#define   PIN_NEO_PIXEL   5 
#define   NUM_PIXELS      2 // 연결 된 LED 갯수 

// NeoPixel 선언
Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  NeoPixel.begin(); // 초기화
}

void loop() {
  NeoPixel.clear(); // LED 초기화

  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(100, 100, 100));  // 지정한 핀에 RGB값 지정
    NeoPixel.show(); // LED 업데이트
  }
  
  delay(100);
}