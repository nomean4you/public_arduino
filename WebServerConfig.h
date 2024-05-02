// WebServerConfig.h

#ifndef WEB_SERVER_CONFIG_H
#define WEB_SERVER_CONFIG_H

#include <WebServer.h>
#include "TickerNames.h"  // 티커 정보 접근을 위해 포함
#include "TickerInfo.h"   // 필요한 경우 티커 정보를 표시하는 함수를 포함

extern WebServer server; // 외부에서 정의된 서버 인스턴스
extern bool isTickerSelected; // 사용자가 티커를 선택했는지 여부를 추적하는 전역 변수
extern String currentTicker; // 현재 선택된 티커를 저장하는 전역 변수
extern std::vector<String> tickers; // 선택된 티커 리스트 저장
String selectedInfo; // 선택한 정보를 저장하는 전역 변수
extern int currentTickerIndex; // 현재 표시 중인 티커 인덱스


void setupWebServer() {
    // Root path
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", "<h1>Welcome to the Crypto Ticker Server!</h1><p><a href='/setup'>Go to /setup to select tickers and information.</a></p>");
    });

    
    // Ticker setup path
    server.on("/setup", HTTP_GET, []() {
        String html = "<html><head><title>Ticker Setup</title><meta charset='utf-8'></head><body>";
        html += "<h1>Select Tickers and Information</h1><form action='/submit' method='GET'>";

        // Adding all groups
        const TickerInfo* groups[] = {group1, group2, group3, group4};
        const size_t groupSizes[] = {sizeof(group1) / sizeof(TickerInfo), sizeof(group2) / sizeof(TickerInfo), sizeof(group3) / sizeof(TickerInfo), sizeof(group4) / sizeof(TickerInfo)};
        for (int group = 0; group < 4; group++) {
            html += "<div style='float: left; margin-right: 20px;'><strong>Group " + String(group + 1) + "</strong><br>";
            for (int i = 0; i < groupSizes[group]; i++) {
                html += "<input type='checkbox' name='ticker' value='" + String(groups[group][i].symbol) + "'> " + String(groups[group][i].koreanName) + " (" + String(groups[group][i].englishName) + ")<br>";
            }
            html += "</div>";
        }

        html += "<div style='clear: both;'><h2>Select Additional Information:</h2>";
        html += "<input type='checkbox' name='info' value='opening_price'> 시작 가격 (Opening Price)<br>";
        html += "<input type='checkbox' name='info' value='high_price'> 최고 가격 (High Price)<br>";
        html += "<input type='checkbox' name='info' value='low_price'> 최저 가격 (Low Price)<br>";
        html += "<input type='checkbox' name='info' value='trade_price'> 최근 거래 가격 (Trade Price)<br>";
        html += "<input type='checkbox' name='info' value='prev_closing_price'> 이전 종가 (Prev Closing Price)<br>";
        html += "<input type='checkbox' name='info' value='change'> 가격 변동 정보 (Change)<br>";
        /*html += "<input type='checkbox' name='info' value='change_price'> 가격 변동량 (Change Price)<br>";
        html += "<input type='checkbox' name='info' value='change_rate'> 가격 변동률 (Change Rate)<br>";*/
        html += "<input type='checkbox' name='info' value='signed_change_price'> 부호가 있는 가격 변동량 (Signed Change Price)<br>";
        html += "<input type='checkbox' name='info' value='signed_change_rate'> 부호가 있는 가격 변동률 (Signed Change Rate)<br>";
        html += "<input type='checkbox' name='info' value='trade_volume'> 최근 거래량 (Trade Volume)<br>";
        html += "<input type='checkbox' name='info' value='acc_trade_price'> 누적 거래대금 (Acc Trade Price)<br>";
        html += "<input type='checkbox' name='info' value='acc_trade_price_24h'> 24시간 누적 거래대금 (Acc Trade Price 24h)<br>";
        html += "<input type='checkbox' name='info' value='acc_trade_volume'> 누적 거래량 (Acc Trade Volume)<br>";
        html += "<input type='checkbox' name='info' value='acc_trade_volume_24h'> 24시간 누적 거래량 (Acc Trade Volume 24h)<br>";
        html += "<input type='checkbox' name='info' value='highest_52_week_price'> 52주 신고가 (Highest 52 Week Price)<br>";
        html += "<input type='checkbox' name='info' value='highest_52_week_date'> 52주 신고가 달성일 (Highest 52 Week Date)<br>";
        html += "<input type='checkbox' name='info' value='lowest_52_week_price'> 52주 신저가 (Lowest 52 Week Price)<br>";
        html += "<input type='checkbox' name='info' value='lowest_52_week_date'> 52주 신저가 달성일 (Lowest 52 Week Date)<br>";
        //html += "<input type='checkbox' name='info' value='bid_ask_ratio'> 매수/매도 잔량 비율 (Bid/Ask Ratio)<br>";
        //html += "<input type='checkbox' name='info' value='trade_intensity'> 1분당 체결강도 (One Minute Trade Intensity)<br>";
        html += "<input type='submit' value='Submit' style='margin-top: 20px;'></form>";
        html += "</body></html>";
        server.send(200, "text/html", html);
    });

    // Ticker submit path
    server.on("/submit", HTTP_GET, []() {
    tickers.clear(); // 기존 티커 목록을 초기화
    selectedInfo = ""; // 선택된 정보 초기화
    String tickersSelected = "";
    for (int i = 0; i < server.args(); i++) {
        if (server.argName(i) == "ticker") {
            tickersSelected += server.arg(i) + ",";
            tickers.push_back(server.arg(i)); // 티커를 배열에 추가
        }
        if (server.argName(i) == "info") {
            if (selectedInfo.length() > 0) selectedInfo += ",";
            selectedInfo += server.arg(i);
        }
    }
    tickersSelected.remove(tickersSelected.length() - 1); // 마지막 콤마 제거

    isTickerSelected = true; // 티커 선택 상태 업데이트
    currentTickerIndex = 0; // 티커 인덱스 리셋

    server.send(200, "text/html", "<p>Tickers selected: " + tickersSelected + "</p><a href='/setup'>Modify Selection</a>");
});

    server.begin();
    Serial.println("HTTP server started");
}

#endif



