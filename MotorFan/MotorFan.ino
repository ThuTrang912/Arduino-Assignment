/*
  Motor
  Date : 2022/01/01
  Author : IE1A 99 K.Murakami
*/
// ピン番号をマクロで定義
#define THER_PIN 14
#define MOTOR_PIN 13
#define LEDC_CHANNEL_1 1 // LEDC の PWM チャネル 0 から 15
#define LEDC_TIMER_8_BIT 8 // LEDC タイマーの精度 8 ビット
#define LEDC_BASE_FREQ 100 // LEDC のベース周波数 100Hz
//boolean swData; // SW の状態を保持する変数
//boolean swDataOld = false; // 前回の SW の状態を保持する変数（初期値は false）
// モーターの回転速度
int motorSpeed[] = {0, 30, 50, 70};
String speedMsg[] = {"切", "弱", "中", "強"}; // 速度文字
int speedIndex = 0; // 回転速度配列要素番号
int analogValue = 0; // アナログ値（0~4095）
double temperature = 0; // 温度


void setup() {
  Serial.begin(115200); // シリアル通信の転送レート（bps）を設定
  // モーターチャネル設定
  ledcSetup(LEDC_CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  // モーターのチャネルにピンを接続
  ledcAttachPin(MOTOR_PIN, LEDC_CHANNEL_1);


}
double getTemperature() {
  // アナログ値取得
  analogValue = analogRead(THER_PIN);
  // アナログ値から温度を求める
  //温度　= 傾き　* 読み取ったアナログ値 -　直線近似の温度
  return (temperature = 0.0244 * analogValue - 25) ;
}


// メインループメソッド
void loop() {
  double temperature = getTemperature();
  Serial.println(temperature);
  if (temperature > 28) {
    speedIndex = 3;
  } else if (temperature > 25) {
    speedIndex = 2;
  } else if (temperature > 22) {
    speedIndex = 1;
  } else {
    speedIndex = 0;
  }
  ledcWrite(LEDC_CHANNEL_1, motorSpeed[speedIndex]); // モーター回転
  Serial.println(speedMsg[speedIndex]);
  delay(1000); // チャタリング防止
}
