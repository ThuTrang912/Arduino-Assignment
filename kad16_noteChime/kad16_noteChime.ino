#define LEDC_CHANNEL_0 0//LEDCのPWMチャネル0から15
#define LEDC_TIMER_13_BIT 13 //LEDCS-013
#define LEDC_BASE_FREQ 5000 //LEDCO-25000Hz

const int buzPin = 23; // GPIO 1023pin
const int btnPin = 17;

const int NOTE_NONE = NOTE_MAX; // // 各音符の音程 (音の高さ)

int melody[] = {  
  NOTE_E, NOTE_C, NOTE_D, NOTE_G, NOTE_NONE, NOTE_G, NOTE_D, NOTE_E, NOTE_C, NOTE_NONE 
};
// 各音符の音階 (オクターブ)
int noteOctaves[] = { 4, 4, 4, 3, 0, 3, 4, 4, 4, 0 };
//各音符の長さ
int noteDurations[] = { 2, 2, 2, 1, 4, 2, 2, 2, 1, 4};

void setup() {
  ledcSetup (LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT); 
  ledcAttachPin(buzPin, LEDC_CHANNEL_0);
  pinMode(btnPin, INPUT);
}

void loop(){
  if(digitalRead(btnPin) == HIGH){
    for (int thisNote= 0; thisNote < 10; thisNote++) {
      ledcWriteNote(LEDC_CHANNEL_0, (note_t)melody[thisNote], noteOctaves[thisNote]);
      int pauseBetweenNotes = 1000 / noteDurations[thisNote] * 1.30;
      delay(pauseBetweenNotes);
      ledcWriteTone(LEDC_CHANNEL_0, 0); //演奏止める.
    }
    delay(2000);
  }
}