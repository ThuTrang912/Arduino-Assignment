#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_13_BIT 13
#define LEDC_BASE_FREQ 5000
const int buzPin = 23;
const int btnPin = 17;
int noteDuration = 1000 / 8;

void setup() {
  Serial.begin(115200); // シリアル通信を初期化
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(buzPin, LEDC_CHANNEL_0);
  pinMode(btnPin, INPUT);
}

void loop() {
  if (digitalRead(btnPin) == HIGH) {
    // 低い周波数から高い周波数へ
    for (int i = 25; i < 120; i++) {
      ledcWriteTone(LEDC_CHANNEL_0, 20 * i);
      delay(noteDuration);
      Serial.print(20 * i);
      Serial.print(" ");
    }
    Serial.println(); // 改行

    // 高い周波数から低い周波数へ
    for (int i = 120; i >= 25; i--) {
      ledcWriteTone(LEDC_CHANNEL_0, 20 * i);
      delay(noteDuration);
      Serial.print(20 * i);
      Serial.print(" ");
    }
    Serial.println(); // 改行

    // 周波数を0に設定して音を停止
    ledcWriteTone(LEDC_CHANNEL_0, 0);
  }
}
