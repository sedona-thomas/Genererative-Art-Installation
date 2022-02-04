/*
 * TTGO Text Visualization: 
 * 
 * @author Sedona Thomas
 * @author snt2127
 */

#define WAIT 500 // miliseconds

#include <stdint.h>
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

uint32_t currentBackgroundColor = TFT_WHITE;
uint32_t currentTextColor = TFT_BLACK;
uint8_t currentTextSize = 1; // 10 pixels

unsigned long startTime = 0;
unsigned long loopStartTime = 0; // Used for testing draw times

void writeLine(std::vector<String> strs, int yPos, int size);
void drawDegreeSymbol(int xPos, int yPos, int size);
inline uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue);

void setup(void) {
  tft.init();
  tft.setRotation(1);
  startTime = millis();
}

void loop() {
  loopStartTime = millis();
  setupScreen();

  std::vector<String> strs = {"hello", " ", "world"};
  writeLine(strs, 0, 0, 1);
  delay(WAIT);
}

void setupScreen() {
  tft.setTextSize(currentTextSize);
  tft.fillScreen(currentBackgroundColor);
  tft.setTextColor(currentTextColor);
}

void writeLine(std::vector<String> strs, int xPos, int yPos, int size) {
  tft.fillScreen(currentBackgroundColor);
  tft.setTextColor(currentTextColor);
  for(const auto& str : strs) {
    xPos += tft.drawString(str, xPos, yPos, size);
  }
}

void drawDegreeSymbol(int xPos, int yPos, int size) {
  tft.drawChar(127, xPos, yPos, size);
}

// https://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
inline uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
  red   >>= 3;
  green >>= 2;
  blue  >>= 3;
  return (red << 11) | (green << 5) | blue;
}
