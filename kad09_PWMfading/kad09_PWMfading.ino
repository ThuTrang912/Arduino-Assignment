const int pwmPin = 4; //A10でも4でもどちらでも使えるのを試す   
void setup() {   
  Serial.begin(115200); 
  //PWMのセットアップを記述   
  ledcSetup(0, 12800, 8);
  //PWMチャネルとピンの割り当てを記述 
  ledcAttachPin(pwmPin, 0);
} 
void loop() {   
  static uint8_t duty = 0; //アナログ出力のデューティ値   
  static int diff = 1; //増分・減分（使わなくても可）   
  Serial.printf("%3d\n", duty);// デューティの表示 
  /*     
    ここにPWMでチャネル0にLEDの明暗を制御するコードを書く     
    loop()関数が繰り返されるたびにdutyが0～255～0と増減する     
    コードを書く   
  */
  for(; duty < 255 ; duty += diff){
    ledcWrite(0 , duty);
    Serial.printf("%3d\n" , duty);
    delay(10);
  }

  for(; duty > 0 ; duty -= diff){
    ledcWrite(0 , duty);
    Serial.printf("%3d\n" , duty);
    delay(10);
  }

  delay(10); // 10ミリ秒間隔で繰り返し 
} 