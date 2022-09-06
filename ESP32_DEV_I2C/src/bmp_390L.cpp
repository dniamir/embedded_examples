// Based on code from
// https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/
// Will communicate with a BMP390L (I2C address is 0x76)
// SCL - GPIO 22
// SDA - GPIO 21
// No pull-ups needed on the dev board.

#include <Wire.h>
#include <Arduino.h>
#define ONBOARD_LED 2

int address = 0x76;
int reg = 0x00;
float wait_time = 100;

// Never ending task
void toggleLED1(void *parameter){
  for(;;){ // infinite loop

    // Turn the LED on
    digitalWrite(ONBOARD_LED, HIGH);

    // Pause the task for 500ms
    vTaskDelay(*((float*)parameter) / portTICK_PERIOD_MS);

    // Turn the LED off
    digitalWrite(ONBOARD_LED, LOW);

    // Pause the task again for 500ms
    vTaskDelay(*((float*)parameter) / portTICK_PERIOD_MS);

    // Print which core the task is running on
    // Serial.print("Task 1 is running on: ");
    // Serial.println(xPortGetCoreID());
    // Serial.println(*((float*)parameter));
    // Serial.println();
  }
}
 
void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  Wire.begin();
  Serial.begin(115200);

  // float wait_time = 200; THIS WILL NOT WORK

  xTaskCreate(
    toggleLED1,    // Function that should be called
    "Toggle LED1",   // Name of the task (for debugging)
    1000,            // Stack size (bytes)
    (void*)&wait_time,            // Parameter to pass
    1,               // Task priority - the HIGHER the number, the better
    NULL             // Task handle
  );
  
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