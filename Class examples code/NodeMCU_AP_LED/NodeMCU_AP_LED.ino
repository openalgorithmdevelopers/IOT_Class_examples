#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = D2;
SimpleDHT11 dht11(pinDHT11);


#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

int LED_STATUS = 0;

void handleRoot() {
  Serial.println(LED_STATUS);
  if(LED_STATUS == 1)
  {
    LED_STATUS = 0;
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    LED_STATUS = 1;
    digitalWrite(LED_BUILTIN, LOW);
  }
  server.send(200, "text/html", "<h1>LED is " + String(LED_STATUS) + "</h1>");    
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
