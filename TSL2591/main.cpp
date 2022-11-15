# include <TSL2591.h>
# include <Wire.h>
# include <Arduino.h>
# include <chip.h>

// Define sensor
ArduinoI2C arduino_i2c;
TSL2591 temp_sensor = TSL2591(arduino_i2c);

// Interrupt Pin
const int tsl_interrupt_pin = 35;  // the number of the pushbutton pin

int I2C_SDA = 33;
int I2C_SCL = 32;

void setup() {
  Serial.begin(9600);

  Wire.begin(I2C_SDA, I2C_SCL);

  temp_sensor.initialize();
  delay(200);
  temp_sensor.enable();
  temp_sensor.configure_sensor();

  temp_sensor.write_tsl_field("AIEN", 0);  // Disable Persist Interrupt
  temp_sensor.write_tsl_field("NPIEN", 1);  // Enable No-Persist Interrupt

  // Interrupt - Minimum value of 50
  temp_sensor.write_tsl_field("NPAILTL", 50);  // No persist low threshold low byte
  temp_sensor.write_tsl_field("NPAILTH", 0);  // No persist low threshold high byte

  // Interrupt - Maximum value of 6000
  temp_sensor.write_tsl_field("NPAIHTL", 6000 & 0b11111111);  // No persist high threshold low byte
  temp_sensor.write_tsl_field("NPAIHTH", 6000 >> 8);  // No persist high threshold high byte

  // Setup interrupt pin
  pinMode(tsl_interrupt_pin, INPUT);

}

void loop() {
  temp_sensor.read_full_luminosity();
  Serial.println("Readings");
  Serial.println(temp_sensor.light_fs);
  Serial.println(temp_sensor.light_ir);
  Serial.println(temp_sensor.light_vis);
  Serial.println();

  int tsl_interrupt_state = digitalRead(tsl_interrupt_pin);
  Serial.println("TSL Interrupt State");
  Serial.println(tsl_interrupt_state);
  Serial.println();

  // Clear Interrupt
  temp_sensor.clear_interrupt();  // Reset Interrupt
  delay(1000);

}
