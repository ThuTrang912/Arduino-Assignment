const int analogPin = A17; // GPIO IO27 pin
const int redLedPin = 16;   // Đỏ
const int blueLedPin = 4;  // Xanh

int darkLevel = 1000;  // Ngưỡng độ tối

void setup() {
  Serial.begin(115200);
  
  ledcSetup(0, 12800, 8);
  ledcAttachPin(blueLedPin, 0);
  pinMode(redLedPin, OUTPUT);
  // pinMode(blueLedPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  
  if (sensorValue < darkLevel) {
    // Khi giá trị từ cảm biến thấp hơn ngưỡng, bật cả hai LED
    ledcWrite(0, 255); // Đèn xanh bật
    digitalWrite(redLedPin, HIGH); // Đèn đỏ bật
  } else {
    // Khi giá trị từ cảm biến cao hơn ngưỡng, tắt cả hai LED
    ledcWrite(0, 0);  // Đèn xanh tắt
    digitalWrite(redLedPin, LOW); // Đèn đỏ tắt
  }
  
  delay(10);
}
