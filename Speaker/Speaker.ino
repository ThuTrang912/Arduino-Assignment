/*
 Speaker
 Date : 2022/01/01
 Author : IE1A 99 K.Murakami
*/
// ピン番号をマクロで定義
#define SW_PIN 14
#define SPKR_PIN 27
// スピーカーの PWM 出力関連を定義
#define LEDC_CHANNEL_0 0 // LEDC の PWM チャネル 0 から 15
#define LEDC_TIMER_13_BIT 13 // LEDC タイマーの精度 13 ビット
#define LEDC_BASE_FREQ 5000 // LEDC のベース周波数 5000Hz
// 使用する音の周波数を定義
#define C4 261.626 // ド
#define D4 293.665 // レ
#define E4 329.628 // ミ
#define F4 349.228 // ファ
#define G4 391.995 // ソ
#define A4 440.000 // ラ
#define B4 493.883 // シ
#define C5 523.251 // ド
#define D5 587.330 // レ
#define E5 659.255 // ミ
#define F5 698.456 // ファ
#define G5 783.991 // ソ
#define A5 880.000 // ラ
#define B5 987.767 // シ
#define C6 1046.502 // ド
#define D6 1174.659 // レ
#define E6 1318.510 // ミ
#define F6 1396.913 // ファ
#define G6 1567.982 // ソ
#define NONE 0 // 無音
#define WHOLE_NOTE 1000 // 全音符(1 秒)
boolean swData; // SW の状態を保持する変数
boolean swDataOld = false; // 前回の SW の状態を保持する変数（初期値は false）
// マリオテーマ楽譜
double mario[] = {E5, E5, NONE, E5, NONE, C5, E5, NONE, G5, NONE, NONE, NONE, G4};
// 起動時に一度だけ呼び出されるメソッド
void setup() {
   Serial.begin(115200); // シリアル通信の転送レート（bps）を設定
   // ピンの入出力設定
   pinMode(SW_PIN, INPUT);
   // スピーカーチャネル設定
   ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
   // スピーカーのチャネルにピンを接続
   ledcAttachPin(SPKR_PIN, LEDC_CHANNEL_0);
   // setup 完了後、マリオのテーマを奏でる(八分音符)
   melody(mario, sizeof(mario) / sizeof(double), WHOLE_NOTE / 8);
   Serial.println("プログラム開始");
}
// 演奏メソッド（楽譜, 楽譜の要素数, 音符の長さ）
  void melody(double *score, int len, int note) {
   for (int i = 0; i < len; i++) {
    ledcWriteTone(LEDC_CHANNEL_0, score[i]);
    delay(note);
  }
  ledcWriteTone(LEDC_CHANNEL_0, NONE); //消音
}
// メインループメソッド
void loop() {
   // 現在の各 SW の状態を読み取る
   swData = digitalRead(SW_PIN);
   // 現在の SW の状態が、前回の SW の状態と違う場合
   if (swData != swDataOld) {
      if (swData) {
          Serial.println("押した");
 
          // コイン音を鳴らす
          ledcWriteTone(LEDC_CHANNEL_0, B5);
          delay(WHOLE_NOTE / 8); // 八分音符
          ledcWriteTone(LEDC_CHANNEL_0, E6);
          delay(WHOLE_NOTE / 4); // 四分音符
          ledcWriteTone(LEDC_CHANNEL_0, NONE);
      }else{
          Serial.println("離した");
      }
    }
    // 次回の為に現在の SW の状態を保存する
     swDataOld = swData;
     delay(10); // チャタリング防止
 }
 
