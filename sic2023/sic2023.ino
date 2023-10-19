// #include <M5StickC.h>
// #include <WiFi.h>

// // Firebase Library 
// #include "FirebaseESP32.h"

// // Firebase Declare
// #define FIREBASE_HOST "https://sic-team-summer-2023-default-rtdb.firebaseio.com/"
// #define FIREBASE_AUTH "9tnvQAkuak27PvcqSF3OoJQt9qUJcQRZFRsFWpOE"

// // Create Variables
// FirebaseData firebaseData;
// FirebaseJson json;

// // using internet update
// const char* ssid = "Chanchan";
// const char* password = "bechan912";


// void setup() {
//   M5.begin();
//   M5.Lcd.setRotation(3);
//   M5.IMU.Init();  // Sử dụng M5.IMU thay vì M5.MPU6886.Init()
//   M5.Lcd.setTextColor(WHITE); // Font color
//   M5.Lcd.setTextSize(2); // Size

//   // Connect to WiFi
//   WiFi.begin(ssid, password);

//   while(WiFi.status() != WL_CONNECTED){
//     delay(500);
//     Serial.print(".");  
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");

//   //Connect to Firebase
//   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//   Firebase.reconnectWiFi(true);  
// }

// int gia_toc;

// String truong_gia_toc = "/truong_gia_toc";

// void loop() {
//   M5.Lcd.fillScreen(BLACK);  // Clean Screen
//   for (int i = 0; i < 200; i++) {
//       M5.Lcd.fillRect(10, 0, 160, 80, BLACK);  // x , y width, height
//       float ax, ay, az;
//       M5.IMU.getAccelData(&ax, &ay, &az);  // 値を取得
//       ax = ax * -1;
//       //ay = ay * 1000;
//       //az = az * 1000;
//       Serial.printf("ax: %.2f, ay: %.2f, az: %.2f", ax, ay, az);

//       M5.Lcd.setCursor(0, 0); // Text LOCATION      
//       M5.Lcd.print("x: ");
//       M5.Lcd.print(ax, 1); // 0.02

//       M5.Lcd.setCursor(0, 20); // Text LOCATION      
//       M5.Lcd.print("y: ");
//       M5.Lcd.print(ay, 1); // 0.02
      
//       M5.Lcd.setCursor(0, 40); // Text LOCATION      
//       M5.Lcd.print("z: ");
//       M5.Lcd.print(az, 1); // 0.02

//       if(ax > 1)
//       delay(2000);
//   }
// }


#include <M5StickC.h>
#include <Wire.h>
#include <FirebaseESP32.h>
#include <WiFi.h>

// Firebase Credentials
#define FIREBASE_HOST "your-firebase-host.firebaseio.com"
#define FIREBASE_AUTH "your-firebase-auth-token"

// WiFi Credentials
const char* ssid = "Chanchan";
const char* password = "bechan912";

// Firebase database path
const String accelPath = "/acceleration";

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.IMU.Init();
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  M5.Lcd.fillScreen(BLACK);
  for (int i = 0; i < 200; i++) {
    M5.Lcd.fillRect(10, 0, 160, 80, BLACK);
    float ax, ay, az;
    M5.IMU.getAccelData(&ax, &ay, &az);

    // Calculate acceleration magnitude
    float acceleration = sqrt(ax * ax + ay * ay + az * az);

    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("Acceleration: ");
    M5.Lcd.print(acceleration, 2);

    // If acceleration exceeds a threshold, update Firebase
    if (acceleration > 5.0) { // Adjust the threshold as needed
      updateFirebase(acceleration);
    }

    delay(2000);
  }
}

void updateFirebase(float acceleration) {
  // Create a JSON object to send to Firebase
  FirebaseJson json;
  json.setFloat("acceleration", acceleration);

  // Send the JSON data to Firebase
  Firebase.pushFloat(accelPath, json);
}

