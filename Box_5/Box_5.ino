#include <Adafruit_NeoPixel.h>
#include <Servo.h>
Servo latch;
const byte KNOB_PINS[4] = { 0, 1, 2, 3};
const byte LIGHT_PINS[4] = { 0, 1, 2, 3};
bool STATE[4] = { false, false, false, false};
int KEY[4] = {700, 800, 500, 900};
#define NUMPIXELS 4
#define tolerance 50
bool done = false;
Adafruit_NeoPixel pixels(NUMPIXELS, 7, NEO_RGB + NEO_KHZ800);
void setup() {
  pixels.begin();
  latch.attach(9);
  Serial.begin(9600);
  latch.write(0);
}
void loop() {
  CheckPins();
  error();
  activate();
}

void CheckPins() {
  //Serial.println(analogRead(0));
  for (int i = 0; i < 4; i++) {
    if ((analogRead(KNOB_PINS[i]) <= (KEY[i] + tolerance)) &&
      (analogRead(KNOB_PINS[i]) >= (KEY[i] - tolerance)))
    {
      STATE[i] = true;
      Serial.println("yes");
    } else {
      STATE[i] = false;
      Serial.println("no");
    }
  }
}
void error() {
  for (int i = 0; i < 4; i++) {
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
      STATE[3] == true ) {
    latch.write(90);
    Serial.println("DONE");
  }
}



