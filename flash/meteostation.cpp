#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"

#define DHTPIN 14
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "*****"; // Wi-Fi SSID
const char* password = "*****"; // Wi-Fi password
const char* host = "0.0.0.0"; // Server IP
const int port = 80; // Server port

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
  Serial.println("================================");
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  
  HTTPClient http;
  
  http.begin("http://"+host+":"+String(port)+"/");
  http.addHeader("Content-Type", "application/json");
  
  int httpCode = http.POST("{\"tmp\": "+String(t)+", \"hmd\": "+String(h)+"}");
  String payload = http.getString();
  http.end();

  delay(1000);
  
}

