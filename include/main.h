#pragma once
#ifndef _main_h
#define _main_h
//#define SPIFFS LittleFS

#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include "SPIFFS.h"
  #define  LittleFS SPIFFS
  
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include "FS.h"
  #include <LittleFS.h>
 
#endif
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>  ////https://github.com/Links2004/arduinoWebSockets needed for instant communication between client and server through Websockets
#include <ArduinoJson.h>      // needed for JSON encapsulation (send multiple variables with one string)
#include <debugutils.h>
#include <utenti.h>
#include "html.h"
#include <impostazioni.h>
#include "wifi.h"
#include "webserver.h"
#include <webskt.h>
#endif