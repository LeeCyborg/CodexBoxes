#include <Adafruit_NeoPixel.h>
#include <Servo.h>
Servo latch;
#define PIN 6
#define NUMPIXELS 1
#define buttonPin 2
#include <Stepper.h>
const int stepsPerRevolution = 5000;
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);
int stepCount = 0;
bool state = false;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  pixels.begin();
  latch.attach(9);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
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
  motor();
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

