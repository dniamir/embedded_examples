#include <Arduino.h>

#include <GxEPD.h>
#include <GxGDEW0154M10/GxGDEW0154M10.h>      // 1.54" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <BitmapGraphics.h>
#include <Fonts/FreeSansBold9pt7b.h>

#define ONBOARD_LED 2

GxIO_Class io (SPI, SS, 22, 21);
GxEPD_Class display(io, 16, 4);

const char* name = "FreeSansBold9pt7b";
const GFXfont* f = &FreeSansBold9pt7b;

void toggle_on_board_led(void * parameter){
  for(;;){ // infinite loop
    digitalWrite(ONBOARD_LED, HIGH);  
    delay(100);                 
    digitalWrite(ONBOARD_LED, LOW);    
    delay(100);
  }                  
}

void setup_lcd(void * parameter){
  Serial.println("Starting...");
  display.init();
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.update();
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(50, 15);
  display.println();
  display.println(" Daily Quote");
  display.update();
  delay(1000);
  display.eraseDisplay();
}

void setup() {
  pinMode(ONBOARD_LED, OUTPUT);

  Serial.begin(9600);

  delay(2000);

  // Start Blinking Lights
  xTaskCreate(toggle_on_board_led, "Toggle LED1", 1000, NULL,  1, NULL);

  // Setup Screen
  // xTaskCreate(setup_lcd, "Setup LCD", 1000, NULL,  1, NULL);
  setup_lcd(NULL);

}

void loop() {
  
  display.setRotation(1);
  display.drawBitmap(gImage_test, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
  delay(1000);

  display.setRotation(0);
  display.setFont(f);
  display.setCursor(15, 10);
  display.println();
  display.println("Darien: 1");
  display.update();

  delay(2000);
}