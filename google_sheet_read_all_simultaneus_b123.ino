#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Wi-Fi credentials
const char* ssid = "DECOM41231";
const char* password = "9886249760";

// Google Apps Script Web App URL (doGet URL)
const char* url = "https://script.google.com/macros/s/AKfycbw5W-nH-qBLN_tfsfjj0BymnIiLI6_VTKXvtH3u0HY0hpsyQ2jXuaflpPdQHyguuepjXg/exec";

void setup() {
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
  } else {
    Serial.println("Initial GET failed: " + http.errorToString(httpCode));
  }

  http.end();
}
