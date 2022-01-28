#pragma once
#ifndef _wifi_h
#define _wifi_h
#include <main.h>
const byte DNS_PORT = 53;
DNSServer dnsServer;
#pragma region STA
bool inizializza_wifi()
{
  WiFi.setSleep(WIFI_PS_NONE);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.hostname(Progetto);      // DHCP Hostname (useful for finding device for static lease)
  //
  //RECUPERO DATI CONNESSIONE
  //
  String ip = String(loginCred.IPUsr );
  if(ip != "")
  {
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress primaryDNS(8, 8, 8, 8);
    IPAddress secondaryDNS(8, 8, 4, 4);
    IPAddress local_IP;
    bool x= local_IP.fromString(ip);
    if (! WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
    {
      #ifdef DEBUGMIO
        Serial.println("STA Failed to configure");
      #endif
      loginSt = WIFI_CONF_ERR;
    }
  }

delay(100);
  
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
//***********-----------------**************----------------***************
#pragma region AP
void setAPMode(){
  WiFi.mode(WIFI_AP);
  WiFi.disconnect();

WiFi.softAP(ssidAP, passwordAP);

  IPAddress IP = WiFi.softAPIP();
  
  DEBUG_PRINT("AP IP address: " +IP.toString() );
 dnsServer.start(DNS_PORT, "*", IP);
}
#pragma endregion AP
#endif
