#pragma once
#ifndef webser_h
#define webser_h
#include <Arduino.h>
#include <WebServer.h>                                // needed to create a simple webserver
#include <ArduinoJson.h>
#include "variabili.h"
#include "html.h"

WebServer server(serverPort);                                 // the server uses port 80 (standard port for websites
void setupServer(){
  server.on("/", []() {                               // define here wat the webserver needs to do
    server.send(200, "text\html", page);           //    -> it needs to send out the HTML string "webpage" to the client
  });
  
  server.begin();                                     // start server
}
void loopServer() {
  server.handleClient();                              // Needed for the webserver to handle all clients
  
}


#endif