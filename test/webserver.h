#pragma once
#ifndef webser_h
#define webser_h
#include <Arduino.h>
#include <ArduinoJson.h>
#include "variabili.h"
#include "html.h"
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
void faipagina(){
        
        p = (String)intestazione;
        for ( int q = 1; q < 9; q++ )
          {
            
            if (uscita[q]==1)            
              { 
                p+= "<button id=\"button" + String(q) + "menu\" href=\"#\" class=\"button button3\" type=\"button\" onclick= \"window.location.href='"; 
              }
            else
              { p+= "<button id=\"button" + String(q) + "menu\" href=\"#\" class=\"button button4\" type=\"button\" onclick= \"window.location.href='"; }
            p+= relcmd[q * 2];
            p+= "'\" >";
            p+= myStringsOn[q-1];
            p+= "</button>";
          }        
          p += (String)finePagina;
          p += (String)script;
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
    
    if(req == "/status"){
      Serial.println("dentro status"); 
        //faiJson();
        DynamicJsonDocument doc(384);
        int rssi = WiFi.RSSI();
        if (rssi<-30&&rssi>-66) doc["rssiPer"] = "100%";
        else if (rssi<-67&&rssi>-69) doc["rssiPer"] = "90%"; 
        else if (rssi<-70&&rssi>-79) doc["rssiPer"] = "30%";
        else if (rssi<-80&&rssi>-90) doc["rssiPer"] = "10%";
        doc["nome"] = NomeProg;
        doc["prog"] = Progetto;
        doc["vers"] = Versione;
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
    }else{
    if (req.endsWith("/e")) Comanda_Uscita(1);
    else if (req.endsWith("/t")) Comanda_Uscita(2);
    else if (req.endsWith("/u")) Comanda_Uscita(3);
    else if (req.endsWith("/o")) Comanda_Uscita(4);
    else if (req.endsWith("/a")) Comanda_Uscita(5);
    else if (req.endsWith("/d")) Comanda_Uscita(6);
    else if (req.endsWith("/g")) Comanda_Uscita(7);
    else if (req.endsWith("/j"))  Comanda_Uscita(8);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    faipagina();
    }
    client.println();
    client.println();
    client.println(p);
    client.println();
    client.stop();
    Serial.println("Chiuso client");
}
#endif