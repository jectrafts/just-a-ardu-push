#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Servo.h> // servo library  
Servo s1;
Servo s2;  
int r=2;
int f=2;
int z =2;
// Wi-Fi credentials
const char* ssid = "wifi name";
const char* password = "wifi password";

// Google Apps Script Web App URL (doGet URL)
const char* url = "url";

void setup() {
  s1.attach(4);
  s2.attach(0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Call the Google Apps Script to GET , b2, b3
  fetchData();
}

void loop() {
  // Optional: fetch every 10 seconds
  // fetchData();
  // delay(10000);
  fetchData();

}
void fetchData() {
  WiFiClientSecure client;
  client.setInsecure();  // Don't verify SSL cert

  HTTPClient http;
  http.begin(client, url);

  int httpCode = http.GET();
  Serial.println("GET Code: " + String(httpCode));

  if (httpCode == HTTP_CODE_FOUND) {  // 302 Redirect
    String newUrl = http.getLocation();
    Serial.println("Redirected to: " + newUrl);
    http.end();  // Close current connection

    if (http.begin(client, newUrl)) {
      int redirectedCode = http.GET();
      Serial.println("Redirected GET Code: " + String(redirectedCode));

      if (redirectedCode > 0) {
        String payload = http.getString();
        Serial.println("Redirected Response: " + payload);

        // Parse JSON
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print("JSON parse failed: ");
          Serial.println(error.c_str());
          return;
        }

        String b1 = doc["b1"];
        String b2 = doc["b2"];
        String b3 = doc["b3"];

        Serial.println("b1 = " + b1);
        Serial.println("b2 = " + b2);
        Serial.println("b3 = " + b3);
        if((b1=="0")&&(r==0 || r==2)){
          Serial.println("10");
          s1.write(180);  //s1 180 closes s2 0 closes
          delay(1000);  
          s1.write(90);  
          delay(1000); 
          r=1;
          }
        if((b1=="1")&&(r==1 || r==2)){
          Serial.println("11");
          s1.write(0);  //s1 180 closes s2 0 closes
          delay(1000);  
          s1.write(90);  
          delay(1000); 
          r=0;
        }
        if((b3=="0")&&(f==0 || f==2)){
          Serial.println("20");
          s2.write(0);  //s1 180 closes s2 0 closes
          delay(1000);  
          s2.write(30);  
          delay(1000); 
          f=1;
          }
        if((b3=="1")&&(f==1 || f==2)){
          Serial.println("20");
          s2.write(180);  //s1 180 closes s2 0 closes
          delay(1000);  
          s2.write(80);  
          delay(1000); 
          f=0;
        }
        if(b2=="0"&&(z==1 || z==2)){
          Serial.println("30");
          s1.write(0);  //s1 180 closes s2 0 closes
          delay(1000);  
          s1.write(30);  
          delay(1000); 
          z=1;
          }
        if(b2=="1"&&(z==1 || z==2)){
          Serial.println("31");
          s1.write(180);  //s1 180 closes s2 0 closes
          delay(1000);  
          s1.write(90);  
          delay(1000); 
          z=1;
        }
      } else {
        Serial.println("Redirected GET failed: " + http.errorToString(redirectedCode));
      }

      http.end();
    }
  } else if (httpCode > 0) {
    // Not redirected but got valid response
    String payload = http.getString();
    Serial.println("Response: " + payload);

    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print("JSON parse failed: ");
      Serial.println(error.c_str());
      return;
    }

    String b1 = doc["b1"];
    String b2 = doc["b2"];
    String b3 = doc["b3"];

    Serial.println("b1 = " + b1);
    Serial.println("b2 = " + b2);
    Serial.println("b3 = " + b3);
    if(b1=="1"){
      Serial.println("11");
      }
    if(b1=="0"){
      Serial.println("10");
    }
    if(b2=="1"){
      Serial.println("21");
      }
    if(b2=="0"){
      Serial.println("20");
    }
    if(b3=="1"){
      Serial.println("31");
      }
    if(b3=="0"){
      Serial.println("30");
    }
  } else {
    Serial.println("Initial GET failed: " + http.errorToString(httpCode));
  }

  http.end();
}
