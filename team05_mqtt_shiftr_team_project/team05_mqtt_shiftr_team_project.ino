#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "CampusIoT-WiFi";
const char* password = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";
const char* mqtt_server = "team-e.cloud.shiftr.io";

#define BUILTIN_LED 4


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
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  char* hashPosition = strchr((char*)payload, '#');

  if (hashPosition != NULL) {
    char* valueStr = hashPosition + 1;
    int value = atoi(valueStr);

    Serial.print("Giá trị sau dấu '#': ");
    Serial.println(value);

    led_count = value;

    if (value == 1) {
      digitalWrite(BUILTIN_LED, LOW);
    } else {
      digitalWrite(BUILTIN_LED, HIGH);
    }
  } else {
    Serial.println("Không có dấu '#' trong payload.");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "sk2a04";

    if (client.connect(clientId.c_str(), "team-e", "QWPwWOSiQO3hsjGs")) {
      Serial.println("connected");
      client.publish("sk2a/team-e", "chan");
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

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int b = digitalRead(swPin);
  if (b == HIGH && flag == 0) {
    flag = 1;
    if(led_count < 5 ){
      led_count++;
    }else{led_count = 1;}
    
    snprintf(msg, MSG_BUFFER_SIZE, "chan #%d", led_count);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("sk2a/team-e", msg);
  }
  if (b == LOW) {
    flag = 0;
  }

 
}