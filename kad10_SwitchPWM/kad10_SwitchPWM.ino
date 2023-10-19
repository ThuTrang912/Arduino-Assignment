const int pwmPin = A10; // GPIO IO4 pin
const int btnPin = 17; // GPIO IO17 pin
bool flag = false; // フラグ初期値false: 押されていない状態
float diff = 0; // 初期の増分値

void setup() {
  // シリアル入出力の準備
  Serial.begin(115200);

  // アナログ(PWM)出力の準備
  ledcSetup(0, 12800, 8);

  // デジタル入力の準備
  ledcAttachPin(pwmPin, 0);
  pinMode(btnPin, INPUT);
}

void loop() {
  int b = digitalRead(btnPin);

  if (b == HIGH && !flag) {
    // Tăng giá trị diff lên 0.25 cho mỗi lần nhấn nút
    diff += 0.25;

    if (diff > 1.0) {
      diff = 0.0; // Đặt lại giá trị diff nếu đã vượt quá 1
    }

    int duty = static_cast<int>(255 * diff); // Tính giá trị duty

    ledcWrite(0, duty);
    Serial.printf("duty=%3d\n", duty);

    flag = true;
  }

  if (b == LOW) {
    flag = false;
  }

  delay(10);
}
