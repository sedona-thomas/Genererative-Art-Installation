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

std::string EnglishUDHR = "Universal Declaration of Human Rights Preamble Whereas recognition of the inherent dignity and of the equal and inalienable rights of all members of the human family is the foundation of freedom, justice and peace in the world, Whereas disregard and contempt for human rights have resulted in barbarous acts which have outraged the conscience of mankind, and the advent of a world in which human beings shall enjoy freedom of speech and belief and freedom from fear and want has been proclaimed as the highest aspiration of the common people, Whereas it is essential, if man is not to be compelled to have recourse, as a last resort, to rebellion against tyranny and oppression, that human rights should be protected by the rule of law, Whereas it is essential to promote the development of friendly relations between nations, Whereas the peoples of the United Nations have in the Charter reaffirmed their faith in fundamental human rights, in the dignity and worth of the human person and in the equal rights of men and women and have determined to promote social progress and better standards of life in larger freedom, Whereas Member States have pledged themselves to achieve, in cooperation with the United Nations, the promotion of universal respect for and observance of human rights and fundamental freedoms, Whereas a common understanding of these rights and freedoms is of the greatest importance for the full realization of this pledge, Now, therefore, The General Assembly, Proclaims this Universal Declaration of Human Rights as a common standard of achievement for all peoples and all nations, to the end that every individual and every organ of society, keeping this Declaration constantly in mind, shall strive by teaching and education to promote respect for these rights and freedoms and by progressive measures, national and international, to secure their universal and effective recognition and observance, both among the peoples of Member States themselves and among the peoples of territories under their jurisdiction.";
std::string FrenchUDHR = "Déclaration universelle des droits de l'homme Préambule Considérant que la reconnaissance de la dignité inhérente à tous les membres de la famille humaine et de leurs droits égaux et inaliénables constitue le fondement de la liberté, de la justice et de la paix dans le monde, Considérant que la méconnaissance et le mépris des droits de l'homme ont conduit à des actes de barbarie qui révoltent la conscience de l'humanité et que l'avènement d'un monde où les êtres humains seront libres de parler et de croire, libérés de la terreur et de la misère, a été proclamé comme la plus haute aspiration de l'homme, Considérant qu'il est essentiel que les droits de l'homme soient protégés par un régime de droit pour que l'homme ne soit pas contraint, en suprême recours, à la révolte contre la tyrannie et l'oppression, Considérant qu'il est essentiel d'encourager le développement de relations amicales entre nations, Considérant que dans la Charte les peuples des Nations Unies ont proclamé à nouveau leur foi dans les droits fondamentaux de l'homme, dans la dignité et la valeur de la personne humaine, dans l'égalité des droits des hommes et des femmes, et qu'ils se sont déclarés résolus à favoriser le progrès social et à instaurer de meilleures conditions de vie dans une liberté plus grande, Considérant que les Etats Membres se sont engagés à assurer, en coopération avec l'Organisation des Nations Unies, le respect universel et effectif des droits de l'homme et des libertés fondamentales, Considérant qu'une conception commune de ces droits et libertés est de la plus haute importance pour remplir pleinement cet engagement, L'Assemblée générale Proclame la présente Déclaration universelle des droits de l'homme comme l'idéal commun à atteindre par tous les peuples et toutes les nations afin que tous les individus et tous les organes de la société, ayant cette Déclaration constamment à l'esprit, s'efforcent, par l'enseignement et l'éducation, de développer le respect de ces droits et libertés et d'en assurer, par des mesures progressives d'ordre national et international, la reconnaissance et l'application universelles et effectives, tant parmi les populations des Etats Membres euxmêmes que parmi celles des territoires placés sous leur juridiction.";

void setupScreen();
void writeDoubleScrollingLine(std::vector<String> strs1, std::vector<String> strs2, int xPos, int yPos, int size);
void writeScrollingLine(std::vector<String> strs, int xPos, int yPos, int size);
void writeLine(std::vector<String> strs, int xPos, int yPos, int size);
std::vector<String> getCharacterVector(std::string str);
inline uint16_t getRGB(uint8_t r, uint8_t g, uint8_t b);

void setup(void) {
  tft.init();
  tft.setRotation(1);
  startTime = millis();
}

void loop() {
  loopStartTime = millis();
  setupScreen();

  //std::vector<String> strs = {"a", " ", "b", " ", "c"};

  writeDoubleScrollingLine(getCharacterVector(EnglishUDHR), getCharacterVector(FrenchUDHR), 0, 0, 2);
}

void setupScreen() {
  tft.setTextSize(currentTextSize);
  tft.fillScreen(currentBackgroundColor);
  tft.setTextColor(currentTextColor);
}

void writeDoubleScrollingLine(std::vector<String> strs1, std::vector<String> strs2, int xPos, int yPos, int size) {
  for (int i = 0; i < strs1.size(); i++) {
    tft.fillScreen(currentBackgroundColor);
    tft.setTextColor(currentTextColor);

    int currentX = xPos;
    std::vector<String> subStrs1 = {strs1.begin() + i, strs1.end()};
    for (const auto& str : subStrs1) {
      currentX += tft.drawString(str, currentX, yPos, size);
    }

    currentX = xPos;
    std::vector<String> subStrs2 = {strs2.begin() + i, strs2.end()};
    for (const auto& str : subStrs2) {
      currentX += tft.drawString(str, currentX, yPos + 10 * size + 5, size);
    }
    delay(WAIT);
  }
}

void writeScrollingLine(std::vector<String> strs, int xPos, int yPos, int size) {
  for (int i = 0; i < strs.size(); i++) {
    tft.fillScreen(currentBackgroundColor);
    tft.setTextColor(currentTextColor);

    int currentX = xPos;
    std::vector<String> subStrs = {strs.begin() + i, strs.end()};
    for (const auto& str : subStrs) {
      currentX += tft.drawString(str, currentX, yPos, size);
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

std::vector<String> getCharacterVector(std::string str) {
  std::vector<String> chars;
  for (int i = 0; i < str.size(); i++) { 
    chars.push_back(String(str[i])); 
  }
  return chars;
}

// https://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
inline uint16_t getRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}
