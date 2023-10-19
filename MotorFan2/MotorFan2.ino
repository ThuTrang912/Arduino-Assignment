/*
 MotorFan
 Date : 2022/07/19
 Author : Sk1A 04 ブンカシュン
*/
// ピン番号をマクロで定義
#define THER_PIN 14
#define MOTOR_PIN 13
#define LEDC_CHANNEL_1 1 // LEDC の PWM チャネル 0 から 15
#define LEDC_TIMER_8_BIT 8 // LEDC タイマーの精度 8 ビット
#define LEDC_BASE_FREQ 100 // LEDC のベース周波数 100Hz

int analogValue = 0; // アナログ値（0~4095）
double temperature = 0; // 温度
// モーターの回転速度
  int motorSpeed[] = {0, 30, 50, 70}; 
  String speedMsg[] = {"切", "弱", "中", "強"}; // 速度文字
  int speedIndex = 0; // 回転速度配列要素番号

  // 起動時に一度だけ呼び出されるメソッド
  void setup() {
    Serial.begin(115200); // シリアル通信の転送レート（bps）を設定
    // モーターチャネル設定
    ledcSetup(LEDC_CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
    // モーターのチャネルにピンを接続
    ledcAttachPin(MOTOR_PIN, LEDC_CHANNEL_1);
 }

 void melody(int *score, int note, int speedIndex) {
   for (int i = speedIndex; i <= speedIndex ; i++) {
    ledcWrite(LEDC_CHANNEL_1, score[i]); // モーター回転
    delay(1000);
  }
}

  // メインループメソッド
  void loop() {
    // アナログ値取得
    analogValue = analogRead(THER_PIN);
    // 現在の SW の状態を読み取る
    temperature = (  0.0244*analogValue - 25) ;
    Serial.println(temperature);
    if (temperature >= 32) {
      speedIndex = 3;
    }else if (temperature < 32 && temperature >= 28){
      speedIndex = 2;
    }else if (temperature < 28 && temperature >= 25){
      speedIndex = 1;
    }else if (temperature < 25){
      speedIndex = 0;
    }
    melody(motorSpeed, sizeof(motorSpeed) / sizeof(int), speedIndex);
    Serial.println(speedMsg[speedIndex]);
    delay(1000); // チャタリング防止
  }
