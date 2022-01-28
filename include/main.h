#pragma once
#ifndef _main_h
#define _main_h
#define DEBUGMIO
//#include <FS.h>
#include <DNSServer.h>

//
#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
  #include <ESPAsyncTCP.h>
  #include <LittleFS.h>
  #define SPIFFS LittleFS
  extern "C"
  {
  #include <user_interface.h>
  }
#else // ESP32
  #include <WiFi.h>
  #include <ETH.h>
  #include "esp_wifi.h"
  #include <ESPmDNS.h>
  #include <AsyncTCP.h>
  //#include "SPIFFS.h"
  #if ESP_IDF_VERSION_MAJOR < 4
    #ifndef CONFIG_LITTLEFS_FOR_IDF_3_2
      #define CONFIG_LITTLEFS_FOR_IDF_3_2
    #endif
    #include <LITTLEFS.h>
    #define SPIFFS LITTLEFS
  #else
    #include <LittleFS.h>
    #define SPIFFS LittleFS
  #endif
#endif
//#define SPIFFS LittleFS
//
// #ifdef ESP32
//   #include <WiFi.h>
//   #include <AsyncTCP.h>
//   #include <ESPmDNS.h>
//   //#define SPIFFS LittleFS
//   //#include <LittleFS.h>
//   #include <SPIFFS.h>
// #elif defined(ESP8266)
//   #include <ESP8266WiFi.h>
//   #include <ESPAsyncTCP.h>
//   #include <ESP8266mDNS.h>
//   	#define SPIFFS LittleFS
// 	#include <LittleFS.h> 
// #endif
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>      // needed for JSON encapsulation (send multiple variables with one string)
#include <ESP_DoubleResetDetector.h>            //https://github.com/khoih-prog/ESP_DoubleResetDetector
#include <impostazioni.h>

#include <debugutils.h>
#include "wifi.h"
#include "webserver.h"
#include <webskt.h>
#include <eep.h>
#endif