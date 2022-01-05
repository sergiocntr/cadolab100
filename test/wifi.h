#pragma once
#ifndef _wifi_h
#define _wifi_h
#include <main.h>
//
#pragma region STA
bool inizializza_wifi()
{
  WiFi.setSleep(WIFI_PS_NONE);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  //
  //RECUPERO DATI CONNESSIONE
  //
  
  delay(100);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    #ifdef DEBUGMIO
      Serial.println("STA Failed to configure");
      
    #endif
    loginSt = WIFI_CONF_ERR;
    return false;
    
  }
  WiFi.begin(loginCred.ssid, loginCred.passSsid);
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
      loginSt = WIFI_CONF_ERR;
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
  Serial.println(loginCred.ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif
  loginSt = WIFI_CONN_OK;
  return true;
}
#pragma endregion STA
#pragma region AP
void setAPMode(){
  WiFi.mode(WIFI_AP);
  WiFi.disconnect();

WiFi.softAP(ssidAP, passwordAP);

  IPAddress IP = WiFi.softAPIP();
  #ifdef DEBUGMIO
    DEBUG_PRINT("AP IP address: ");Serial.println(IP);
  #endif
}
#pragma endregion AP
#endif
