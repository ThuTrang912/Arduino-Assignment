const int analogPin = A17; //GPIO IO27pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = analogRead(analogPin);
  Serial.println(a);
  delay(10);
}