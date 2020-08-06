/*
  The TFT_eSPI library incorporates an Adafruit_GFX compatible
  button handling class, this sketch is based on the Arduin-o-phone
  example.

  This example diplays a keypad where numbers can be entered and
  send to the Serial Monitor window.

  The sketch has been tested on the ESP8266 (which supports SPIFFS)

  The minimum screen size is 320 x 240 as that is the keypad size.
*/

// The SPIFFS (FLASH filing system) is used to hold touch screen
// calibration data

#include "FS.h"

#include <SPI.h>
#include <TFT_eSPI.h>      // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

// This is the file name used to store the calibration data
// You can change this to create new calibration files.
// The SPIFFS file name must start with "/".
#define CALIBRATION_FILE "/TouchCalData1"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false

// Keypad start position, key sizes and spacing
#define KEY_X 43 // Centre of key 40
#define KEY_Y 45 //96
#define KEY_W 68 // Width and height
#define KEY_H 68
#define KEY_SPACING_X 10 // X and Y gap
#define KEY_SPACING_Y 10
#define KEY_TEXTSIZE 3   // Font size multiplier

// Create 15 keys for the keypad
char keyLabel[12][4] = {"1", "2", "3", 
                        "4", "5", "6", 
                        "7", "8","9", 
                        "<-", "0", "C"
                       };
                       
uint16_t keyColor[12] = {
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                         TFT_BLACK, TFT_BLACK, TFT_BLACK,
                        };

uint16_t keyTextColor[12] = {
                         TFT_WHITE, TFT_WHITE, TFT_WHITE,
                         TFT_WHITE, TFT_WHITE, TFT_WHITE,
                         TFT_WHITE, TFT_WHITE, TFT_WHITE,
                         TFT_WHITE, TFT_WHITE, TFT_RED,
                        };

// Invoke the TFT_eSPI button class and create all the button objects
TFT_eSPI_Button key[12];

//------------------------------------------------------------------------------------------

void setup() {
  // Use serial port
  Serial.begin(115200);

  // Initialise the TFT screen
  tft.init();

  // Set the rotation before we calibrate
  tft.setRotation(0);

  // Calibrate the touch screen and retrieve the scaling factors
//  uint16_t calData[5] = { 364, 3548, 240, 3575, 7 }; old
  uint16_t calData[5] = { 251, 3570, 392, 3467, 4 };

  tft.setTouch(calData);

  // Clear the screen
  tft.fillScreen(TFT_BLACK);

  // Draw keypad background
  tft.fillRect(0, 0, 240, 320, TFT_BLACK);

  // Draw keypad
  drawKeypad();
}

//------------------------------------------------------------------------------------------

void loop(void) {
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  boolean pressed = tft.getTouch(&t_x, &t_y);

  // / Check if any key coordinate boxes contain the touch coordinates
  for (uint8_t b = 0; b < 12; b++) {
    if (pressed && key[b].contains(t_x, t_y)) {
      
      key[b].press(true);  // tell the button it is pressed
    } else {
      key[b].press(false);  // tell the button it is NOT pressed
    }
  }

  // Check if any key has changed state
  for (uint8_t b = 0; b < 12; b++) {
    if (key[b].justReleased()) key[b].drawButton();     // draw normal

    if (key[b].justPressed()) {
        key[b].drawButton(true);  // draw invert

     if(b >= 0){
       Serial.println(keyLabel[b][0]); 
     }
      delay(100); // UI debouncing
    }
  }
}

//------------------------------------------------------------------------------------------

void drawKeypad(){ 
  //Draw Horizontal Lines
  //  for (int h = 80; h <= 320; h += 80)
  //    tft.drawFastHLine(0, h, 240, TFT_DARKGREY);

  //Draw Vertical Lines
  //  for (int v=80; v<=240; v+=80)
  //    tft.drawFastVLine(v, 0, 320, TFT_WHITE);

  // Draw the keys
  for (uint8_t row = 0; row < 4; row++) {
    for (uint8_t col = 0; col < 3; col++) {
      uint8_t b = col + row * 3;
      key[b].initButton(&tft,
                        KEY_X + col * (KEY_W + KEY_SPACING_X), // x
                        KEY_Y + row * (KEY_H + KEY_SPACING_Y) , // y
                        KEY_W, // width btn
                        KEY_H, // height btn
                        TFT_BLACK, // outline
                        keyColor[b], // btn color
                        keyTextColor[b], // text color
                        keyLabel[b],  // label
                        KEY_TEXTSIZE); // text size
      key[b].drawButton();
    }
  }
}

//------------------------------------------------------------------------------------------
