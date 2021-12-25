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
void tempoTrascorso(){
  if((millis()- tempo) >1000)
  {
    tempo=millis();
    sec++;
    
    if (sec>59) { sec=0; minuto++; }
    if (minuto>59) { minuto=0; ore++; }
    if (ore>23) { ore=0; giorni++;}
    
  }
}
void faipagina(){
        // int rssi = WiFi.RSSI();
        // String rssiPer;
        // if (rssi<-30&&rssi>-66) rssiPer = "100&#37;";
        // else if (rssi<-67&&rssi>-69) rssiPer = "90&#37;"; 
        // else if (rssi<-70&&rssi>-79) rssiPer = "30&#37;";
        // else if (rssi<-80&&rssi>-90) rssiPer = "10&#37;";
        // p = (String)intestazione;
        // for ( int q = 1; q < 9; q++ )
        //   {
            
        //     if (uscita[q]==1)            
        //       { 
        //         p+= "<button id=\"button" + String(q) + "menu\" href=\"#\" class=\"button button3\" type=\"button\" onclick= \"window.location.href='"; 
        //       }
        //     else
        //       { p+= "<button id=\"button" + String(q) + "menu\" href=\"#\" class=\"button button4\" type=\"button\" onclick= \"window.location.href='"; }
        //     p+= relcmd.charAt(q-1);
        //     p+= "'\" >";
        //     p+= myStringsOn[q-1];
        //     p+= "</button>";
        //   }        
        //   //p += (String)finePagina;
        //   p += (String)nom + String(NomeProg)+ String(prog) + String(Progetto) + String(vers) + String(Versione) + String(ss) + String(ssid) + String(rs) + String(rssi) + String(rsper) + rssiPer + String(fineTabella);
        //   p += (String)script;
        p=String(page);
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
        Serial.print("Richiesta non valida: ");
        Serial.println(req);
        return;
    }
    req = req.substring(addr_start + 1, addr_end);
    //Serial.print("Request: ");
    //Serial.println(req);
    
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
        //doc["nome"] = NomeProg;
        doc["vers"] = Versione;
        doc["tempo"] = String(giorni) + "d:" + normalize(ore) + "h:" + normalize(minuto) + "m";
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
    faipagina();
    }
    client.println();
    
    client.println(p);
    //client.println();
    client.stop();
    //Serial.println("Chiuso client");
}
#endif