#include <Arduino.h>

#define ONBOARD_LED 2
const int ledPin = 23;

// Never ending task
void toggleLED1(void * parameter){
  for(;;){ // infinite loop

    // Turn the LED on
    digitalWrite(ONBOARD_LED, HIGH);

    // Pause the task for 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // Turn the LED off
    digitalWrite(ONBOARD_LED, LOW);

    // Pause the task again for 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // Print which core the task is running on
    Serial.print("Task 1 is running on: ");
    Serial.println(xPortGetCoreID());
  }
}

void toggleLED2(void * parameter){
  for(;;){ // infinite loop

    // Turn the LED on
    digitalWrite(ledPin, HIGH);

    // Pause the task for 500ms
    vTaskDelay(250 / portTICK_PERIOD_MS);

    // Turn the LED off
    digitalWrite(ledPin, LOW);

    // Pause the task again for 500ms
    vTaskDelay(250 / portTICK_PERIOD_MS);

    // Print which core the task is running on
    Serial.print("Task 2 is running on: ");
    Serial.println(xPortGetCoreID());
  }
}

// One off task
void uploadToAWS(void * parameter){
    // Implement your custom logic here

    // When you're done, call vTaskDelete. Don't forget this!
    // This is one way of ending the task (from within the task itself)
    vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);

  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(ledPin, OUTPUT);

  xTaskCreate(
    toggleLED1,    // Function that should be called
    "Toggle LED1",   // Name of the task (for debugging)
    1000,            // Stack size (bytes)
    NULL,            // Parameter to pass
    1,               // Task priority - the HIGHER the number, the better
    NULL             // Task handle
  );

  xTaskCreate(
    toggleLED2,    // Function that should be called
    "Toggle LED2",   // Name of the task (for debugging)
    1000,            // Stack size (bytes)
    NULL,            // Parameter to pass
    1,               // Task priority - the HIGHER the number, the better
    NULL             // Task handle
  );

  xTaskCreate(
    uploadToAWS,    // Function that should be called
    "Upload to AWS",  // Name of the task (for debugging)
    1000,            // Stack size (bytes)
    NULL,            // Parameter to pass
    1,               // Task priority - the HIGHER the number, the better
    NULL             // Task handle
  );

  // A task that is tied to a specific core (ESP32 is dual core)
  xTaskCreatePinnedToCore(
      uploadToAWS,      // Function that should be called
      "Upload to AWS",    // Name of the task (for debugging)
      1000,               // Stack size (bytes)
      NULL,               // Parameter to pass
      1,                  // Task priority - the HIGHER the number, the better
      NULL,               // Task handle
      0          // Core you want to run the task on (0 or 1)
  );

}

void loop() {
  // digitalWrite(ONBOARD_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(20);                  // wait for a second
  // digitalWrite(ONBOARD_LED, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000);                  // wait for a second
}

