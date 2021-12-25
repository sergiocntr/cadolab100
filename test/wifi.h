#pragma once
#ifndef _wifi_h
#define _wifi_h
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include "variabili.h"
#include "impostazioni.h"
//long rssi;
//int status = WL_IDLE_STATUS;
WiFiServer server(80);
void inizializza_wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    #ifdef DEBUGMIO
      Serial.println("STA Failed to configure");
    #endif
    
  }
  WiFi.begin(ssid, password);
    #ifdef DEBUGMIO
      Serial.println("");
    #endif
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
#ifdef DEBUGMIO
  Serial.print(".");
#endif
    
  }
#ifdef DEBUGMIO
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif
  
  if (!MDNS.begin("esp32"))
  {
#ifdef DEBUGMIO
    Serial.println("Error setting up MDNS responder!");
#endif
    
    while (1)
    {
      delay(1000);
    }
  }
#ifdef DEBUGMIO
  Serial.println("mDNS responder started");
#endif
  
  server.begin();
#ifdef DEBUGMIO
  Serial.println("TCP server started");
#endif
  

  MDNS.addService("http", "tcp", 80);
}
#endif
