/* 
 * Boards: ESP32-WROOM-DA Module
 * Library: BluetoothSerial
 * 내용 : ESP32 보드 Bluetooth Serial을 연결하는 코드 작성 & Bluetooth Serial을 이용하여 ESP32 보드의 LED 점등
*/

#include <BluetoothSerial.h>

const char *pin = "1234";

#define LED_BLUE    2
#define LED_RED     25
#define LED_YELLOW  33
#define LED_GREEN   32

String device_name = "ESP32-Bluetooth Test";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    char value = SerialBT.read();
    int ledpin;

    Serial.write(value);

    if(value == 'a') {
      ledpin = LED_RED;
    }
    else if(value == 'b') {
      ledpin = LED_YELLOW;
    }
    else if(value == 'c') {
      ledpin = LED_GREEN;
    }
    else if(value != ' ' && value != '\n' && value != 13) {
      ledpin = LED_BLUE;
    }
    else return;
    req_led(ledpin);
    Serial.print("value: ");
    Serial.println((int)value);
  }
}

void req_led(int ledpin) {
  digitalWrite(ledpin, HIGH);
  delay(500);
  digitalWrite(ledpin, LOW);
  delay(500);
  digitalWrite(ledpin, HIGH);
  delay(500);
  digitalWrite(ledpin, LOW);
  delay(500);
  Serial.println(ledpin);
}