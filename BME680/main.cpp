// Will communicate with a BMP680 (I2C address is 0x76)
// SCL - GPIO 32
// SDA - GPIO 33
// No pull-ups needed on the dev board.
// This reads the ID address
// The right output should be 61h

#include <Wire.h>
#include <Arduino.h>
#define ONBOARD_LED 2

int address = 0x76;
int reg = 0xD0;
float wait_time = 100;
 
void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  Wire.begin(33, 32);
  Serial.begin(9600);
  
}
 
void loop() {

  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, 1);
  uint8_t byte = Wire.read();
  Serial.println("The slave address / reg address / reg value are:");

  // Dev values
  Serial.print(address);
  Serial.print(" / ");
  Serial.print(reg);
  Serial.print(" / ");
  Serial.print(byte);
  Serial.println("");

  // Hex values
  Serial.print("0x");
  Serial.print(String(address, HEX));
  Serial.print(" / 0x");
  Serial.print(String(reg, HEX));
  Serial.print(" / 0x");
  Serial.print(String(byte, HEX));
  Serial.println("");

  Serial.println("");

  delay(500);
  
}