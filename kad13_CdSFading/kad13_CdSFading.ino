const int analogPin = A17;  // CdSセンサーのアナログ入力ピン
const int blueLedPin = 4;   // 青色LEDの制御ピン

void setup() {
  Serial.begin(115200);
  pinMode(blueLedPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(analogPin);

  // アナログ入力値を0から255にマップし、デューティ比を計算
  int dutyCycle = map(sensorValue, 0, 4095, 255, 0);

  // 青色LEDをデューティ比で点灯
  analogWrite(blueLedPin, dutyCycle);

  // シリアルモニタにアナログ入力値とデューティ比を出力
  Serial.printf("%d, %d\n", sensorValue, dutyCycle);

  delay(10);
}
