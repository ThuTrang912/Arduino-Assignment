/*
 Motor
 Date : 2022/01/01
 Author : IE1A 99 K.Murakami
*/
// ピン番号をマクロで定義
#define SW_PIN 14
#define MOTOR_PIN 13
#define LEDC_CHANNEL_1 1 // LEDC の PWM チャネル 0 から 15
#define LEDC_TIMER_8_BIT 8 // LEDC タイマーの精度 8 ビット
#define LEDC_BASE_FREQ 100 // LEDC のベース周波数 100Hz
boolean swData; // SW の状態を保持する変数
boolean swDataOld = false; // 前回の SW の状態を保持する変数（初期値は false）
// モーターの回転速度
int motorSpeed[] = {0, 30, 50, 70};
String speedMsg[] = {"切", "弱", "中", "強"}; // 速度文字
int speedIndex = 0; // 回転速度配列要素番号

void setup() {
   Serial.begin(115200); // シリアル通信の転送レート（bps）を設定
 
   // ピンの入出力設定
   pinMode(SW_PIN, INPUT);
 
   // モーターチャネル設定
   ledcSetup(LEDC_CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
   // モーターのチャネルにピンを接続
   ledcAttachPin(MOTOR_PIN, LEDC_CHANNEL_1);
}

// メインループメソッド
void loop() {
   // 現在の SW の状態を読み取る
   swData = digitalRead(SW_PIN);
   // 現在の SW の状態が、前回の SW の状態と違う場合
   if (swData != swDataOld) {
      // 現在の SW の状態が ON(true)の場合
      if (swData) {
          // 要素番号を次へ更新（0→1→2→3→0）
          speedIndex = (speedIndex + 1) % (sizeof(motorSpeed)/sizeof(int));
          // if(speedIndex > 3){
          //     speedIndex = 0;  
          //}
           ledcWrite(LEDC_CHANNEL_1, motorSpeed[speedIndex]); // モーター回転
           Serial.println(speedMsg[speedIndex]);
      }
   }
    
   // 次回の為に現在の SW の状態を保存する
   swDataOld = swData;
   delay(10); // チャタリング防止
}
