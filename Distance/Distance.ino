/*
 Distance
 Date : 2022/01/01
 Author : IE1A 99 K.Murakami
*/
// ピン番号をマクロで定義
#define TRIG_PIN 16 // トリガー（送信）
#define ECHO_PIN 17 // エコー（受信）
double duration = 0; // 受信までの時間
double distance = 0; // 物との距離
// 起動時に一度だけ呼び出されるメソッド
void setup() {
   Serial.begin(115200); // シリアル通信の転送レート（bps）を設定
 
   // ピンの入出力設定
   pinMode(TRIG_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
 
   // トリガーを LOW に落としておく
   digitalWrite(TRIG_PIN, LOW);
   delay(10); // 落ちきるまで少し待機
}
// 超音波送信メソッド
void sendTrigger() {
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10); // 送信してから一瞬だけ待機
   digitalWrite(TRIG_PIN, LOW);
}
// メインループメソッド
void loop() {
   sendTrigger(); // 超音波送信
 
   duration = pulseIn(ECHO_PIN, HIGH); // 受信した時間を代入
    // 値が 0 より大きい場合（受け取れていたら）
   if (duration > 0) {
     duration /= 2; // 往復の距離を片道に変換
     // 音速を 340m/s として受信時間から距離に変換
     distance = duration * 340 / 10000;
     // シリアルモニタに出力
     Serial.print("距離：");
     Serial.print(distance);
     Serial.println("cm");
  }
 
   delay(1000); // 1 秒待機
}
