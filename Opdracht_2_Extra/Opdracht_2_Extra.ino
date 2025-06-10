const int ledCount = 6;
const int ledPins[ledCount] = {3, 5, 6, 9, 10, 11}; // PWM-capable pins

int brightness[ledCount] = {0};    // Brightness of each LED
int maxBrightness = 255;
float fadeFactor = 0.7;           // Multiplier to smoothly fade out (0.90 = slower fade)
int delayBetween = 90;             // Delay between updates

void setup() {
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Wave from left to right
  for (int i = 0; i < ledCount; i++) {
    brightness[i] = maxBrightness;

    updateLEDs();
    delay(delayBetween);
    fadeAll();
  }

  // Wave from right to left
  for (int i = ledCount - 1; i >= 0; i--) {
    brightness[i] = maxBrightness;

    updateLEDs();
    delay(delayBetween);
    fadeAll();
  }
}

// Updates LED brightness with inverted logic
void updateLEDs() {
  for (int i = 0; i < ledCount; i++) {
    analogWrite(ledPins[i], 255 - brightness[i]); // Inverted output
  }
}

// Smoothly fades all LEDs
void fadeAll() {
  for (int i = 0; i < ledCount; i++) {
    brightness[i] = (int)(brightness[i] * fadeFactor);
    if (brightness[i] < 5) brightness[i] = 0; // snap off to avoid long dim tail
  }
}
