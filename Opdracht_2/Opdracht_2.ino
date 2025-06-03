const int ledCount = 8;
const int ledPins[ledCount] = {13, 12, 11, 10, 9, 8, 7, 6}; // Pins for LEDs

void setup() {
  // Set all LED pins as OUTPUT
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Left to right
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
    delay(100);
    digitalWrite(ledPins[i], HIGH);
  }

  // Right to left
  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], LOW);
    delay(100);
    digitalWrite(ledPins[i], HIGH);
  }
}