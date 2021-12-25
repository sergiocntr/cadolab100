#pragma once
#ifndef webser_h
#define webser_h
#include <Arduino.h>
#include <ArduinoJson.h>
#include "variabili.h"
#include "html.h"
uint8_t sec=0;
uint8_t minuto=0;
uint8_t ore=0;
uint8_t giorni=0;
uint32_t tempo;
String TempoTrascorso;
void Comanda_Uscita(uint8_t Numero)
{
  uscita[Numero]=! uscita[Numero];
}
void ResettaUscite()
{
  for (size_t i = 1; i < 9; i++)
  {
    uscita[i]=0;
  
  }
}
String normalize(uint8_t digit){
  String a="";
  if(digit < 10) return(" " + String(digit));
  else return String(digit);
}
void startTime(){
  tempo=millis();
}
void avvioda(){
  TempoTrascorso = String(giorni) + "d:" + normalize(ore) + "h:" + normalize(minuto) + "m";
}
void tempoTrascorso(){
  if((millis()- tempo) >1000)
  {
    tempo=millis();
    sec++;
    
    if (sec>59) { sec=0; minuto++; avvioda();
      #ifdef DEBUGMIO
      Serial.println("Avviato da " + TempoTrascorso);
      #endif
      }
    if (minuto>59) { minuto=0; ore++; }
    if (ore>23) { ore=0; giorni++;}
  }
}

void Pubblica_Web() 
{ 
    WiFiClient client = server.available();
    
    if (!client) 
    {
        return;
    }
    //Serial.println("");
    //Serial.println("New client");
    while(client.connected() && !client.available())
    {
        delay(1);
    }
    String req = client.readStringUntil('\r');
    uint8_t addr_start = req.indexOf(' ');
    uint8_t addr_end = req.indexOf(' ', addr_start + 1);
    if (addr_start == -1 || addr_end == -1) 
    {      
#ifdef DEBUGMIOSTRONG
  Serial.print("Richiesta non valida: ");
  Serial.println(req);
#endif
        
        return;
    }
    req = req.substring(addr_start + 1, addr_end);
#ifdef DEBUGMIOSTRONG
  Serial.print("Request: ");
  Serial.println(req);
#endif
    
    
    if(req == "/status"){
      //Serial.println("dentro status"); 
        //faiJson();
        DynamicJsonDocument doc(512);
        int rssi = WiFi.RSSI();
        
        if (rssi>-67) doc["rssiPer"] = "100%";
        else if (rssi<=-67 &&rssi>-70) doc["rssiPer"] = "90%"; 
        else if (rssi<=-70 &&rssi>-75) doc["rssiPer"] = "60%"; 
        else if (rssi<=-75 &&rssi>-80) doc["rssiPer"] = "30%";
        else if (rssi<=-80) doc["rssiPer"] = "10%";
        //String avvio = String(giorni) + "d:" + normalize(ore) + "h:" + normalize(minuto) + "m";;
        doc["vers"] = Versione;
        doc["tempo"] = TempoTrascorso;
        doc["ssid"] = ssid;
        doc["rssi"] = rssi;
        JsonArray puls = doc.createNestedArray("puls");
        for (size_t i = 1; i < 9; i++)
        {
          puls.add(uscita[i]); 
          //Serial.println(uscita[i]);
        }
        p="";   //reinizzializzo variabile
        serializeJson(doc, p);  //qui la pagina viene fatta dalla libreria arduinoJson
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:application/json");
#ifdef DEBUGMIOSTRONG
        serializeJsonPretty(doc,Serial);
#endif
        //client.println();
    }else{
    if (req.endsWith("/q")) Comanda_Uscita(1);
    else if (req.endsWith("/w")) Comanda_Uscita(2);
    else if (req.endsWith("/e")) Comanda_Uscita(3);
    else if (req.endsWith("/r")) Comanda_Uscita(4);
    else if (req.endsWith("/t")) Comanda_Uscita(5);
    else if (req.endsWith("/y")) Comanda_Uscita(6);
    else if (req.endsWith("/u")) Comanda_Uscita(7);
    else if (req.endsWith("/i"))  Comanda_Uscita(8);
    else if (req == "/reset")  ResettaUscite();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    //client.println();
    p=String(page);
    }
    client.println();
    
    client.println(p);
    //client.println();
    client.stop();
#ifdef DEBUGMIOSTRONG
      Serial.println("Chiuso client");
#endif
    //
}
#endif