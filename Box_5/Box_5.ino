#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <Stepper.h>
const int stepsPerRevolution = 5000;
Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);
int stepCount = 0;
Servo latch;
const byte KNOB_PINS[5] = { 0, 1, 2, 3, 4};
const byte LIGHT_PINS[5] = { 0, 1, 2, 3, 4};
bool STATE[5] = { false, false, false, false, false};
int KEY[5] = {300, 300, 300, 500, 500};
#define NUMPIXELS 5
#define tolerance 20
bool done = false;
Adafruit_NeoPixel pixels(NUMPIXELS, 7, NEO_RGB + NEO_KHZ800);
void setup() {
  pixels.begin();
  latch.attach(9);
  Serial.begin(9600);
  latch.write(0);
  for (int i = 0; i < 5; i++) { // callibrate 
    KEY[i] = analogRead(i) + random(50,400);
  }
}
void loop() {

  CheckPins();
  error();
  activate();
}

void CheckPins() {

  Serial.println(analogRead(0));
  for (int i = 0; i < 5; i++) {
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
  for (int i = 0; i < 5; i++) {
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
      done == false) {
    for (int i = 0; i < 5; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      pixels.show();
    }
    motor();
    done = true;
    Serial.println("DONE");
  }
}
void motor() {
  Serial.begin(9600);
  for (int i = 0; i < 2350; i++) {
    myStepper.step(- 1);
    Serial.print("steps:");
    Serial.println(stepCount);
    stepCount++;
  }
}



