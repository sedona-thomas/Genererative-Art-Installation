/*
 * TTGO Text Visualization: scrolls through the UDHR in the two original languages (French and English)
 * 
 * @author Sedona Thomas
 * @author snt2127
 */

#define WAIT 500 // miliseconds

#include <stdint.h>
#include <iostream>
#include <fstream>

#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

uint32_t currentBackgroundColor = TFT_WHITE;
uint32_t currentTextColor = TFT_BLACK;
uint8_t currentTextSize = 1; // 10 pixels

unsigned long startTime = 0;
unsigned long loopStartTime = 0; // Used for testing draw times

void setup(void) {
  tft.init();
  tft.setRotation(1);
  startTime = millis();
}

void loop() {
  loopStartTime = millis();
  setupScreen();

  std::vector<String> strs = {"a", " ", "b", " ", "c"};
  writeScrollingLine(strs, 0, 0, 1);
}

void setupScreen() {
  tft.setTextSize(currentTextSize);
  tft.fillScreen(currentBackgroundColor);
  tft.setTextColor(currentTextColor);
}

std::string readFile(std::string fileName) {
  std::ifstream in(fileName);
  std::string fileContents((std::istreambuf_iterator<char>(in)),  std::istreambuf_iterator<char>());
  return fileContents;
}

void writeScrollingLine(std::vector<String> strs, int xPos, int yPos, int size) {
  for (int i = 0; i < strs.size(); i++) {
    int currentX = xPos;
    tft.fillScreen(currentBackgroundColor);
    tft.setTextColor(currentTextColor);
    std::vector<String> subStrs = {strs.begin() + i, strs.end()};
    for (const auto& str : subStrs) {
      xPos += tft.drawString(str, xPos, yPos, size);
    }
    delay(WAIT);
  }
}

void writeLine(std::vector<String> strs, int xPos, int yPos, int size) {
  tft.fillScreen(currentBackgroundColor);
  tft.setTextColor(currentTextColor);
  for (const auto& str : strs) {
    xPos += tft.drawString(str, xPos, yPos, size);
  }
  delay(WAIT);
}

// https://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
inline uint16_t getRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}


//std::string readFile(std::string fileName) {
//  std::ifstream in(fileName);
//  std::string fileContents((std::istreambuf_iterator<char>(in)),  std::istreambuf_iterator<char>());
//  return fileContents;
//}
//
//void writeLine(const char *chars, int xPos, int yPos, int size) {
//  tft.fillScreen(currentBackgroundColor);
//  tft.setTextColor(currentTextColor);
//  while (*chars++) {
//    String c = chars;
//    xPos += tft.drawString(c, xPos, yPos, size);
//  }
//  delay(WAIT);
//}
//
//void writeScrollingLine(const char *chars, int xPos, int yPos, int size) {
//  while (*chars++) {
//    int currentX = xPos;
//    const char *c = chars;
//    tft.fillScreen(currentBackgroundColor);
//    tft.setTextColor(currentTextColor);
//    while (*c++) {
//      currentX += tft.drawString(c, currentX, yPos, size);
//    }
//    delay(WAIT);
//  }
//}
