#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <Stepper.h>
const int stepsPerRevolution = 5000;
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);
int stepCount = 0;
Servo latch;
const byte BUTTON_PINS[4] = { 4, 2, 5, 3};
const byte LIGHT_PINS[4] = { 0, 1, 2, 3};
bool STATE[4] = { false, false, false, false};
#define NUMPIXELS 4
bool done = false;

Adafruit_NeoPixel pixels(NUMPIXELS, 7, NEO_RGB + NEO_KHZ800);
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
  for (int i = 0; i < 4; i++) {
    if (digitalRead(BUTTON_PINS[i]) == LOW) {
      STATE[i] = true;
      Serial.println("flipped");
    } else {
      STATE[i] = false;
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
  if (digitalRead(BUTTON_PINS[0]) == HIGH &&
      digitalRead(BUTTON_PINS[1]) == HIGH &&
      digitalRead(BUTTON_PINS[2]) == HIGH &&
      digitalRead(BUTTON_PINS[3]) == HIGH && 
      done == false ) {
    motor();
    done = true; 
    Serial.println("DONE");
  }
}

void motor() {
  Serial.begin(9600);
  for (int i = 0; i < 2350; i++) {
    myStepper.step(1);
    Serial.print("steps:");
    Serial.println(stepCount);
    stepCount++;
  }
}

