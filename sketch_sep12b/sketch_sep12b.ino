#include <M5StickC.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.IMU.Init();  // Sử dụng M5.IMU thay vì M5.MPU6886.Init()
  M5.Lcd.setTextColor(WHITE); // Font color
  M5.Lcd.setTextSize(2); // Size
  M5.Lcd.fillScreen(BLACK);  // Clean Screen
  M5.Lcd.print("y: yyyyyy ");
}
void loop() {
  // put your main code here, to run repeatedly:
  M5.Lcd.print("y: yyyyyy ");
}
