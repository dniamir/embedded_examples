#include <Wire.h>
#include <Arduino.h>

const int BME680_I2C_ADDRESS = 0b1110110;
const byte WHO_AM_I_REGISTER = 0xD0;

// Initialize I2C
int I2C_SDA = PB7;
int I2C_SCL = PA15;

// I2C1:
// SDA: PA14, PB7
// SCL: PA13, PA15, PB8
// PA13 and PA14 are used for SWD
// PB8 is used for the LED

// I2C2:
// SDA: PF0-OSC-IN, PA8
// SCL: PA9
// Can't get I2C2 to work with Wire


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
  Serial.begin(19200);  // Does not work with clock speed of 9600 - PA2 is output
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.setSDA(I2C_SDA);
	Wire.setSCL(I2C_SCL);
  Wire.begin();
}

void loop() {
  byte sensorID = 5;
  sensorID = readRegister(BME680_I2C_ADDRESS, WHO_AM_I_REGISTER);
  Serial.print("Sensor ID: 0x");
  Serial.println(sensorID, HEX);  // Should be 0x61
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note: LOW is the voltage level for turning on the built-in LED on Blue Pill)
  delay(100);
  Serial.println("Test1");

  digitalWrite(LED_BUILTIN, HIGH);    // Turn the LED off by making the voltage HIGH (Note: this is because the LED is active-low on the Blue Pill)
  delay(100);
}
