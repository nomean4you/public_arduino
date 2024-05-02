//ESP32_ILI9341_upbit_ticker_info_system.ino

#include <WebServer.h> // 웹 서버 관련 헤더 파일 참조

#include "WifiConfig.h"
#include "TickerNames.h"
#include "TickerInfo.h"
#include "WebServerConfig.h" // 웹 서버 설정을 위한 헤더 파일 참조
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

// Define ILI9341 pin numbers
#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 4
#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_CLK 18

// Initialize Adafruit_ILI9341
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// 전역 변수 선언
unsigned long lastUpdateTime = 0; // 마지막 업데이트 시간을 추적
const unsigned long updateInterval = 1500; // 정보 갱신 간격 (1.5초)
std::vector<String> tickers; // 선택된 티커 리스트 저장
int currentTickerIndex = 0; // 현재 표시 중인 티커 인덱스
String currentTicker = ""; // 현재 티커
bool isTickerSelected = false; // 사용자가 티커를 선택했는지 여부를 추적
extern String selectedInfo; // 웹서버에서 선택된 정보 저장



// Web Server on port 80
WebServer server(80);

// Price formatting function
String formatPrice(double price) {
  bool isSmallAmount = price < 1000;
  String priceStr = String(isSmallAmount ? price : round(price), isSmallAmount ? 2 : 0);

  int dotIndex = priceStr.indexOf('.');
  if (dotIndex == -1) {
    dotIndex = priceStr.length();
  }

  for (int i = dotIndex - 3; i > 0; i -= 3) {
    priceStr = priceStr.substring(0, i) + ',' + priceStr.substring(i);
  }

  return priceStr + " KRW";
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  // WiFi 설정 로드 및 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // 디스플레이 설정
  tft.begin();
  tft.setRotation(1); // 화면을 가로 방향으로 설정
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_GREENYELLOW);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Please connect to the server!");
  
  // IP 주소 출력
  tft.setCursor(0, 50);
  tft.println("IP: " + WiFi.localIP().toString());

  // UPBIT
  tft.setCursor(0, 80);
  tft.println("UPBIT TICKER INFO.");

  // 웹 서버 설정 및 시작
  setupWebServer(); // 웹 서버 설정 함수 호출
}

