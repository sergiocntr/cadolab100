#pragma once
#ifndef webser_h
#define webser_h
#include <Arduino.h>
#include <ArduinoJson.h>
#include "variabili.h"
#include "html.h"
void setupWeb(){
  ip = WiFi.localIP();
} 
void Comanda_Uscita(uint8_t Numero)
{
  if (uscita[Numero]==1)
  {
    //digitalWrite(Numero+1, HIGH); 
    uscita[Numero]=0;
  } 
  else
  {
    //digitalWrite(Numero+1, LOW); 
    uscita[Numero]=1;
  }
}

void Pubblica_Web() 
{ 
    WiFiClient client = server.available();
    
    if (!client) 
    {
        return;
    }
    Serial.println("");
    Serial.println("New client");
    while(client.connected() && !client.available())
    {
        delay(1);
    }
    String req = client.readStringUntil('\r');
    uint8_t addr_start = req.indexOf(' ');
    uint8_t addr_end = req.indexOf(' ', addr_start + 1);
    if (addr_start == -1 || addr_end == -1) 
    {      
        Serial.print("Richiesta non valida: ");
        Serial.println(req);
        return;
    }
    req = req.substring(addr_start + 1, addr_end);
    Serial.print("Request: ");
    Serial.println(req);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
    client.println();
    if(req == "/status"){
      Serial.println("dentro status"); 
        //faiJson();
        StaticJsonDocument<384> doc;
        int rssi = WiFi.RSSI();
        if (rssi<-30&&rssi>-66) doc["rssiPer"] = "100%";
        else if (rssi<-67&&rssi>-69) doc["rssiPer"] = "90%"; 
        else if (rssi<-70&&rssi>-79) doc["rssiPer"] = "30%";
        else if (rssi<-80&&rssi>-90) doc["rssiPer"] = "10%";
        doc["nome"] = NomeProg;
        doc["progetto"] = Progetto;
        doc["vers"] = Versione;
        doc["ssid"] = ssid;
        doc["rssi"] = rssi;


        JsonArray puls = doc.createNestedArray("puls");
        for (size_t i = 0; i < 9; i++)
        {
          puls.add(uscita[i]); 
          //Serial.println(uscita[i]);
        }
        String json;
        serializeJson(doc, json);
        client.println(json);
        
    }else {
      
      bool check =false;
      if (req.endsWith("/e")) {
        Comanda_Uscita(0);
        client.println((const char*)index_min_html);
      } else
      if (req.endsWith("/t")) {
        Comanda_Uscita(1);
        client.println((const char*)index_min_html);
      } else
      if (req.endsWith("/u")) {
        Comanda_Uscita(2);
        client.println((const char*)index_min_html);
      } else
      if (req.endsWith("/o")) {
        Comanda_Uscita(3);
        client.println((const char*)index_min_html);
      } else
      if (req.endsWith("/a")) {
        Comanda_Uscita(4);
        client.println((const char*)index_min_html);
      } else
      if (req.endsWith("/d")) {
        Comanda_Uscita(5);
        client.println((const char*)index_min_html);
      } else
      if (req.endsWith("/g")) {
        Comanda_Uscita(6);
        client.println((const char*)index_min_html);
      } else
      if (req.endsWith("/j")) {
        Comanda_Uscita(7);
        client.println((const char*)index_min_html);
      }
      else if (req == "/")
      {
        client.println((const char*)index_min_html);
      }
    }
    client.println();
    client.stop();
    Serial.println("Chiuso client");
}
#endif
