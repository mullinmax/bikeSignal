// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// turn signal cycle in milliseconds
#define TURNCYCLE 750

// brightness of turn signal
#define BRIGHTNESS 175

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void turnSignal(int t, boolean right);
void brakeSignal(int brightness);
void clearSignal();

boolean leftPressed = false;
boolean rightPressed = false;
boolean turning = false;
boolean right = false;
boolean braking = false;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();
    delay(250);
  }
}

void loop() {

  if (digitalRead(3) == HIGH) {
    braking = false;
  } else {
    braking = true;
  }

  if (digitalRead(0) == HIGH) {
    leftPressed = true;
  }

  if (digitalRead(1) == HIGH) {
    rightPressed = true;
  }

  if (digitalRead(0) == LOW && digitalRead(1) == LOW) {
    leftPressed = false;
    rightPressed = false;
  }
  if (leftPressed && rightPressed) {
    turning  = false;
  }

  if (!leftPressed && rightPressed) {
    right = true;
    turning = true;
  } else if (leftPressed && ! rightPressed) {
    right = false;
    turning = true;
  }

  clearSignal();
  if (braking) {
    brakeSignal(BRIGHTNESS);
  }
  if (turning) {
    turnSignal(TURNCYCLE, right);
  }
  pixels.show();
}

void turnSignal(int t, boolean right) {
  if ((millis() % t) > (t / 2)) {
    for (int i = 0; i < NUMPIXELS; i++) {
      if ((i < NUMPIXELS / 2) ^ right) {
        pixels.setPixelColor(i, pixels.Color(239, 123, 0));
      }
    }
  }
}

void brakeSignal(int brightness) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(brightness, 0, 0));
  }
}

void clearSignal() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

