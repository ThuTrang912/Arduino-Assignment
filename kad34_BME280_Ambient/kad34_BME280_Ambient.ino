#include <WiFi.h>
#include "Ambient.h"
#include "ESP32_BME280_SPI.h"

const char* ssid = "CampusIoT-WiFi";
const char* password = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

unsigned int channelId = 71751;
const char* writeKey = "9abff23f7bd0173b";

WiFiClient client;
Ambient ambient;

const uint8_t SCLK_bme280 = 14;
const uint8_t MOSI_bme280 =13; //Master Output Slave Input ESP32=Master,BME280=slave 
const uint8_t MISO_bme280 =12; //Master Input Slave Output
const uint8_t CS_bme280 = 26; //CS pin

ESP32_BME280_SPI bme280spi(SCLK_bme280, MOSI_bme280, MISO_bme280, CS_bme280, 10000000);

int count = 0;

void setup(){
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor

   WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  ambient.begin(channelId, writeKey, &client);

  uint8_t t_sb = 5; //stanby 1000ms
  uint8_t filter = 0; //filter O = off
  uint8_t osrs_t = 4; //OverSampling Temperature x4
  uint8_t osrs_p = 4; //OverSampling Pressure x4
  uint8_t osrs_h = 4; //OverSampling Humidity x4
  uint8_t Mode = 3; //Normal mode
 
  bme280spi.ESP32_BME280_SPI_Init(t_sb, filter, osrs_t, osrs_p, osrs_h, Mode);
  delay(1000);
}

void loop(){

  int delayTime = 5000 * (count++);
  // bme_get();
  delay(delayTime);

  //ここからBME280 kad33のbme_get()を使わず温度・湿度・大気圧の変数をfloat型でセット
  float temperature = bme280spi.Read_Temperature();
  float humidity = bme280spi.Read_Humidity();
  float pressure = bme280spi.Read_Pressure();

  //BME280の温度・湿度・大気圧の値をd4,d5,d6にセット
  ambient.set(4,temperature);
  ambient.set(5,humidity);
  ambient.set(6,pressure);

  ambient.send();

  //Ambientクラウドに一斉送信

  //BME280の温度・湿度・大気圧の値をシリアルモニタに表示
  Serial.printf("温度 = %.1f [°C]\n", temperature);
  Serial.printf("湿度 = %.1f [%%]\n", humidity);     //%は半角で表示
  Serial.printf("大気圧 = %.1f [hPa]\n", pressure);

}

//************** BME280 測定 *************************
void bme_get(){ 
  byte temperature = (byte)round(bme280spi.Read_Temperature());
  byte humidity = (byte)round(bme280spi.Read_Humidity());
  uint16_t pressure = (uint16_t)round(bme280spi.Read_Pressure());

  char temp_c[10], hum_c[10], pres_c[10];
  sprintf(temp_c, "%2d ℃", temperature);
  sprintf(hum_c, "%2d ％", humidity);
  sprintf(pres_c, "%4d hPa", pressure);

  Serial.println("-----------------------");
  Serial.print("Temperature = "); Serial.println(temp_c);
  Serial.print("Humidity = "); Serial.println(hum_c);
  Serial.print("Pressure = "); Serial.println(pres_c);
  Serial.println("-----------------------");
  Serial.flush();
}
