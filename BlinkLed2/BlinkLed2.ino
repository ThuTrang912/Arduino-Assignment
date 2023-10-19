/*
  Blink
  Date : 2022/06/21
  Athor : SK1A chan
*/

int LED1 = 25; //LEDのビン番号
int LED2 = 26; //LEDのビン番号
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200); //シリアル通信の転送レート(bps)の設定
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);//LEDのビンをデジタル出力に設定
  pinMode(LED2, OUTPUT);//LEDのビンをデジタル出力に設定
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("点灯"); //シリアルモニタに出力
  delay(1000);                       // wait for a second
  
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("消灯"); //シリアルモニタに出力
  delay(1000);                       // wait for a second

  digitalWrite(LED2, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("点灯"); //シリアルモニタに出力
  delay(1000);                       // wait for a second
  
  digitalWrite(LED2, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("消灯"); //シリアルモニタに出力
  delay(1000);                       // wait for a second
}
