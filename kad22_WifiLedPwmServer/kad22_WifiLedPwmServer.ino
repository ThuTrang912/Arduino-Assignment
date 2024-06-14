#include <WiFi.h>

const char ssid[] = "CampusIoT-WiFi";
const char passwd[] = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

const int blueLedPin = 4; // Blue LED
WiFiServer server(80);

void setup() {
  delay(1000);
  Serial.begin(115200);
  pinMode(blueLedPin, OUTPUT);
  ledcSetup(0, 5000, 8); // PWM channel 0, 5000 Hz, 8-bit resolution
  ledcAttachPin(blueLedPin, 0);

  Serial.print("Connecting...");
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
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
            client.println("<h1>ESP32</h1>");
            client.println("<h2>Wi-Fi LED PWM Changer</h2>");
            client.println("<form method='get'>");
            client.println("<input type='radio' name='pwm' value='0'> 0% </br>");
            client.println("<input type='radio' name='pwm' value='64'> 25% </br>");
            client.println("<input type='radio' name='pwm' value='128'> 50% </br>");
            client.println("<input type='radio' name='pwm' value='192'> 75% </br>");
            client.println("<input type='radio' name='pwm' value='255'> 100% </br>");
            client.println("<input type='submit' name='btn' value='Send' style='background-color:#88ff88; color:blue;'>");
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
       
        // if (currentLine.endsWith("GET /?pwm=64&btn=Send")) {
        if (currentLine.endsWith("btn=Send")) {
        // if (currentLine.indexOf("pwm=") != -1) {
          Serial.println("ok");
          int pwmValue = currentLine.indexOf("pwm=") != -1 ? currentLine.substring(currentLine.indexOf("pwm=") + 4, currentLine.indexOf("&")).toInt() : 0;
          ledcWrite(0, pwmValue);
          Serial.print("PWM Value: ");
          Serial.println(pwmValue);
        }
      }
    }
  }
}
