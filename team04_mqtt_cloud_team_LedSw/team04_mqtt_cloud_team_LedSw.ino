/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/

#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "CampusIoT-WiFi";
const char* password = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";
// const char* mqtt_server = "broker.mqtt-dashboard.com";
//const char* mqtt_server = "ecc-comp3.cloud.shiftr.io";
const char* mqtt_server = "team-e.cloud.shiftr.io";


#define BUILTIN_LED 4
const int swPin = 17; //const…初期化した後代入されない 
int flag = 0; //フラグ初期値0:押されていない状態  
int count = 0; //カウンタ変数 
int onOrOff = 0;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
  
  // Tìm vị trí của dấu '#'
  char* hashPosition = strchr((char*)payload, '#');

  // Kiểm tra xem có dấu '#' trong payload không
  if (hashPosition != NULL) {
    // Lấy giá trị sau dấu '#'
    char* valueStr = hashPosition + 1;

    // Chuyển giá trị chuỗi thành số nguyên
    int value = atoi(valueStr);

    // In giá trị
    Serial.print("Giá trị sau dấu '#': ");
    Serial.println(value);

    onOrOff = value;
    
    // Điều kiện bật/tắt LED
    if (value == 1) {
      digitalWrite(BUILTIN_LED, LOW);   // Bật LED
    } else {
      digitalWrite(BUILTIN_LED, HIGH);  // Tắt LED
    }
  } else {
    Serial.println("Không có dấu '#' trong payload.");
  }


  // // Switch on the LED if an 1 was received as first character
  // if ((char)payload[0] == '1') {
  //   digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
  //   // but actually the LED is on; this is because
  //   // it is active low on the ESP-01)
  // } else {
  //   digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  // }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    //String clientId = "ESP8266Client-";
    // clientId += String(random(0xffff), HEX);
    String clientId = "sk2a04"; 
    // Attempt to connect
    // if (client.connect(clientId.c_str())) {
      //ecc-comp3用①ユーザー名ト②パスワード
      if (client.connect(clientId.c_str(),"team-e","QWPwWOSiQO3hsjGs")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      client.publish("sk2a/team-e", "chan");
      // ... and resubscribe
      // client.subscribe("inTopic");
      client.subscribe("sk2a/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
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

  // unsigned long now = millis();
  // if (now - lastMsg > 2000) {
  //   lastMsg = now;
  //   ++value;
  //   // snprintf (msg, MSG_BUFFER_SIZE, "hello world #%d", value);
  //   snprintf (msg, MSG_BUFFER_SIZE, "chan #%d", value);
  //   Serial.print("Publish message: ");
  //   Serial.println(msg);
  //   // client.publish("outTopic", msg);
  //   client.publish("sk2a/team-e", msg);
  // }

  int b = digitalRead(swPin);
  if(b == HIGH && flag == 0){
    // Serial.println(++count);
    flag = 1;
    onOrOff = onOrOff ^ 1;
    // snprintf (msg, MSG_BUFFER_SIZE, "chan #%d", ++count);
    snprintf (msg, MSG_BUFFER_SIZE, "chan #%d", onOrOff);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("sk2a/team-e", msg);
  } 
  if(b == LOW){
    flag = 0;
  }
}


/////tuần sau thêm chỗ gửi đi là số 1 thì bật số 0 thì tắt,
//////khi đang là số 0 thì chuyển thành số 1
