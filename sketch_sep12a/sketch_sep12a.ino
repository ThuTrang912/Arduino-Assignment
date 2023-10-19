#include <WiFi.h>

// Firebase Library 
#include "FirebaseESP32.h"

// Firebase Declare
#define FIREBASE_HOST "https://sic-team-summer-2023-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "9tnvQAkuak27PvcqSF3OoJQt9qUJcQRZFRsFWpOE"

// Create Variables
FirebaseData firebaseData;
FirebaseJson json;

// using internet update
const char* ssid = "";
const char* password = "";

void setup() {
  // Connect to WiFi
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");  
  }
  Serial.println("");
  Serial.println("WiFi connected");

  //Connect to Firebase
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//  Firebase.reconnectWiFi(true);  
}

int gia_toc;

String truong_gia_toc = "/truong_gia_toc";

void loop() {
  // lấy giá trị kiểu int từ firebase
  Firebase.getInt(firebaseData, truong_gia_toc);
  //hứng giá trị 
  gia_toc = firebaseData.intData();
  {
      Serial.println("data in /truong_gia_toc :");
      Serial.println(gia_toc);
      delay(1000);  
  }

  //set giá trị
  Firebase.setInt(firebaseData, truong_gia_toc, 10);
  Serial.println("Push data to /truong_gia_toc done");
  Serial.println();
  delay(1000);
  
}
