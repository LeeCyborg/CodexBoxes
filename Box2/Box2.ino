
#include <Adafruit_NeoPixel.h>

#include <Servo.h>
Servo latch;
const byte BUTTON_PINS[6] = { 2, 3, 4, 5, 6, 7};
#define NUMPIXELS 1
#define knife 2
bool state = false;

Adafruit_NeoPixel pixels(NUMPIXELS, 10, NEO_RGB + NEO_KHZ800);
void setup() {
  pixels.begin();
  latch.attach(9);
  Serial.begin(9600);
  for (byte i = 0; i < 5; i++){
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  pinMode(knife, INPUT_PULLUP);
  latch.write(0);
}

void loop() {
  if (digitalRead(2) == HIGH && state == false) {
    error();
    Serial.println("on");
  } else {
    flip();
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

void flip() {
  activated();
  state = true;
  latch.write(90);
}



