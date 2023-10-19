
void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  pinMode(17, INPUT);
}

// the loop function runs over and over again forever
void loop() {

  int b = digitalRead(17);
  if(b == 1){
    tan();
    chou();
    tan();
  }else{
    digitalWrite(16, LOW);
  }
  delay(10);
}

void tan(){
  for(int i = 0 ; i < 3 ; i++){
    digitalWrite(16, HIGH);  // turn the LED on (HIGH is the voltage level)
    Serial.print(".");     
    delay(200);
    digitalWrite(16, LOW);   // turn the LED off by making the voltage LOW
    delay(200);
  } 
}

void chou(){
  for(int i = 0 ; i < 3 ; i++){
    digitalWrite(16, HIGH);  // turn the LED on (HIGH is the voltage level)
    Serial.print("-");     
    delay(600);
    digitalWrite(16, LOW);   // turn the LED off by making the voltage LOW
    delay(200);
  } 
}
