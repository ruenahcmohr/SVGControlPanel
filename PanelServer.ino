#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <FS.h>

const char* ssid = "FBI073482";
const char* password = "........";

ESP8266WebServer server(80);


void handleRoot() {
  
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "C" ) {
     if (0) {
     } else if (server.arg(i) == "0") {
      digitalWrite(LED_BUILTIN, LOW);
     } else if (server.arg(i) == "1") {
      digitalWrite(LED_BUILTIN, HIGH);
     } 
    }
     
  }
  
    File file = SPIFFS.open("/main.svg", "r"); // Open it
    if (!file) {
      
      String message = "file error\n";
      message += "<br>";
    
      Dir dir = SPIFFS.openDir("");
      while (dir.next()) {
        message += dir.fileName();
        message += "<br>";
      }
      message += "End of file list";
      server.send(200, "text/html", message);
      
    } else {
      server.streamFile(file, "image/svg+xml"); // And send it to the client
      file.close(); // Close it
    }
    
 
}

void handleNotFound() {
  server.send(404, "text/plain", "File Not Found\n\n");
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  //Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  if (SPIFFS.begin()) fsok = 'y';

  //delay(3000);
  //Serial.print("Mac : ");
  //Serial.println(WiFi.macAddress());
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   // Serial.print(".");
  }
  //Serial.println("");

  //Serial.print("Connected to ");
  //Serial.println(ssid);
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());

  MDNS.begin("esp8266");
  
   server.on("/", handleRoot);

 // server.on("/inline", []() { server.send(200, "text/plain", "this works as well");  });

  server.onNotFound(handleNotFound);

  server.begin();
}

void loop(void) {
  server.handleClient();
}
