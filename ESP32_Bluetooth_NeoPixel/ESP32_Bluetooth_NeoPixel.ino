/* 
 * Boards: ESP32-WROOM-DA Module
 * Library: BluetoothSerial, Adafruit_NeoPixel
 * 내용 : ESP32 보드 Bluetooth Serial을 연결하는 코드 작성 & 연결 대기상태 점멸등 점등, 연결 시 파란 LED 점등
*/

#include <BluetoothSerial.h>
#include <Adafruit_NeoPixel.h>

#define   PIN_NEO_PIXEL   5 
#define   NUM_PIXELS      2 // 연결 된 LED 갯수 

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

// NeoPixel 객체 생성
Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

// BluetoothSerial 객체 생성
BluetoothSerial SerialBT;
bool ledState = false;

const char *pin = "1234";
String device_name = "ESP32_Bluetooth_NeoPixel_Control";

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif

  NeoPixel.begin();
}

void loop() {
  // Bluetooth Serial 연결 확인
  if(!SerialBT.connected()) {
    // Bluetooth Serial이 연결되지 않았을 경우 점멸등 
    blinkLED();
    return;
  }
  else {
    // Bluetooth Serial이 연결되었을 경우 파란 LED 점등
    NeoPixel.clear();
    for(int i = 0; i < NUM_PIXELS; i ++) {
      NeoPixel.setPixelColor(i, NeoPixel.Color(0, 0, 255));
      NeoPixel.show();
    }
  }


  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    char value = SerialBT.read();
    Serial.print(value);
  }
}

void blinkLED() {
  ledState = !ledState;

  NeoPixel.clear();
  
  if(ledState) {
    for(int i = 0; i < NUM_PIXELS; i ++) {
      NeoPixel.setPixelColor(i, NeoPixel.Color(255, 150, 150));
      NeoPixel.show();
    }
  }
  else {
    for(int i = 0; i < NUM_PIXELS; i ++) {
      NeoPixel.setPixelColor(i, NeoPixel.Color(0, 0, 0));
      NeoPixel.show();
    }
  }

  delay(500);
}