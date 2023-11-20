#include <Wire.h>
#include <Arduino.h>

const int BME680_I2C_ADDRESS = 0b1110110;
const byte WHO_AM_I_REGISTER = 0xD0;

// Initialize I2C
int I2C_SDA = PA8;
int I2C_SCL = PA9;

// PA13 is SCL1 and PA14 is SDA1
// or
// PB8 is SCL1 and PB7 is SDA1

// PC14 is SCL2 and PF0-OSC_IN is SDA2
// or
// PA9 is SCL2 and PA8 is SDA2

TwoWire myWire2(PA9, PA8); // PA9 = SDA, PA8 = SCL for I2C2


// Declare and define the readRegister function before setup
byte readRegister(byte address, byte reg) {
    myWire2.beginTransmission(address);
    myWire2.write(reg);
    byte error = myWire2.endTransmission();

    // If there was an I2C error during transmission, reinitialize I2C and return 0xFF
    if (error) {
        myWire2.flush(); // Clear the buffer
        myWire2.end();   // End the I2C connection
        delay(10);    // Short delay (optional, for stabilization)
        myWire2.begin(); // Reinitialize I2C
        return 0xFF;
    }

    myWire2.requestFrom(address, (byte)1);
    if (myWire2.available()) {
        return myWire2.read();
    }

    return 0xFF; // Return 0xFF if there was an issue with the reading
}



void setup() {
  Serial.begin(19200);  // Does not work with clock speed of 9600 - PA2 is output
  pinMode(LED_BUILTIN, OUTPUT);
  // myWire2.setSDA(I2C_SDA);
	// myWire2.setSCL(I2C_SCL);
  myWire2.begin();
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
