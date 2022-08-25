#include <Arduino.h>

#define ONBOARD_LED 2

void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
}

void loop() {
  digitalWrite(ONBOARD_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(20);                  // wait for a second
  digitalWrite(ONBOARD_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                  // wait for a second
}