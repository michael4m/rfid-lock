#include <SoftwareSerial.h>

SoftwareSerial port2(3, 2);
String informasi;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
port2.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available() > 0){
    
    informasi = Serial.readStringUntil("\n");
    Serial.print("INFO :" +informasi );
  
  }

  port2.listen();

  while(port2.available() > 0){
    
    informasi = port2.readStringUntil("\n");
    Serial.print("INFO :" +informasi );
  
  }
}



