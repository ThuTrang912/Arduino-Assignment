#include <WiFi.h>
#include "Ambient.h"

const char* ssid = "CampusIoT-WiFi";
const char* password = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

unsigned int channelId = 71751;
const char* writeKey = "9abff23f7bd0173b";

WiFiClient client;
Ambient ambient;

void setup(){
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    ambient.begin(channelId, writeKey, &client);
}

void loop(){
	int rand;
	rand = random(1000);

    ambient.set(1, rand);                // データーがint型かfloat型であれば、直接セットすることができます。
    ambient.send();
    Serial.println(rand);

    delay(5000);
}
