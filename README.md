# public_arduino
for public Arduino source code!!
Esp32와 망할놈의 ILI9341 스크린을 조합해서 만든 
UPBIT TICKER조회용 소스입니다.
chatgpt 4.0으로 이거 만드느라 4일 개고생했습니다.
기본적으로 받아서 설치해야할 라이브러리는 
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h> 
이런것들은 ARDUION 라이브러리 관리자에서 검색해서 설치하세요.
Adafruit_GFX 이라이브러리는 ZIP파일 받아서 추가하셔야합니다. 

업비트의 API는 기본적으로 로그인하지 않고 토큰없이도 받아 볼수있는 정보입니다.
제가 등록한 API 정보외에 더 추가하고 싶으신분은 추가하세요.

UPBIT API에서 받아볼수 있는 공짜 정보는 아래에 있습니다.

################################################
trade_date (최근 거래 일자, UTC)
trade_time (최근 거래 시각, UTC)
trade_date_kst (최근 거래 일자, KST)
trade_time_kst (최근 거래 시각, KST)
trade_timestamp (최근 거래 일시의 유닉스 타임스탬프)
opening_price (시가)
high_price (고가)
low_price (저가)
trade_price (종가, 현재가)
prev_closing_price (전일 종가, UTC 0시 기준)
change (상태 변화, 예: 상승, 보합, 하락)
change_price (변화액의 절대값)
change_rate (변화율의 절대값)
signed_change_price (부호가 있는 변화액)
signed_change_rate (부호가 있는 변화율)
trade_volume (가장 최근 거래량)
acc_trade_price (누적 거래대금, UTC 0시 기준)
acc_trade_price_24h (24시간 누적 거래대금)
acc_trade_volume (누적 거래량, UTC 0시 기준)
acc_trade_volume_24h (24시간 누적 거래량)
highest_52_week_price (52주 최고가)
highest_52_week_date (52주 최고가 달성일)
lowest_52_week_price (52주 최저가)
lowest_52_week_date (52주 최저가 달성일)
timestamp (타임스탬프) 
##################################################
LCD 스크린에 9개이상의 API정보는 체크하지마세요 
LCD 스크린 밖으로 튀어나갑니다. 글씨가 중복되어 나타날수 있습니다.

2024-05-01 현재기준으로 UPBIT의 91EA의 TICKER 명을 가져왔습니다.
나중에 UPBIT에서 더 추가될수도 퇴출될수도 있으니 유의하세요.

아래 헤더중 WifiConfig.h 는  각자의 WIFI SSID 와 SCREAT NUMBER는
각자 설정하시기 바랍니다.

업로딩을 하면 LCD스크린에 각자의 IP주소가 뜹니다.
거기로 접속하셔서 COIN TICKER를 설정하시고 
가져올 API정보를 체크하신뒤 SUBMIT 버튼 누르면 
LCD 액정에 표시될겁니다.
ILI9341 LCD 스크린이 아닌분은 각자 맞는 LCD 라이브러리를 
다운받아서 치환해서 쓰세요.


초보인 제가 이거 만드느라 꼬박 4일 걸렸습니다.
여러분도 할수 있습니다. 다음에는 웹서버 입력방식이 아닌 터치스크린 입력방식을
도전해보겠습니다.

그럼 즐건 아두이노 되세요 !!
2024.05.01 노동절날  
아두이노 초보 무니나라.


ESP32_ILI9341_Upbit_ticker_Open_Source_V1.1 UPGRADE VERSION
업그레이드 버젼입니다.
API에서 받아오는 정보를 더 추가 했습니다.
특히 변동량 에서 상승/보합/하락 을 색깔별로 나타나게 했습니다.
LCD에선 Change 로 출력됩니다.
52주 신고가/신저가 추가 했습니다.
 
**변경 -- 가격 변동 정보 (Change) 이  코드가 색깔별로 나타납니다.
**추가  API 정보 **
 누적 거래대금 (Acc Trade Price)
 24시간 누적 거래대금 (Acc Trade Price 24h)
 누적 거래량 (Acc Trade Volume)
 24시간 누적 거래량 (Acc Trade Volume 24h)
 52주 신고가 (Highest 52 Week Price)
 52주 신고가 달성일 (Highest 52 Week Date)
 52주 신저가 (Lowest 52 Week Price)
 52주 신저가 달성일 (Lowest 52 Week Date)
2024.05.03
