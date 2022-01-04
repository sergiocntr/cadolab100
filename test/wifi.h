#pragma once
#ifndef _wifi_h
#define _wifi_h
#include <main.h>
bool inizializza_wifi()
{
  WiFi.setSleep(WIFI_PS_NONE);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    #ifdef DEBUGMIO
      Serial.println("STA Failed to configure");
      login = 
    #endif
    return false;
    
  }
  WiFi.begin(ssid, password);
    #ifdef DEBUGMIO
      Serial.println("");
    #endif
  uint32_t timeoutConn = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    if ( (millis()- timeoutConn) >10000 )
    {
      #ifdef DEBUGMIO
      Serial.println("WIFI connection timed out");
    #endif
      return false;
    }
    
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
  
//   if (!MDNS.begin("esp32"))
//   {
// #ifdef DEBUGMIO
//     Serial.println("Error setting up MDNS responder!");
// #endif
//     return false;
//   }
// #ifdef DEBUGMIO
//   Serial.println("mDNS responder started");
// #endif
  
  //server.begin();
#ifdef DEBUGMIO
  Serial.println("TCP server started");
#endif
  

  //MDNS.addService("http", "tcp", 80);
  return true;
}
#endif
