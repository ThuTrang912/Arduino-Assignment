

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(16, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  tan();
  chou();
  tan();
             
  Serial.println("");
  delay(1000);                  // wait for a second
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
