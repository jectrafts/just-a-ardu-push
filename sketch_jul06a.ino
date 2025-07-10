#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
String r ="";
int i=0 ;
const char* ssid = "DECOM41231";
const char* password = "9886249760";

const char* scriptURL = "https://script.google.com/macros/s/AKfycbxoUp4cKLbqKghaVEYjZ9BehTd4UCFexHTWTh7fDVDOifP4kpBjxko6BiJHdjFhPnWPvQ/exec";
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

 // Bypass SSL checks (not secure for production)

}

void loop() {
  i+=1;
  WiFiClientSecure client;
  client.setInsecure(); 
  HTTPClient https;
  if (https.begin(client, scriptURL)) {
    https.addHeader("Content-Type", "application/json");
    String json0 = "{\"value\":\"0\"}";
    String json1 = "{\"value\":\"1\"}";
    
    if((i%2)==0){
      r=json0;
     }
    else{
      r=json1;
     }
    int httpCode = https.POST(r);
    String payload = https.getString();

    Serial.println("HTTP Response code: " + String(httpCode));
    Serial.println("Server response: " + payload);

    https.end();
  } else {
    Serial.println("Connection to script failed.");
  }

}
  
  // Nothing
