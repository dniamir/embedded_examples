#include <Arduino.h>

int LED_BUILTIN_TEMP = 3;

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN_TEMP, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN_TEMP, HIGH);
  // wait for a second
  delay(400);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN_TEMP, LOW);
   // wait for a second
  delay(400);
}