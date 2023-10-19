const int analogPin = A17; //GPIO IO27pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  float a = analogRead(analogPin);
  int x = (3.3 / 4095.0) * a; 
  Serial.printf("%3d=%.2f[V] \n",a,x);
  delay(10);
}
