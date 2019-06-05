#include "L298N.h"
#include <IRremote.h>

// pin definition
#define EN1 2
#define IN1 3
#define IN2 4
#define EN2 5
#define IN3 6
#define IN4 7
// create a motor instance
L298N motor1(EN1, IN1, IN2);
L298N motor2(EN2, IN3, IN4);
// initial speed
byte theSpeed = 255;
int PIN_RECV = 8;
IRrecv irrecv(PIN_RECV);
decode_results results;

void setup() {
  // set the initial speed
  motor1.setSpeed(theSpeed);
  motor2.setSpeed(theSpeed);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {

  if (irrecv.decode(&results)) {
    switch (results.value) {
    case 16718055:
      Serial.println("2");
      motor1.forward();
      motor2.forward();
      break;
    case 16716015:
      Serial.println("4");
      motor1.forward();
      motor2.backward();
      break;
    case 16730805:
      Serial.println("8");
      motor1.backward();
      motor2.backward();
      break;
    case 16734885:
      Serial.println("6");
      motor2.forward();
      motor1.backward();
      break;
    case 16726215:
      Serial.println("5");
      motor1.stop();
      motor2.stop();
      break;
    case 16754775:
      Serial.println("+");
      theSpeed++;
      break;
    case 16769055:
      Serial.println("-");
      theSpeed--;
      break;
    }
    motor1.setSpeed(theSpeed);
    motor2.setSpeed(theSpeed);
    Serial.println(theSpeed);
    Serial.println(results.value);
    irrecv.resume();
  }
}
