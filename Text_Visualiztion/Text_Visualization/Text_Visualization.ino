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

  std::string fileName = "";
  std::string fileString = readFile(fileName);
  char *fileChars = fileString.c_str();
  
  writeScrollingLine(strs, 0, 0, 1);
}

void setupScreen() {
  tft.setTextSize(currentTextSize);
  tft.fillScreen(currentBackgroundColor);
  tft.setTextColor(currentTextColor);
}

std::string readFile(std::string fileName) {
  std::ifstream in(fileName);
  std::string contents((std::istreambuf_iterator<char>(in)),  std::istreambuf_iterator<char>());
  return contents;
}

void writeScrollingLine(char *chars, int xPos, int yPos, int size) {
  for (int i = 0; i < chars.size(); i++) {
    int currentX = xPos;
    char *c = chars;
    tft.fillScreen(currentBackgroundColor);
    tft.setTextColor(currentTextColor);
    while (*c++) {
      currentX += tft.drawString(c, currentX, yPos, size);
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

std::vector<String> splitByChar(

// https://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
inline uint16_t getRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}
