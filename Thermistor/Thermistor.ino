/*
 Thermistor
 Date : 2022/01/01
 Author : IE1A 99 K.Murakami
*/
// ピン番号をマクロで定義
#define THER_PIN 15
#define LED_PIN 4
int analogValue = 0; // アナログ値（0~4095）
double temperature = 0; // 温度
// 起動時に一度だけ呼び出されるメソッド


void setup() {
  Serial.begin(115200); // シリアル通信の転送レート（bps）を設定
  // ピンの入出力設定
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // アナログ値取得
  analogValue = analogRead(THER_PIN);
  // アナログ値から温度を求める
  //温度　= 傾き　* 読み取ったアナログ値 -　直線近似の温度
  temperature = 0.0244 * analogValue - 25 ;
  Serial.println(temperature);
  // 温度が 27℃以上の場合
  if (temperature >= 27) {
  digitalWrite(LED_PIN, HIGH); // 点灯
  } else {
  digitalWrite(LED_PIN, LOW); // 消灯
}
 
 delay(100);
}
