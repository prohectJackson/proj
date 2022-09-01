#include <Servo.h>
const int SERVO = 10;
Servo servo;
const int se =A0;
void setup() {
  Serial.begin(9600);
  servo.attach(SERVO);
  servo.write(0);
  delay(1000);
}

void loop() {
  int sv=analogRead(se);
  Serial.println(sv);
  int a=sv;
  if(a <100){
    
  servo.write(0);
  delay(1000);
  }
  else{
    
  servo.write(150);
  delay(1000);
  }
}
