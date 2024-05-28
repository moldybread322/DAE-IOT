#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "thingProperties.h"

#define LEDPIN 2

// Initialize TCS34725 with a valid integration time and gain
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup() {
  // Initialize serial and wait for port to open
  Serial.begin(9600);
  delay(1500);

  // Initialize the IoT Cloud properties
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Set debug level
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Initialize LED pin
  pinMode(LEDPIN, OUTPUT);

  // Initialize TCS34725 sensor
  if (tcs.begin()) {
    Serial.println("Found color sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // Halt
  }
}

void loop() {
  ArduinoCloud.update();

  // Get RGB and light intensity data
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  float lux = tcs.calculateLux(r, g, b);

  // Update the cloud variables
  redValue = r;
  greenValue = g;
  blueValue = b;
  lightIntensity = lux;

  delay(2000); // Update every 2 seconds
}

void onLedStateChange() {
  // This function is called whenever ledState variable changes
  digitalWrite(LEDPIN, ledState ? HIGH : LOW);
}
