#include <WiFi.h>


//接続先のSSIDとパスワード学内CampusIOT
const char ssid[] = "CampusIoT-WiFi";
const char passwd[] = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

const int ledPin = 16; // 赤色LED
WiFiServer server(80);


void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT); // set the LED pin mode

  //Wifi接続シーケンス
  Serial.print("Connecting...");
  WiFi.begin(ssid, passwd);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println(" connected");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
   WiFiClient client = server.available();

  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<meta name='viewport' content='initial-scale=1.5'>");
            client.println("</head>");
            client.println("<body>");
            client.println("<form method='get'>");
            client.println("<h1>ESP32</h1>");
            client.println("<h2>Wi-Fi LED Switch</h2>");
            client.println("<input type='submit' name=btn value='ON' style='background-color:#88ff88; color:red;'>");
            client.println("<input type='submit' name=btn value='OFF' style='background-color:black; color:white;'>");
            client.println("</form>");
            client.println("</body>");
            client.println("</html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /?btn=ON")) {
          digitalWrite(ledPin, HIGH);
        }
        if (currentLine.endsWith("GET /?btn=OFF")) {
          digitalWrite(ledPin, LOW);
        }
      }
    }

    client.stop();
    Serial.println("client disonnected");
  }
}
