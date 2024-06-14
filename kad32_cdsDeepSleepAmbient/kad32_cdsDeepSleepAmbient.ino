#include "esp_sleep.h" 

#include <WiFi.h>
#include "Ambient.h"

const char* ssid = "CampusIoT-WiFi";
const char* password = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

unsigned int channelId = 71751;
const char* writeKey = "9abff23f7bd0173b";

WiFiClient client;
Ambient ambient;

const int cdsPin = A0; //光センサー A0ピン
const int bluePin = 4; //青色LED IO4ピン
const int redPin = 16; //赤色LED IO16ピン

void setup() { 
  // put your setup code here, to run once: 
  Serial.begin(115200); 
  Serial.println("Start"); 
  
  esp_sleep_pd_config (ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF); 
  esp_sleep_pd_config (ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF); 
  esp_sleep_pd_config (ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF); 
  esp_sleep_pd_config (ESP_PD_DOMAIN_MAX, ESP_PD_OPTION_OFF); 
  
  pinMode (redPin, OUTPUT);
  pinMode (bluePin, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(redPin, HIGH);

  ambient.begin(channelId, writeKey, &client);
}

void loop() { 
  // put your main code here, to run repeatedly: 
  delay(1000); 
  double ana = analogRead(cdsPin);
  Serial.print("アナログ入力：");
  Serial.println(ana);
  ambient.set(3,ana);
  ambient.send();
  ledFlash(bluePin, 200); //送信時に青色LED点滅

  esp_sleep_enable_timer_wakeup (10 * 1000 * 1000); // wakeup (restart) after 10sec 
  esp_deep_sleep_start(); 
  
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
