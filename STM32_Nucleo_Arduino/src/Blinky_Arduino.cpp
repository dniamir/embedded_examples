#include <Arduino.h>

// HardwareSerial Serial(PA10, PA9);

void setup() {
  Serial.begin(19200);  // Does not work with clock speed of 9600 - PA2 is output
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note: LOW is the voltage level for turning on the built-in LED on Blue Pill)
  delay(500);
  Serial.println("Test1");

  digitalWrite(LED_BUILTIN, HIGH);    // Turn the LED off by making the voltage HIGH (Note: this is because the LED is active-low on the Blue Pill)
  delay(500);
}