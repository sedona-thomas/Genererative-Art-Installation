/*
 * TTGO Text Visualization: scrolls through the UDHR in the two original languages (French and English)
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
  writeScrollingLine(strs, 0, 0, 1);
}

void setupScreen() {
  tft.setTextSize(currentTextSize);
  tft.fillScreen(currentBackgroundColor);
  tft.setTextColor(currentTextColor);
}

void writeScrollingLine(std::vector<String> chars, int xPos, int yPos, int size) {
  for (int i = 0; i < chars.size(); i++) {
    int currentX = xPos;
    tft.fillScreen(currentBackgroundColor);
    tft.setTextColor(currentTextColor);
    for_each(chars.begin() + i, chars.end(),[](){ currentX += tft.drawString(chars, xPos, yPos, size); });
    delay(WAIT);
  }
}

void writeLine(std::vector<String> strs, int xPos, int yPos, int size) {
  tft.fillScreen(currentBackgroundColor);
  tft.setTextColor(currentTextColor);
  for(const auto& str : strs) {
    xPos += tft.drawString(str, xPos, yPos, size);
  }
  delay(WAIT);
}

// https://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
inline uint16_t getRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}
