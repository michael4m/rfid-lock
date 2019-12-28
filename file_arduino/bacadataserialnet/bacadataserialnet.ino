#include <Ethernet.h>
#include <SPI.h>
#include <SoftwareSerial.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;

char host[] = "192.168.1.101";

long previousMillis = 0;
unsigned long currentMillis = 0;


String rfid, pintu;
String data;
String rcv=""; //Variable in which the server response is recorded.

SoftwareSerial port2(3, 2);
String informasi;
void setup() {


  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); 
  }

    // put your setup code here, to run once:
  Serial.begin(115200);
  port2.begin(115200);

    data = "";

    Serial.println("GAS");
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available() > 0){
    
    informasi = Serial.readStringUntil("\n");
    Serial.print("INFO :" +informasi );
    getRequest(informasi, "1");
  
  }

  port2.listen();

  while(port2.available() > 0){
    
    informasi = port2.readStringUntil("\n");
    Serial.print("INFO :" +informasi );
    getRequest(informasi, "2");
  }
}

void getRequest(String id, String pintu){

  data = "rfid=" + rfid + "&pintu=" + pintu;

  if (client.connect(host,80)) {
   // REPLACE WITH YOUR SERVER ADDRESS
   Serial.println("Connection established");
    client.println("POST /rfid-lock/api/cek_data.php HTTP/1.1"); 
    client.print("Host: ");
    client.println(host); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data);
     unsigned long timeout = millis();
    while (client.available() == 0) 
    {
      if (millis() - timeout > 15000) //If nothing is available on server for 15 seconds, close the connection.
      { 
        return;
      }
    }
    while(client.available())
    {
      String line = client.readStringUntil('\n') + "\n"; //Read the server response line by line..
      rcv+=line; //And store it in rcv.
    }
    client.stop(); // Close the connection. 
  }else {
    Serial.println("Connection failed");
  }
  Serial.println("Received string: ");
  Serial.println(rcv); //Display the server response.

  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }

  delay(1000); // WAIT THREE MINUTES BEFORE SENDING AGAIN
  
}



