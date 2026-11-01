#include <SPI.h>
#include <SD.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeSans9pt7b.h>

const int BUTTON_PREV_PIN = 3;
const int BUTTON_NEXT_PIN = 4;
const int BUTTON_SELECT_PIN = 5;
const int SD_CS_PIN = 2;

GxEPD2_BW<GxEPD2_290_T9, GxEPD2_290_T9::HEIGHT> display(GxEPD2_290_T9(7, 6, 1, 0));

File textFile;
String currentFilename = "/book.txt";
unsigned long filePosition = 0;
bool needsRefresh = true;

struct ButtonState {
  int pin;
  bool stableState;
  bool lastRawState;
  uint32_t lastChangedAt;
};

ButtonState btnPrev = {BUTTON_PREV_PIN, HIGH, HIGH, 0};
ButtonState btnNext = {BUTTON_NEXT_PIN, HIGH, HIGH, 0};
ButtonState btnSelect = {BUTTON_SELECT_PIN, HIGH, HIGH, 0};

void setUpButton(ButtonState &btn) {
  pinMode(btn.pin, INPUT_PULLUP);
  btn.stableState = digitalRead(btn.pin);
  btn.lastRawState = btn.stableState;
  btn.lastChangedAt = millis();
}

bool wasPressed(ButtonState &btn) {
  bool rawState = digitalRead(btn.pin);
  uint32_t now = millis();
  if (rawState != btn.lastRawState) {
    btn.lastRawState = rawState;
    btn.lastChangedAt = now;
  }
  if (rawState != btn.stableState && (now - btn.lastChangedAt >= 30)) {
    btn.stableState = rawState;
    if (btn.stableState == LOW) {
      return true;
    }
  }
  return false;
}

void drawFileChunk() {
  display.init(115200, true, 2, false);
  display.setRotation(1);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(GxEPD_BLACK);

  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(10, 20);
    display.print("Reading: ");
    display.println(currentFilename);
    display.println("-----------------------------------");

    if (SD.exists(currentFilename)) {
      File file = SD.open(currentFilename, FILE_READ);
      if (file) {
        file.seek(filePosition);
        int linesPrinted = 0;
        while (file.available() && linesPrinted < 8) {
          String line = file.readStringUntil('\n');
          display.println(line);
          linesPrinted++;
        }
        filePosition = file.position();
        file.close();
      } else {
        display.println("Error: Failed to open file.");
      }
    } else {
      display.println("Error: book.txt not found on SD!");
    }
  } while (display.nextPage());
}

void setup() {
  Serial.begin(115200);
  
  setUpButton(btnPrev);
  setUpButton(btnNext);
  setUpButton(btnSelect);

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
  } else {
    Serial.println("SD card initialized.");
  }

  display.init(115200);
  drawFileChunk();
}

void loop() {
  if (wasPressed(btnNext)) {
    drawFileChunk();
    delay(200);
  }

  if (wasPressed(btnSelect)) {
    filePosition = 0;
    drawFileChunk();
    delay(200);
  }

  delay(50);
}
