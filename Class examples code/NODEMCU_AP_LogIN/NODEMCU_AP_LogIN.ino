#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

String logInHTML = "<form action=\"action_page.php\" method=\"post\">\n"
"  <div class=\"container\">\n"
"    <label for=\"uname\"><b>Username</b></label>\n"
"    <input type=\"text\" placeholder=\"Enter Username\" name=\"uname\" required>\n"
"\n"
"    <label for=\"psw\"><b>Password</b></label>\n"
"    <input type=\"password\" placeholder=\"Enter Password\" name=\"psw\" required>\n"
"\n"
"    <button type=\"submit\">Login</button>\n"
"    <label>\n"
"      <input type=\"checkbox\" checked=\"checked\" name=\"remember\"> Remember me\n"
"    </label>\n"
"  </div>\n"
"\n"
"  <div class=\"container\" style=\"background-color:#f1f1f1\">\n"
"    <button type=\"button\" class=\"cancelbtn\">Cancel</button>\n"
"    <span class=\"psw\">Forgot <a href=\"#\">password?</a></span>\n"
"  </div>\n"
"</form>";

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", logInHTML);
}

void handleAbout() {
  server.send(200, "text/html", "<h2>This is about page</h1>");
}

void handleMyProfile() {
  server.send(200, "text/html", "<h3>This is my profile page</h1>");
}

void setup() {
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
  server.on("/about", handleAbout);
  server.on("/profile", handleMyProfile);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
