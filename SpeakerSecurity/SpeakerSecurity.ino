/*
 Speaker
 Date : 2022/01/01
 Author : IE1A 99 K.Murakami
*/
// ピン番号をマクロで定義
#define TRIG_PIN 16 // トリガー（送信）
#define ECHO_PIN 17 // エコー（受信）
double duration = 0; // 受信までの時間
double distance = 0; // 物との距離

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
double miss[] = {B4, F5, NONE, F5, F5, E5, NONE, D5, C5, NONE};

// 起動時に一度だけ呼び出されるメソッド
void setup() {
   Serial.begin(115200); // シリアル通信の転送レート（bps）を設定
   
   // ピンの入出力設定
   pinMode(TRIG_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);

 
   // トリガーを LOW に落としておく
   digitalWrite(TRIG_PIN, LOW);
   delay(10); // 落ちきるまで少し待機
   // ピンの入出力設定
   pinMode(SW_PIN, INPUT);
   // スピーカーチャネル設定
   ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
   // スピーカーのチャネルにピンを接続
   ledcAttachPin(SPKR_PIN, LEDC_CHANNEL_0);
   // setup 完了後、マリオのテーマを奏でる(八分音符)
   Serial.println("プログラム開始");
}

// 超音波送信メソッド
void sendTrigger() {
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10); // 送信してから一瞬だけ待機
   digitalWrite(TRIG_PIN, LOW);
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
    sendTrigger(); // 超音波送信
    duration = pulseIn(ECHO_PIN, HIGH); // 受信した時間を代入
    // 値が 0 より大きい場合（受け取れていたら）
    
   if (duration > 0) {
      duration /= 2; // 往復の距離を片道に変換
      // 音速を 340m/s として受信時間から距離に変換
      distance = duration * 340 / 10000;
      // シリアルモニタに出力
      Serial.print("距離1：");
      Serial.print(distance);
      Serial.println("cm");
      
      while(distance < 5){
          melody(miss, sizeof(miss) / sizeof(double), WHOLE_NOTE / 8);
          while(true){
                    sendTrigger(); // 超音波送信
                    duration = pulseIn(ECHO_PIN, HIGH); // 受信した時間を代入
                    // 値が 0 より大きい場合（受け取れていたら）
                    if(duration > 0) {
                        duration /= 2; // 往復の距離を片道に変換
                        // 音速を 340m/s として受信時間から距離に変換
                        distance = duration * 340 / 10000;
                         // シリアルモニタに出力
                        Serial.print("距離2：");
                        Serial.print(distance);
                        Serial.println("cm");
                        // 現在の各 SW の状態を読み取る
                        swData = digitalRead(SW_PIN);
                        // 現在の SW の状態が、前回の SW の状態と違う場合
                        if (swData != swDataOld) {
                            if (swData) {
                               Serial.println("押した");
                                ledcWriteTone(LEDC_CHANNEL_0, NONE);
                                break;
                            }else{
                                Serial.println("離した");
                                if(distance >= 5){
                                    melody(mario, sizeof(mario) / sizeof(double), WHOLE_NOTE / 8);
                                }else{
                                    melody(miss, sizeof(miss) / sizeof(double), WHOLE_NOTE / 8);
                                }
                            }
          
                         }
                         // 次回の為に現在の SW の状態を保存する
                          swDataOld = swData;
                      }
              }
            

      delay(10); // チャタリング防止
    }

   }
}

        
