#pragma once
#ifndef webser_h
#define webser_h
#include <main.h>

AsyncWebServer server(serverPort);    
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
void setupServer(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // request->send(SPIFFS, "/index.html", "text/html");
    request->send(SPIFFS, "/index.html", "text/html");
    // request->send(200, "text/plain", "Hello, world");
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  // Route to load index.js file
  server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.js", "text/javascript");
  });
  server.onNotFound(notFound);
  server.begin();

}
#endif

