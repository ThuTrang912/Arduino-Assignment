
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    5

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 5

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  //colorWipe(strip.Color(255,   0,   0), 50); // Red      
  colorRun(strip.Color(255,   0,   0), 50);//赤が50ミリ秒おきに下から上へひとつずつ点灯   
  delay(1000);   
  colorRun(strip.Color(0,   255, 0), 50);//緑が50ミリ秒おきに下から上へひとつずつ点灯   
  delay(1000); 
}

/**  * colorRun  */  
void colorRun(uint32_t color, int wait) {   
  // ここにcolor色のLEDが0番目からwaitミリ秒おきに点滅する処理を入れる 
  for(int i = 0; i < LED_COUNT; i++){
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.show();
    //delay((1000 / 5) - wait);
    delay(wait);
  }

} 



