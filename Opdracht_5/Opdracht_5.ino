#include <Servo.h>

const int button1Pin = 13;
const int button2Pin = 12;
const int servoPin = 3;

Servo myServo;

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  myServo.attach(servoPin);
  myServo.write(0); // startpositie
}

void loop() {
  bool button1 = digitalRead(button1Pin) == HIGH;
  bool button2 = digitalRead(button2Pin) == HIGH;

  if (button1 && button2) {
    // Beide knoppen: 5s op, 2s wachten, 0.5s terug
    moveServo(0, 120, 5000);
    delay(2000);
    moveServo(120, 0, 500);
  } 
  else if (button1) {
    // Alleen knop 1: langzaam heen en terug (5s)
    moveServo(0, 120, 5000);
    moveServo(120, 0, 5000);
  } 
  else if (button2) {
    // Alleen knop 2: snel heen en terug (0.5s)
    moveServo(0, 120, 500);
    moveServo(120, 0, 500);
  }
}

// Algemene functie voor servo-beweging met tijd
void moveServo(int fromAngle, int toAngle, int durationMs) {
  int steps = abs(toAngle - fromAngle);
  if (steps == 0) return;

  float stepDelay = (float)durationMs / steps;

  int direction = (toAngle > fromAngle) ? 1 : -1;
  for (int angle = fromAngle; angle != toAngle + direction; angle += direction) {
    myServo.write(angle);
    delay(stepDelay);
  }
}