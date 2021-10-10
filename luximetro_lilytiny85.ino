//
//void setup() {
////  pinMode(3, INPUT_PULLUP);
//  pinMode(3, INPUT_PULLUP);
//}
//
//void loop() {
//  int buttonState = digitalRead(3);
//  digitalWrite(1, !buttonState);
//}

/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 * This example shows a full screen rectangle,
 * writes the rectangle size inside the rectangle,
 * and scrolls the size off the screen.
 *
 */

#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include <BH1750FVI.h> // BH1750FVI Light sensor library

BH1750FVI LightSensor(BH1750FVI::k_DevModeContHighRes);
unsigned int lux;

uint8_t width = 128;
uint8_t height = 32;

#include "font16x32digits.h"
const DCfont *currentFont = FONT16X32DIGITS;

const int HOLD_PIN = 3;
const int MODE_PIN = 4;

int sensorMode = LOW;
int hold = LOW;

void setup() {
  pinMode(HOLD_PIN, INPUT_PULLUP);
//  pinMode(MODE_PIN, INPUT_PULLUP);
  
  LightSensor.begin();
//  LightSensor.SetMode(BH1750FVI::k_DevModeContHighRes);
  
//  oled.begin(width, height, sizeof(tiny4koled_init_128x32br), tiny4koled_init_128x32br);
  oled.begin();
  oled.setFont(currentFont);
  oled.clear();
  oled.on();
  oled.switchRenderFrame();
}

void loop() {
    oled.clear();
//    sensorMode = digitalRead(MODE_PIN);
//    if (sensorMode) {
//      LightSensor.SetMode(BH1750FVI::k_DevModeContHighRes);
//    } else {
//      LightSensor.SetMode(BH1750FVI::k_DevModeContLowRes);
//    }
    
    hold = digitalRead(HOLD_PIN);
    if (hold) {
      lux = LightSensor.GetLightIntensity();
    }
    oled.print(lux);
    
//    if (sensorMode) {
//      for (uint8_t y = 1; y < 2; y++) {
//        oled.setCursor(125, y);
//        oled.startData();
//        oled.sendData(0b11111111);
//    //    oled.repeatData(0b11111111, 8);
//        oled.endData();
//      }
//    } else {
//      for (uint8_t y = 1; y < 3; y++) {
//        oled.setCursor(125, y);
//        oled.startData();
//        oled.sendData(0b11111111);
//    //    oled.repeatData(0b11111111, 8);
//        oled.endData();
//      }
//    }

    if (!hold) {
      for (uint8_t y = 1; y < 4; y++) {
        oled.setCursor(119, y);
        oled.startData();
        oled.sendData(0b11111111);
        oled.repeatData(0b11111111, 8);
        oled.endData();
      }
    }
    oled.switchFrame();
}
