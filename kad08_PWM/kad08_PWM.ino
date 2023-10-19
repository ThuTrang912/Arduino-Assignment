const int pwmPin = A10; //GPIO IO4Pin
void setup() {
  // put your setup code here, to run once:
  ledcSetup(0,12800,8);
  ledcAttachPin(pwmPin,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  ledcWrite(0,255);
  delay(1000);
  ledcWrite(0,127);
  delay(1000);
  ledcWrite(0,0);
  delay(1000);
}
