#include <WiFi.h>
#include "Ambient.h"

const char* ssid = "CampusIoT-WiFi";
const char* password = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

unsigned int channelId = 71751;
const char* writeKey = "9abff23f7bd0173b";

WiFiClient client;
Ambient ambient;

const int volumePin = A3;// ボリューム (可変抵抗) A3ピン 
const int bluePin = 4; //　青色LED IO4 ビン   

void setup(){
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    ambient.begin(channelId, writeKey, &client);

    pinMode (bluePin, OUTPUT);
}

void loop(){
	int rand;
	rand = random(1000);
  ambient.set(1, rand);                // データーがint型かfloat型であれば、直接セットすることができます。
  Serial.println(rand);

  int ana = analogRead (volumePin); // ボリュームのアナログ入力計測
  ledFlash (bluePin, 200); //計測を確認するため青色LED点滅 
  double v = map (ana, 0,4095, 0,3300)/1E3; //1000 Cmvb57 
  ambient.set(2, v);                // データーがint型かfloat型であれば、直接セットすることができます。


  ambient.send();
  //double v = 3.3 * ana / 4095; //この比例配分の式と同じ 
  Serial.printf("アナログ入力:%d, 単純変換値:%f[V]\n", ana, v); 

  delay(5000);
}

/**
* LEDを指定したミリ秒分点滅させる
* @param ledPin LEDの接続しているGPIOビン番号
* @param delayTime　LEDを点灯させておく時間 
*/
void ledFlash(int ledPin, int delayTime){
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
}

