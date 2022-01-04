#pragma once
#ifndef webser_h
#define webser_h
#include <main.h>

AsyncWebServer server(serverPort);    // the server uses port 80 (standard port for websites


void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
void setupServer(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
    return request->requestAuthentication();
    request->send(LittleFS, "/index.html", "text/html");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css","text/css");
  });
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/main.js","application/json");
  });
  
  server.onNotFound(notFound);
  
  server.begin();
}
void loopServer() {
 
  


}
#endif
