const int buttonPin = 12;  // knop
const int ledPin = 10;     // LED 1
const int ledPin2 = 8;     // LED 2

int buttonState = 0;
int lastButtonState = 0;
int ledState = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // reset de timer als status verandert
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // als de status stabiel is gedurende debounceDelay
    if (reading == HIGH && buttonState == LOW) {
      // knop is net ingedrukt
      if (ledState == 0) {
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPin2, LOW);
        ledState = 1;
      } else {
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPin2, HIGH);
        ledState = 0;
      }
    }
    buttonState = reading; // update knopstatus
  }

  lastButtonState = reading;
}
