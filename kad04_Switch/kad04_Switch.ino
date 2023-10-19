void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(17, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int b = digitalRead(17);
  if(b == 1){
    Serial.println("押された");
  }else{
    Serial.println("");
  }
  delay(10);
}
