#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2


#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

int LED_PIN = LED_BUILTIN;

void handleRoot() {
  server.send(200, "text/html", "<h1>Welcome to our DASHBOARD for LED.</h1>");    
}

void handleTurnON()
{
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/html", "<h1>On board LED is not turned ON..</h1>");    
}

void handleTurnOFF()
{
    digitalWrite(LED_PIN, HIGH);
    server.send(200, "text/html", "<h1>On board LED is not turned OFF..</h1>"); 
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
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
  server.on("/turnOn", handleTurnON);
  server.on("/turnOff", handleTurnOFF);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
