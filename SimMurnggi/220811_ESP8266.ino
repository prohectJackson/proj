#include <doxygen.h>
#include <ESP8266.h>

#include "ESP8266.h" // ESP8266 라이브러리 헤더파일 
#include <SoftwareSerial.h>// 소프트웨어 시리얼 
#define SSID        "iptime"        // 공유기 SSID 
#define PASSWORD    "12345678"    // 공유기 비밀번호 
#define HOST_NAME   "3.39.152.203"     // 서버 IP
//#define HOST_NAME   "255.255.255.0"     // 서버 IP
//#define HOST_NAME   "10.10.11.254"     // 서버 IP
#define HOST_PORT   (58056)            // 서버 포트 
//#define HOST_PORT   (7000)            // 서버 포트 

SoftwareSerial mySerial(10, 9); /* RX:D10, TX:D9 */
ESP8266 wifi(mySerial); // ESP01 -시리얼 
bool isConnected = false; // 연결 판별 BOOL



void setup() {

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
//    if (wifi.disableMUX()) { // 1개만접속하도록 
//        Serial.print("single ok\r\n");
//    } else {
//        Serial.print("single err\r\n");
//    }
    //Serial.print("setup end\r\n");
    pinMode(LED_BUILTIN, OUTPUT); // LED핀 통신 테스트 
    
}

void loop() {

//      if (wifi.createTCP(HOST_NAME, HOST_PORT)) { // 연결될때까지 
//        Serial.print("create tcp ok\r\n");  //연결 정상 출력 
//        //isConnected = true; // 연결 BOOL값 TRUE 
//        //break;
//      } 
//      else {
//         Serial.print("create tcp err\r\n"); //에러출력 
//      }
            
    // TCP 서버 연결 
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
    
    uint8_t buffer[128] = {0}; // 버퍼 선언 리시브 데이터 
    uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000); // recv 데이터 저장 
    int ledStatus = digitalRead(LED_BUILTIN); // 13번핀 LED 상태  
   Serial.print("a:");
    if(len > 0){ //수신 데이터가 존재한다면 

      Serial.print("Received : [");
      for(uint32_t i = 0; i < len; i++){
        Serial.print((char)buffer[i]); // recv 데이터 시리얼모니터에 출력 
      }
      Serial.print("]\r\n");
      //여기까지는 됨 

      char command = buffer[0]; // 버퍼의 첫자리를 command로 

      if(command == 'A'){  // 커맨드 A 보낼시 String형 서버로 전송 
        //uint8_t buffer1[128] = {0};
        char str_msg[] = "ONE";
        sprintf(buffer, "%s", str_msg); // Sprintf 버퍼에 데이터 저장 
        wifi.send(buffer, strlen(buffer)); // 서버로 전송 
      }
      else if(command == 'B'){ // 커맨드 B 보낼시 Float형 서버로 전송 
        //uint8_t buffer2[128] = {0};
        char temp[20];
        float f = 32.4;
        dtostrf(f, 4, 1, temp);
        sprintf(buffer, "%s", temp);
        wifi.send(buffer, strlen(buffer));
      }
      else if(command == 'C'){ // 커맨드 C 보낼시 int형 서버로 전송 
        int i = 123;
        sprintf(buffer, "%d", i);
        wifi.send(buffer, strlen(buffer));
      }

      else if(command == 'D'){ // 커맨드 D 보낼시 CHAR형 서버로 전송 
        char c = 'P';
        sprintf(buffer, "%c", c);
        wifi.send(buffer, strlen(buffer));
      }

      else if(command == 'E'){ // 커맨드 E 보낼시 LED ON 
        if (ledStatus == LOW){
           digitalWrite(LED_BUILTIN, HIGH);
           sprintf(buffer, "LED is on"); // 출력 내용 버퍼에 저장 
           wifi.send(buffer, strlen(buffer));
        }
        else{
           sprintf(buffer, "LED is already on");
           wifi.send(buffer, strlen(buffer));
        }
      }

      else if(command == 'F'){ // 커맨드 F 보낼시 LED OFF 
        if (ledStatus == HIGH){
          digitalWrite(LED_BUILTIN, LOW);
          sprintf(buffer, "LED is off.");
          wifi.send(buffer, strlen(buffer));
        }
        else{
         sprintf(buffer, "LED is already off.");
         wifi.send(buffer, strlen(buffer));
        }
      }

      else if(command == 'G'){ // 커맨드 G 보낼시 LED 상태 출력 
        if (ledStatus == LOW){
          sprintf(buffer, "LED status: off");
           wifi.send(buffer, strlen(buffer));
         }
        else {
          sprintf(buffer, "LED status: on");
          wifi.send(buffer, strlen(buffer));
        }
      }
      else if (command == 'Q'){
        if (wifi.releaseTCP()) {
            Serial.print("release tcp ok\r\n");
        } else {
            Serial.print("release tcp err\r\n");
        }   
      }
    }

//    if (wifi.releaseTCP()) {
//        Serial.print("release tcp ok\r\n");
//    } else {
//        Serial.print("release tcp err\r\n");
//    }
//    delay(500);
    
     
}
