     
     
     
     
const int swPin = 17; //const…初期化した後代入されない 
int count = 0; //カウンタ変数 
int flag = 0; //フラグ初期値0:押されていない状態  
void setup() {   
  Serial.begin(115200);   
  pinMode(swPin, INPUT);   // Switch デジタル入力 
} 
void loop() {   
  int b = digitalRead(swPin);
  if(b == HIGH && flag == 0){
    Serial.println(++count);
    flag = 1;
  } 
  if(b == LOW){
    flag = 0;
  }

  /*  ここにフラグ変数flagを活用して、スイッチがおされたときだけ     
  カウンタ変数countがインクリメントされ表示されるソースをかく   
  */   
  delay(10);  
} 

// const int swPin = 17; // タクトスイッチが接続されたピン
// int count = 0; // カウンタ変数
// int flag = 0; // フラグ初期値0: 押されていない状態

// void setup() {
//   Serial.begin(115200);
//   pinMode(swPin, INPUT); // スイッチをデジタル入力に設定
// }

// void loop() {
//   int b = digitalRead(swPin);
  
//   // タクトスイッチが押されたときだけ処理を実行
//   if (b == HIGH && flag == 0) {
//     count++; // カウンタをインクリメント
//     Serial.println(count); // シリアルモニタにカウンタの値を表示
//     flag = 1; // フラグをセットしてチャタリングを防止
//   }
  
//   // タクトスイッチが離されたときにフラグをクリア
//   if (b == LOW) {
//     flag = 0;
//   }
  
//   delay(10); // ディレイを追加して安定化
// }