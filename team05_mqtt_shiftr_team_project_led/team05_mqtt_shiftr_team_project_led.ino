#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "CampusIoT-WiFi";
const char* password = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";
const char* mqtt_server = "team-e.cloud.shiftr.io";

#define BUILTIN_LED 4
#define LED_PIN    5
#define LED_COUNT 5

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int swPin = 17;
int flag = 0;
int onOrOff = 0;
int led_count = 0;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void callback(char* topic, byte* payload, unsigned int length) {
  // Print received message details
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Find '#' character in the payload
  char* hashPosition = strchr((char*)payload, '#');

  if (hashPosition != NULL) {
    // Extract value after '#'
    char* valueStr = hashPosition + 1;
    
    // Convert the value string to an integer
    int value = atoi(valueStr);

    Serial.print("Giá trị sau dấu '#': ");
    Serial.println(value);

    // Update LED count
    led_count = value/10;
    Serial.println(led_count);

    // Control LEDs based on the value
    if (led_count <= 5) {
      // Example behavior for value less than 5
      digitalWrite(BUILTIN_LED, HIGH);
      colorDotOn(led_count - 1, strip.Color(0, 0, 255));
      delay(1000);
      colorDotOff(led_count -1 );
      delay(1000);
    }
    if (led_count == 5) {
      // Example behavior for value equal to 5
      colorDotOn(0, strip.Color(255, 255, 0));
      delay(1000);
      colorDotOff(0);
      delay(1000);
    } 
  } else {
    // No '#' found in the payload
    Serial.println("Không có dấu '#' trong payload.");
  }
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "sk2a04_led";

    if (client.connect(clientId.c_str(), "team-e", "QWPwWOSiQO3hsjGs")) {
      Serial.println("connected");
      client.publish("sk2a/team-e", "led");
      client.subscribe("sk2a/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

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

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // int b = digitalRead(swPin);
  // if (b == HIGH && flag == 0) {
  //   flag = 1;
  //   if(led_count < 5 ){
  //     led_count++;
  //   }else{led_count = 1;}
    
  //   snprintf(msg, MSG_BUFFER_SIZE, "chan #%d", led_count);
  //   Serial.print("Publish message: ");
  //   Serial.println(msg);
  //   client.publish("sk2a/team-e", msg);
  // }
  // if (b == LOW) {
  //   flag = 0;
  // }
  
}

/**  * colorDotOn  */ 
void colorDotOn(int i, uint32_t color){
  strip.setPixelColor(i, color);
  strip.show();
}

/**  * colorDotOff  */ 
void colorDotOff(int i){
  strip.setPixelColor(i, strip.Color(0, 0, 0));
  strip.show();
}

