#include <Arduino.h>

void setup() {
  Serial.begin(9600);  // Connect A9 (STM32 TX) to the USB->UART TX (SWO)
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note: LOW is the voltage level for turning on the built-in LED on Blue Pill)
  delay(100);
  Serial.println("Test1");

  digitalWrite(LED_BUILTIN, HIGH);    // Turn the LED off by making the voltage HIGH (Note: this is because the LED is active-low on the Blue Pill)
  delay(100);
}