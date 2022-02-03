/*
 * TTGO Text Visualization: 
 * 
 * @author Sedona Thomas
 * @author snt2127
 */

#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h


// background color
#define BACKGROUND_COLOR 0x38E0

// Pause in milliseconds between screens, change to 0 to time font rendering
#define WAIT 500


unsigned long targetTime = 0; // Used for testing draw times

void setup(void) {
  tft.init();
  tft.setRotation(1);
}

void loop() {
  loopStartTime = millis();

  tft.setTextSize(1);
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK);

  tft.drawString("This is a test.", 0, 0, 2);
  //int xpos = 0;
  //xpos += tft.drawString("test2", 0, 64, 2);
  //tft.drawChar(127, xpos, 64, 2);
  delay(WAIT);

  tft.drawString("current loop runtime", 0, 48, 2);
  tft.drawNumber(millis() - loopStartTime, 0, 100, 4);
  

}
