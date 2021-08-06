
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 1
#define buttonPin 2

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  pixels.begin();
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(2) == HIGH) {
    error();
    Serial.println("on");
  } else {
    activated();
    Serial.println("off");
  }
}
void error() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();
    delay(100);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
    delay(100);
  }
}

void activated() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();
  }
}



