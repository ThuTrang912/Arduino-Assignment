const int volumePin = A3;// ボリューム (可変抵抗) A3ピン 
const int bluePin = 4; //　青色LED IO4 ビン   
void setup() { 
  Serial.begin(115200); 
  pinMode (bluePin, OUTPUT);

} 

void loop() { 
  int ana = analogRead (volumePin); // ボリュームのアナログ入力計測 
  ledFlash (bluePin, 200); //計測を確認するため青色LED点滅 
  
  //アナログ入力の0-4095の値を0-3300 [mv]にmap (比例配分) する 
  double v = map (ana, 0,4095, 0,3300)/1E3; //1000 Cmvb57 
  //double v = 3.3 * ana / 4095; //この比例配分の式と同じ 
  Serial.printf("アナログ入力:%d, 単純変換値:%f[V]\n", ana, v); 
  
  delay (5000); //5秒おきに実行
}

/**
* LEDを指定したミリ秒分点滅させる
* @param ledPin LEDの接続しているGPIOビン番号
* @param delayTime　LEDを点灯させておく時間 
*/
void ledFlash(int ledPin, int delayTime){
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
}
