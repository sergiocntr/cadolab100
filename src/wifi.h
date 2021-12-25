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
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (!MDNS.begin("esp32"))
  {
    Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  server.begin();
  Serial.println("TCP server started");

  MDNS.addService("http", "tcp", 80);
}
#endif
