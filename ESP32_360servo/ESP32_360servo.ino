/* 
 * Boards: ESP32-WROOM-DA Module
 * Library: ESP32Servo
 * 내용 : ESP32 보드를 이용하여 360서보모터 4개를 별도로 제어하는 코드 작성
*/

#include <ESP32Servo.h>

#define SERVO_1     13
#define SERVO_2     12
#define SERVO_3     14
#define SERVO_4     27

#define PEN         15
#define SENSOR      4

Servo servo1, servo2, servo3, servo4;

void setup() {
  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);
  servo3.attach(SERVO_3);
  servo4.attach(SERVO_4);
}

void loop() {
  servo1.write(180);
  delay(1000);
  servo1.write(90);
  servo2.write(0);
  delay(1000);
  servo2.write(90);
  servo3.write(180);
  delay(1000);
  servo3.write(90);
  servo4.write(0);
  delay(1000);
  servo4.write(90);
}
