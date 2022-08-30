#include <doxygen.h>
#include <ESP8266.h>

#include "ESP8266.h" // ESP8266 라이브러리 헤더파일 
#include <SoftwareSerial.h>// 소프트웨어 시리얼 
#define SSID        "iptime"        // 공유기 SSID 
#define PASSWORD    "12345678"    // 공유기 비밀번호 
#define HOST_NAME   "13.125.217.249"     // 서버 IP
#define HOST_PORT   (59581)            // 서버 포트 
//#define HOST_PORT   (7000)            // 서버 포트 

SoftwareSerial mySerial(10, 9); /* RX:D10, TX:D9 */
ESP8266 wifi(mySerial); // ESP01 -시리얼 
bool isConnected = false; // 연결 판별 BOOL
const int tpin1=5;
const int epin1=4;
const int tpin2=3;
const int epin2=2;


void setup() {
pinMode(tpin1, OUTPUT);
pinMode(epin1, INPUT);
pinMode(tpin2, OUTPUT);
pinMode(epin2, INPUT);
Serial.begin(9600); // 통신속도  

    Serial.print("setup begin\r\n"); // 출력 
    Serial.print("FW Version:"); // F/W 버전 체크 
    Serial.println(wifi.getVersion().c_str()); // 버전 ESP01 모듈에따라 안나옴 
    if (wifi.setOprToStationSoftAP()) { // WIFI 연결 
        Serial.print("to station + softap ok\r\n");  // WIFI 정상 연결되어야 정상출력 
    } else {
        Serial.print("to station + softap err\r\n"); // 에러 메소드 나오면 SSID / PW 확인 및 RX / TX 선 불량 확인
    }
    if (wifi.joinAP(SSID, PASSWORD)) { //  SSID와 비밀번호로 연결되었으면 
        Serial.print("Join AP success\r\n"); // 연결 성공 출력 
        Serial.print("IP:"); 
        Serial.println( wifi.getLocalIP().c_str());// IP 출력 
    } else {
        Serial.print("Join AP failure\r\n"); //에러 메소드 나오면 SSID / PW 확인 및 RX / TX 선 불량 확인
    }
    pinMode(LED_BUILTIN, OUTPUT); // LED핀 통신 테스트
    if ( isConnected == false){
        while(1){
            if (wifi.createTCP(HOST_NAME, HOST_PORT)) { // 연결될때까지 
                Serial.print("create tcp ok\r\n");  //연결 정상 출력 
                isConnected = true; // 연결 BOOL값 TRUE 
                break;
            } else {
                Serial.print("create tcp err\r\n"); //에러출력 
            }
        }
    } 
    
}

void loop() {
    uint8_t buffer[128] = {0};
    uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
    if(len > 0){ //수신 데이터가 존재한다면 
      Serial.print("Received : [");
      for(uint32_t i = 0; i < len; i++){
        Serial.print((char)buffer[i]); // recv 데이터 시리얼모니터에 출력 
      }
      Serial.print("]\r\n");
      char command = buffer[0]; // 버퍼의 첫자리를 command로 
      if(command == 'A'){  // 커맨드 A 보낼시 String형 서버로 전송 
        char str_msg[] = "ONE";
        sprintf(buffer, "%s", str_msg); // Sprintf 버퍼에 데이터 저장 
        wifi.send(buffer, strlen(buffer)); // 서버로 전송 
      }
    }
    else if(Serial.available()){    
      char data;
      data = Serial.read();
      if(data == 'a') {
        char command = buffer[0]; // 버퍼의 첫자리를 command로 
        char str_msg[] = "1personIn";
        sprintf(buffer, "%s", str_msg); // Sprintf 버퍼에 데이터 저장 
        wifi.send(buffer, strlen(buffer)); // 서버로 전송 
      }
      else if(data == 'b') {
        char command = buffer[0]; // 버퍼의 첫자리를 command로 
        char str_msg[] = "1personOut";
        sprintf(buffer, "%s", str_msg); // Sprintf 버퍼에 데이터 저장 
        wifi.send(buffer, strlen(buffer)); // 서버로 전송 
      }
    }
}
