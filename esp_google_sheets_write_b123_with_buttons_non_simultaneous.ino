#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
String r ="";
int f=0 ;
int z=0 ;
int i=0 ;
#define BUTTON_PIN3 4
#define BUTTON_PIN4 0
#define BUTTON_PIN5 2 
const char* ssid = "DECOM41231";
const char* password = "9886249760";

const char* scriptURL = "https://script.google.com/macros/s/AKfycbxoUp4cKLbqKghaVEYjZ9BehTd4UCFexHTWTh7fDVDOifP4kpBjxko6BiJHdjFhPnWPvQ/exec";
const char* sr1 = "https://script.google.com/macros/s/AKfycbx9a71S5iRlNGKoxXeSAY2EYI0GSgS-_MiM9upheobaeA6Rvf-OjNuWSyXZs7yBE43O/exec";
const char* sr3 ="https://script.google.com/macros/s/AKfycbxsLIBzH2jOTJPNgRdgioSxduJrBQ00jy0XthORV6Vq_UsncAIhbhrXt_qXKTsdt-3elA/exec";
const char* sr2 = "https://script.google.com/macros/s/AKfycbxoUp4cKLbqKghaVEYjZ9BehTd4UCFexHTWTh7fDVDOifP4kpBjxko6BiJHdjFhPnWPvQ/exec";
void setup() {
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
  pinMode(BUTTON_PIN4, INPUT_PULLUP);
  pinMode(BUTTON_PIN5, INPUT_PULLUP);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  WiFiClientSecure client;
  client.setInsecure();  // Bypass SSL checks (not secure for production)

}

void loop() {
  int bt3 = digitalRead(BUTTON_PIN3);
  int bt4 = digitalRead(BUTTON_PIN4);
  int bt5 = digitalRead(BUTTON_PIN5);
  if ((bt3 ==0 )){
    
    Serial.println("high3");
    delay(200);
    f+=1;
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    if (https.begin(client, sr1)) {
      https.addHeader("Content-Type", "application/json");
      String json0 = "{\"value\":\"0\"}";
      String json1 = "{\"value\":\"1\"}";
     
      if((f%2)==0){
        
        int httpCode = https.POST(json0);
        String payload = https.getString();
    
        Serial.println("HTTP Response code: " + String(httpCode));
        Serial.println("Server response: " + payload);
    
        https.end();
          } 
      
  
         
       
      else{
        
        int httpCode = https.POST(json1);
        String payload = https.getString();
    
        Serial.println("HTTP Response code: " + String(httpCode));
        Serial.println("Server response: " + payload);
    
        https.end();
        } 

  
  }

  }
  if ((bt4 ==0 )){
    Serial.println("high4");
    delay(200);
    z+=1;
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    if (https.begin(client, sr2)) {
      https.addHeader("Content-Type", "application/json");
      String json0 = "{\"value\":\"0\"}";
      String json1 = "{\"value\":\"1\"}";
     
      if((z%2)==0){
        
        int httpCode = https.POST(json0);
        String payload = https.getString();
    
        Serial.println("HTTP Response code: " + String(httpCode));
        Serial.println("Server response: " + payload);
    
        https.end();
          } 
      
  
         
       
      else{
        
        int httpCode = https.POST(json1);
        String payload = https.getString();
    
        Serial.println("HTTP Response code: " + String(httpCode));
        Serial.println("Server response: " + payload);
    
        https.end();
        } 

  
  }

  }
  if ((bt5 ==0 )){
    Serial.println("high5");
    delay(200);
    i+=1;
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    if (https.begin(client, sr3)) {
      https.addHeader("Content-Type", "application/json");
      String json0 = "{\"value\":\"0\"}";
      String json1 = "{\"value\":\"1\"}";
     
      if((i%2)==0){
        
        int httpCode = https.POST(json0);
        String payload = https.getString();
    
        Serial.println("HTTP Response code: " + String(httpCode));
        Serial.println("Server response: " + payload);
    
        https.end();
          } 
      
  
         
       
      else{
        
        int httpCode = https.POST(json1);
        String payload = https.getString();
    
        Serial.println("HTTP Response code: " + String(httpCode));
        Serial.println("Server response: " + payload);
    
        https.end();
        } 
  
    
    }

  }
}
     

  
  // Nothing
