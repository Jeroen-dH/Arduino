const int potPin = A5; // Potmeter on analog pin A0
const int ledPins[6] = {11, 10, 9, 6, 5, 3}; // Left to right LED pins

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int potValue = analogRead(potPin); // Read potmeter (0 - 1023)

  // Map potmeter value to number of LEDs to turn ON (0 - 6)
  int ledsOn = map(potValue, 0, 1023, 0, 6);

  for (int i = 0; i < 6; i++) {
    if (i < ledsOn) {
      digitalWrite(ledPins[i], HIGH); // Turn on LED
    } else {
      digitalWrite(ledPins[i], LOW);  // Turn off LED
    }
  }

  delay(20); // Optional: debounce/delay for stability
}
