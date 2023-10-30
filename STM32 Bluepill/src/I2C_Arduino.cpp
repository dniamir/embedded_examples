#include <Wire.h>
#include <Arduino.h>

const int BME680_I2C_ADDRESS = 0b1110110;
const byte WHO_AM_I_REGISTER = 0xD0;

// Initialize I2C
int I2C_SDA = 43;
int I2C_SCL = 42;

// B6 is SCL
// B7 is SDA

// Declare and define the readRegister function before setup
byte readRegister(byte address, byte reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    byte error = Wire.endTransmission();

    // If there was an I2C error during transmission, reinitialize I2C and return 0xFF
    if (error) {
        Wire.flush(); // Clear the buffer
        Wire.end();   // End the I2C connection
        delay(10);    // Short delay (optional, for stabilization)
        Wire.begin(); // Reinitialize I2C
        return 0xFF;
    }

    Wire.requestFrom(address, (byte)1);
    if (Wire.available()) {
        return Wire.read();
    }

    return 0xFF; // Return 0xFF if there was an issue with the reading
}



void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin();
}

void loop() {
  byte sensorID = 5;
  sensorID = readRegister(BME680_I2C_ADDRESS, WHO_AM_I_REGISTER);
  Serial.print("Sensor ID: 0x");
  Serial.println(sensorID, HEX);
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note: LOW is the voltage level for turning on the built-in LED on Blue Pill)
  delay(100);
  Serial.println("Test1");

  digitalWrite(LED_BUILTIN, HIGH);    // Turn the LED off by making the voltage HIGH (Note: this is because the LED is active-low on the Blue Pill)
  delay(100);
}
