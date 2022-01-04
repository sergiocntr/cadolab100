#pragma once
#ifndef _main_h
#define _main_h
#include <FS.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <SPIFFS.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  	#define SPIFFS LittleFS
	#include <LittleFS.h> 
#endif
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>  ////https://github.com/Links2004/arduinoWebSockets needed for instant communication between client and server through Websockets
#include <ArduinoJson.h>      // needed for JSON encapsulation (send multiple variables with one string)

#include <impostazioni.h>
enum loginStates loginSt ;
loginCredential loginCred;
#include <debugutils.h>
#include "wifi.h"
#include "webserver.h"
#include <webskt.h>
#include <eep.h>


#endif