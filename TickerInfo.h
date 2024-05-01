// TickerInfo.h 수정
#ifndef TICKER_INFO_H
#define TICKER_INFO_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <WebServer.h>

#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 4

extern Adafruit_ILI9341 tft;
extern WebServer server;

void setupDisplay();
void setupWebServer();
void displayTickerInfo(const char* ticker, const char* price);
void fetchAndDisplayTickerInfo(const String& ticker);  // 수정: 인자 추가

#endif

