#include <WiFi.h>


//接続先のSSIDとパスワード学内CampusIOT
const char ssid[] = "CampusIoT-WiFi";
const char passwd[] = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Wifi接続シーケンス
  WiFi.begin(ssid, passwd);
  Serial.print("Wifi connecting...");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.print(" connected. ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:

}
