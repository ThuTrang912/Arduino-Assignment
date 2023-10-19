/*
  Blink
  Date : 2022/06/21
  Athor : SK1A chan
*/

int LED_BUILTIN = 25; //LEDのビン番号
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200); //シリアル通信の転送レート(bps)の設定
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);//LEDのビンをデジタル出力に設定
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("点灯"); //シリアルモニタに出力
  delay(1000);                       // wait for a second
  
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("消灯"); //シリアルモニタに出力
  delay(1000);                       // wait for a second
}
