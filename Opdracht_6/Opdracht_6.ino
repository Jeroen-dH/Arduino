#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int btnStartLap = 2;  // Start / Lap-knop
const int btnPause    = 3;  // Pauze-knop

// Stopwatch-state
unsigned long startTime   = 0;
unsigned long pausedTime  = 0;
unsigned long lapTime     = 0;
bool running     = false;
bool lapRecorded = false;

// Debounce
const unsigned long DEBOUNCE_MS = 50;
unsigned long lastDb1 = 0, lastDb2 = 0;
bool lastSt1 = LOW, lastSt2 = LOW;

// Voor korte vs lange druk op knop1
unsigned long pressStart = 0;
bool pressing1 = false;

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();

  pinMode(btnStartLap, INPUT);  
  pinMode(btnPause,    INPUT);

  // Init display
  lcd.setCursor(0,0); lcd.print("00:00.00");
  lcd.setCursor(0,1); lcd.print("Lap: --:--.--");
}

void loop() {
  // Lees raw en debounce
  bool raw1 = digitalRead(btnStartLap);
  bool raw2 = digitalRead(btnPause);
  bool b1 = debounce(1, raw1);
  bool b2 = debounce(2, raw2);

  // === Reset (beide knoppen tegelijk) ===
  if (b1 && b2) {
    running     = false;
    lapRecorded = false;
    startTime   = millis();
    pausedTime  = 0;
    lapTime     = 0;
    lcd.setCursor(0,0); lcd.print("00:00.00");
    lcd.setCursor(0,1); lcd.print("Lap: --:--.--");
    // wacht tot beide knoppen los zijn
    while (digitalRead(btnStartLap) || digitalRead(btnPause)) {
      delay(10);
    }
    delay(200);
    return;
  }

  // === Pauze / Resume toggle (knop2) ===
  if (b2 && !b1) {
    if (running) {
      // pauze
      pausedTime = millis() - startTime;
      running    = false;
    } else {
      // resume
      startTime = millis() - pausedTime;
      running   = true;
    }
    delay(200);
  }

  // === Start vs Lap (knop1 kort vs lang) ===
  if (b1 && !pressing1) {
    pressing1   = true;
    pressStart  = millis();
  }
  else if (!b1 && pressing1) {
    unsigned long held = millis() - pressStart;
    if (!running && held < 2000) {
      // kort: Start
      startTime = millis();
      running   = true;
    }
    else if (running && held >= 2000) {
      // lang: Lap
      lapTime     = millis() - startTime;
      lapRecorded = true;
    }
    pressing1 = false;
    delay(200);
  }

  // === Update display ===
  unsigned long elapsed = running
    ? (millis() - startTime)
    : pausedTime;
  display(elapsed, lapRecorded ? lapTime : 0);
}

// Debounce‐helper
bool debounce(int id, bool raw) {
  unsigned long now = millis();
  unsigned long &lastDb = (id==1 ? lastDb1 : lastDb2);
  bool         &lastSt = (id==1 ? lastSt1 : lastSt2);
  if (raw != lastSt && now - lastDb >= DEBOUNCE_MS) {
    lastDb = now;
    lastSt = raw;
  }
  return lastSt;
}

// Format MM:SS.MS
String formatTime(unsigned long t) {
  unsigned int cs  = (t/10) % 100;
  unsigned int sec = (t/1000) % 60;
  unsigned int min =  t/60000;
  char buf[9];
  sprintf(buf, "%02u:%02u.%02u", min, sec, cs);
  return String(buf);
}

// Toon tijden op LCD
void display(unsigned long elapsed, unsigned long lap) {
  lcd.setCursor(0,0);
  lcd.print(formatTime(elapsed));

  lcd.setCursor(0,1);
  if (lapRecorded) {
    lcd.print("Lap: ");
    lcd.print(formatTime(lap));
  } else {
    lcd.print("Lap: --:--.--");
  }
}
