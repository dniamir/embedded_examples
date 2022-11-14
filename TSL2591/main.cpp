# include <TSL2591.h>
# include <Wire.h>
# include <Arduino.h>
# include <chip.h>

// Define sensor
ArduinoI2C arduino_i2c;
TSL2591 temp_sensor = TSL2591(arduino_i2c);

int I2C_SDA = 33;
int I2C_SCL = 32;

void setup() {
  Serial.begin(9600);

  Wire.begin(I2C_SDA, I2C_SCL);

  temp_sensor.initialize();
  delay(200);
  temp_sensor.enable();
  temp_sensor.configure_sensor();

}

void loop() {
  temp_sensor.read_full_luminosity();
  Serial.println(temp_sensor.light_fs);
  Serial.println(temp_sensor.light_ir);
  Serial.println(temp_sensor.light_vis);
  
  Serial.println();
  delay(1000);
}
