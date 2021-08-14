
#include <Adafruit_NeoPixel.h>

#include <Servo.h>
Servo latch;
const byte BUTTON_PINS[6] = { 2, 3, 4, 5, 6, 7};
const byte LIGHT_PINS[6] = { 0, 1, 2, 3, 4, 5};
bool STATE[6] = { false, false, false, false, false, false};
#define NUMPIXELS 6
bool done = false;

Adafruit_NeoPixel pixels(NUMPIXELS, 10, NEO_RGB + NEO_KHZ800);
void setup() {
  pixels.begin();
  latch.attach(9);
  Serial.begin(9600);
  for (byte i = 0; i < 7; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  latch.write(0);
}

void loop() {
  CheckPins();
  error();
  activate();
}

void CheckPins() {
  for (int i = 0; i < 6; i++) {
    if (digitalRead(BUTTON_PINS[i]) == LOW) {
      STATE[i] = true;
      Serial.println("flipped");
    }
  }
}
void error() {
  for (int i = 0; i < 7; i++) {
    if (STATE[i] == true) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      pixels.show();
    } else {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();
    }
  }
}

void activate() {
  if (STATE[0] == true &&
      STATE[1] == true &&
      STATE[2] == true &&
      STATE[3] == true &&
      STATE[4] == true &&
      STATE[5] == true) {
      latch.write(90);
      Serial.println("DONE");
  }
}



