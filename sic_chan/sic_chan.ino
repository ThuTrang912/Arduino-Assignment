#include <M5StickC.h>
#include <Wire.h>
#include <FirebaseESP32.h>
#include <WiFi.h>

// Firebase Credentials
#define FIREBASE_HOST "sic-team-summer-2023-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "9tnvQAkuak27PvcqSF3OoJQt9qUJcQRZFRsFWpOE"

// WiFi Credentials
const char* WIFI_SSID = "Chanchan";
const char* WIFI_PASSWORD = "bechan912";

// Firebase database path
const String accelPathX = "/acceleration-x"; // Firebase path for acceleration-x

FirebaseData fbdo; // FirebaseData object for Firebase communication

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.IMU.Init();
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Initialize FirebaseConfig and FirebaseAuth
  FirebaseConfig config;
  config.host = FIREBASE_HOST;
  //config.auth_type = FIREBASE_USE_PSRAM;
  config.api_key = FIREBASE_AUTH;
  FirebaseAuth auth;
  //auth.user_email = ""; // Leave this empty if not using email authentication

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("HELLO");
}

void updateFirebase(float acceleration, const String& path) {
  // Create a JSON object to send to Firebase
  FirebaseJson json;
  json.set("value", String(acceleration));

  // Send JSON data to Firebase
  if (Firebase.updateNode(fbdo, path, json)) {
    Serial.println("Firebase update success");
  } else {
    Serial.println("Firebase update failed");
    Serial.println(fbdo.errorReason());
  }
}

void loop() {

  if (Firebase.get(fbdo, "/test")) {
    Serial.print("Firebase test data: ");
    Serial.println(fbdo.stringData());
  } else {
    Serial.print("Failed to get Firebase test data. Error: ");
    Serial.println(fbdo.errorReason());
  }

  // delay(5000);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("HELLO");
  // for (int i = 0; i < 200; i++) {
  //   M5.Lcd.fillRect(10, 0, 160, 80, BLACK);
  //   float ax, ay, az;
  //   M5.IMU.getAccelData(&ax, &ay, &az);

  //   // Use only acceleration along the X-axis
  //   float accelerationX = ax;
  //   Serial.printf("ax: %.2f /n", accelerationX);

  //   M5.Lcd.setCursor(0, 0);
  //   M5.Lcd.print("Acceleration X: ");
  //   M5.Lcd.print(accelerationX, 1);

    
  //       // Send Firebase data for acceleration along the X-axis
  //       updateFirebase(accelerationX, accelPathX);

    
  //   delay(1000);
  // }
  
}


