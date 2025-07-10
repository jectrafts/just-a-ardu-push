#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
int i = 0;
String two = "2";
String one = "1";
const char* ssid = "DECOM41231";
const char* password = "9886249760";
String url[3]={"https://script.google.com/macros/s/AKfycbx9a71S5iRlNGKoxXeSAY2EYI0GSgS-_MiM9upheobaeA6Rvf-OjNuWSyXZs7yBE43O/exec","https://script.google.com/macros/s/AKfycbxsLIBzH2jOTJPNgRdgioSxduJrBQ00jy0XthORV6Vq_UsncAIhbhrXt_qXKTsdt-3elA/exec","https://script.google.com/macros/s/AKfycbxoUp4cKLbqKghaVEYjZ9BehTd4UCFexHTWTh7fDVDOifP4kpBjxko6BiJHdjFhPnWPvQ/exec"};
// Google Apps Script Web App URL (script.google.com one)
String initial_url = "https://script.google.com/macros/s/AKfycbxoUp4cKLbqKghaVEYjZ9BehTd4UCFexHTWTh7fDVDOifP4kpBjxko6BiJHdjFhPnWPvQ/exec";
// b1 https://script.google.com/macros/s/AKfycbx9a71S5iRlNGKoxXeSAY2EYI0GSgS-_MiM9upheobaeA6Rvf-OjNuWSyXZs7yBE43O/exec
//b2 https://script.google.com/macros/s/AKfycbxsLIBzH2jOTJPNgRdgioSxduJrBQ00jy0XthORV6Vq_UsncAIhbhrXt_qXKTsdt-3elA/exec
//b3 https://script.google.com/macros/s/AKfycbxoUp4cKLbqKghaVEYjZ9BehTd4UCFexHTWTh7fDVDOifP4kpBjxko6BiJHdjFhPnWPvQ/exec
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");


}

void loop() {
  initial_url = url[i];

    WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;

  // Step 1: Try original URL (expect redirect)
  if (https.begin(client, initial_url)) {
    int httpCode = https.GET();
    Serial.println("Initial HTTP Code: " + String(httpCode));

    // Step 2: Check for 302 and follow "Location"
    if (httpCode == HTTP_CODE_FOUND) {  // 302
      String newURL = https.getLocation();
      Serial.println("Redirected to: " + newURL);
      https.end();

      // Step 3: Request new URL
      if (https.begin(client, newURL)) {
        int code2 = https.GET();
        Serial.println("Redirected HTTP Code: " + String(code2));

        if (code2 > 0) {
          String payload = https.getString();
          Serial.println(payload);
          const char* pay = payload.c_str();
          const char* twoo = two.c_str();
          const char* onee = one.c_str();
          if(strstr(twoo,pay)){
            Serial.println("0");
          }
          if(strstr(onee,pay)){
            Serial.println("1");
          }
        } else {
          Serial.println("Error fetching redirected URL: " + https.errorToString(code2));
        }
        https.end();
      }
    } else if (httpCode > 0) {
      // If no redirect
      String payload = https.getString();
      Serial.println("Response:\n" + payload);
      

      https.end();
    } else {
      Serial.println("Initial request failed: " + https.errorToString(httpCode));
      https.end();
    }
  } else {
    Serial.println("Connection failed.");
    
    }

  i+= 1;
  if(i==3){i=0;}
  
  }
