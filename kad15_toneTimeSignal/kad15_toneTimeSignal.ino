#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_13_BIT 13
#define LEDC_BASE_FREQ 5000
const int buzPin = 23;
const int btnPin = 17;
int noteDuration = 1000 / 8;

void setup() {
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(buzPin, LEDC_CHANNEL_0);
  pinMode(btnPin, INPUT);
}

void loop() {
  if (digitalRead(btnPin) == HIGH) {
    timeSignal();
  }
}

void timeSignal(void) {
  double note_half = noteDuration * 4;
  double note_whole = noteDuration * 8;
  double note_16th = noteDuration / 2;

  int melody[] = {440, 440, 440, 880};
  double noteDurations[] = {note_half, note_half, note_half, note_whole};

  for (int i = 0; i < 4; i++) {
    int noteDuration = noteDurations[i];
    int melodyNote = melody[i];
    ledcWriteTone(LEDC_CHANNEL_0, melodyNote);
    delay(noteDuration);
    ledcWriteTone(LEDC_CHANNEL_0, 0);
    delay(note_16th);
  }
}