void fetchAndDisplayTickerInfo(const String& ticker) {
  HTTPClient http;  // HTTPClient 객체 생성
  String url = "https://api.upbit.com/v1/ticker?markets=KRW-" + ticker;
  http.begin(url);  // URL로 HTTP 연결 시작
  int httpCode = http.GET();  // HTTP GET 요청

  if (httpCode == 200) {  // 요청이 성공했다면
    String response = http.getString();  // 응답을 문자열로 가져옴
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);  // JSON 파싱
    float tradePrice = doc[0]["trade_price"].as<float>();  // 가격 정보 추출
    String formattedPrice = formatPrice(tradePrice);  // 가격 형식화

    tft.fillScreen(ILI9341_BLACK);  // 배경색 설정

    tft.setTextColor(ILI9341_GREEN); // 텍스트 색상을 그린으로 설정
    tft.setTextSize(2); // 텍스트 크기 설정
    tft.setCursor(0, 10);
    tft.println("Ticker: " + ticker);  // 티커 출력

    tft.setTextColor(ILI9341_YELLOW); // 텍스트 색상을 노란색으로 설정
    tft.setTextSize(2); // 텍스트 크기 설정
    tft.setCursor(0, 30); // 커서 위치 조정
    tft.println("Price: " + formattedPrice);  // 형식화된 가격 출력

    // 선택된 추가 정보 표시
    int cursorY = 50; // 다음 표시 위치
    tft.setTextColor(ILI9341_MAGENTA); // 텍스트 색상을 하늘색으로 설정
    tft.setTextSize(2);
    
    if (selectedInfo.indexOf("opening_price") != -1 && doc[0]["opening_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Open: " + formatPrice(doc[0]["opening_price"].as<float>()));
      cursorY += 20;
    }
    if (selectedInfo.indexOf("high_price") != -1 && doc[0]["high_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("High: " + formatPrice(doc[0]["high_price"].as<float>()));
      cursorY += 20;
    }
    if (selectedInfo.indexOf("low_price") != -1 && doc[0]["low_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Low: " + formatPrice(doc[0]["low_price"].as<float>()));
      cursorY += 20;
    }
    
    if (selectedInfo.indexOf("trade_price") != -1 && doc[0]["trade_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Trade: " + formatPrice(doc[0]["trade_price"].as<float>()));
      cursorY += 20;
    }
    if (selectedInfo.indexOf("prev_closing_price") != -1 && doc[0]["prev_closing_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Pre Close: " + formatPrice(doc[0]["prev_closing_price"].as<float>()));
      cursorY += 20;
    }
    if (selectedInfo.indexOf("change") != -1 && doc[0]["change"] != nullptr) {
      String change = doc[0]["change"].as<String>();
      tft.setCursor(0, cursorY);

      if (change == "FALL") {
        tft.setTextColor(ILI9341_BLUE); // 파란색으로 설정
      } else if (change == "RISE") {
        tft.setTextColor(ILI9341_RED); // 빨간색으로 설정
      } else if (change == "EVEN") {
        tft.setTextColor(ILI9341_CYAN); // 시안색으로 설정
      }

      tft.setTextSize(2);
      tft.println("Change: " + change);  // 문자열 출력
      cursorY += 20;
    }
    
    tft.setTextColor(ILI9341_WHITE); // 텍스트 색상을 하얀색으로 설정
    tft.setTextSize(1);

    
    if (selectedInfo.indexOf("signed_change_price") != -1 && doc[0]["signed_change_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Sign. Cha. Price: " + formatPrice(doc[0]["signed_change_price"].as<float>()));
      cursorY += 10;
    }
    if (selectedInfo.indexOf("signed_change_rate") != -1 && doc[0]["signed_change_rate"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Sign. Cha. Rate: " + String(doc[0]["signed_change_rate"].as<float>()) + "%");
      cursorY += 10;
    }
    if (selectedInfo.indexOf("acc_trade_price") != -1 && doc[0]["acc_trade_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Acc. Trade Price: " + formatPrice(doc[0]["acc_trade_price"].as<float>()));
      cursorY += 10;
    }
    if (selectedInfo.indexOf("acc_trade_price_24h") != -1 && doc[0]["acc_trade_price_24h"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Acc. Trade Price 24h: " + formatPrice(doc[0]["acc_trade_price_24h"].as<float>()));
      cursorY += 10;
    }
    if (selectedInfo.indexOf("acc_trade_volume") != -1 && doc[0]["acc_trade_volume"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Acc. Trade Volume: " + String(doc[0]["acc_trade_volume"].as<float>()));
      cursorY += 10;
    }
    if (selectedInfo.indexOf("acc_trade_volume_24h") != -1 && doc[0]["acc_trade_volume_24h"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Acc. Trade Volume 24h: " + String(doc[0]["acc_trade_volume_24h"].as<float>()));
      cursorY += 10;
    }
    if (selectedInfo.indexOf("highest_52_week_price") != -1 && doc[0]["highest_52_week_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Highest 52 Week Price: " + formatPrice(doc[0]["highest_52_week_price"].as<float>()));
      cursorY += 10;
    }
    if (selectedInfo.indexOf("highest_52_week_date") != -1 && doc[0]["highest_52_week_date"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Highest 52 Week Date: " + String(doc[0]["highest_52_week_date"].as<const char*>()));
      cursorY += 20;
    }
    if (selectedInfo.indexOf("lowest_52_week_price") != -1 && doc[0]["lowest_52_week_price"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Lowest 52 Week Price: " + formatPrice(doc[0]["lowest_52_week_price"].as<float>()));
      cursorY += 10;
    }
    if (selectedInfo.indexOf("lowest_52_week_date") != -1 && doc[0]["lowest_52_week_date"] != nullptr) {
      tft.setCursor(0, cursorY);
      tft.println("Lowest 52 Week Date: " + String(doc[0]["lowest_52_week_date"].as<const char*>()));
      cursorY += 10;
    }
  } else {
    Serial.println("Failed to fetch ticker info");
  }
  http.end();  // HTTP 연결 종료
}

void loop() {
  server.handleClient(); // 웹 서버 클라이언트 처리

  if (isTickerSelected && !tickers.empty()) {  // 사용자가 티커를 선택하고 리스트에 티커가 있는 경우에만 정보 갱신
    if (millis() - lastUpdateTime >= updateInterval) {
      lastUpdateTime = millis(); // 마지막 갱신 시간 업데이트
      fetchAndDisplayTickerInfo(tickers[currentTickerIndex]); // 현재 티커 정보 갱신
      currentTickerIndex = (currentTickerIndex + 1) % tickers.size(); // 다음 티커로 인덱스 업데이트
    }
  }
}



