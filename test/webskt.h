#pragma once
#ifndef webskt_h
#define webskt_h
#include <main.h>
WebSocketsServer webSocket = WebSocketsServer(wbsktPort);

uint8_t sec=0;
uint8_t minuto=0;
uint8_t ore=0;
uint8_t giorni=0;
uint32_t tempo=0;
String TempoTrascorso;
// The JSON library uses static memory, so this will need to be allocated:

StaticJsonDocument<128> doc_rx;
void Comanda_Uscita(uint8_t Numero)
{
  StaticJsonDocument<384> doc_tx;                       // provision memory for about 200 characters
  uscita[Numero]=! uscita[Numero];
  //ogni volta che si comanda una uscita bisogna mandare il websocket di avviso
  doc_tx["type"] = "bt_esp";  //tipo comunicazione
  doc_tx["gr"] = Numero-1;      //gruppo
  doc_tx["value"] = uscita[Numero]; //stato
  String jsonString = "";
  serializeJson(doc_tx, jsonString);                // convert JSON object to string
  webSocket.broadcastTXT(jsonString);               // send JSON string to all clients
}

void ResettaUscite()
{
  for (size_t i = 1; i < 9; i++)
  {
    uscita[i]=0;
  }
  StaticJsonDocument<384> doc_tx;                       // provision memory for about 200 characters
  doc_tx["type"] = "resetP_esp";
  String jsonString = "";
  serializeJson(doc_tx, jsonString);                // convert JSON object to string
  webSocket.broadcastTXT(jsonString);               // send JSON string to all clients
  #ifdef DEBUGMIO
    DEBUG_PRINT("Inviato WS" + jsonString);
  #endif
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
  StaticJsonDocument<384> doc_tx;                       // provision memory for about 200 characters
  doc_tx["type"] = "tempo_esp";
  int rssi = WiFi.RSSI();
  doc_tx["rssi"] = rssi;
  if (rssi>-67) doc_tx["rssiPer"] = "100%";
  else if (rssi<=-67 &&rssi>-70) doc_tx["rssiPer"] = "90%"; 
  else if (rssi<=-70 &&rssi>-75) doc_tx["rssiPer"] = "60%"; 
  else if (rssi<=-75 &&rssi>-80) doc_tx["rssiPer"] = "30%";
  else if (rssi<=-80) doc_tx["rssiPer"] = "10%";
  TempoTrascorso = String(giorni) + "d:" + normalize(ore) + "h:" + normalize(minuto) + "m";
  doc_tx["tempo"] = TempoTrascorso;
  String jsonString = "";
  serializeJson(doc_tx, jsonString);                // convert JSON object to string
  webSocket.broadcastTXT(jsonString);               // send JSON string to all clients
  #ifdef DEBUGMIO
    DEBUG_PRINT("Inviato WS " + jsonString);
  #endif
}
void tempoTrascorso(){
  if((millis()- tempo) >1000)
  {
    tempo=millis();
    sec++;
    bool update=false;
    if (sec>59) { sec=0; minuto++; update=true;
      #ifdef DEBUGMIO
      DEBUG_PRINT("Avviato da " + TempoTrascorso);
      #endif
      }
    if (minuto > 59) { minuto = 0; ore++; }
    if (ore > 23) { ore = 0; giorni++;}
    if(update) avvioda();
  }
}
void jsonConn(String& s) {
    //String avvio = String(giorni) + "d:" + normalize(ore) + "h:" + normalize(minuto) + "m";;
    StaticJsonDocument<384> doc_tx;                       // provision memory for about 200 characters
    doc_tx["type"] = "conn_esp";
    doc_tx["vers"] = Versione;
    doc_tx["tempo"] = "appena avviato";
    doc_tx["ssid"] = loginCred.ssid;
    JsonArray puls = doc_tx.createNestedArray("puls");
    for (size_t i = 1; i < 9; i++)
    {
      puls.add(uscita[i]); 
    }
    serializeJson(doc_tx, s); // convert JSON object to string
}
void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length) {      // the parameters of this callback function are always the same -> num: id of the client who send the event, type: type of message, payload: actual data sent and length: length of payload
  switch (type) {                                     // switch on the type of information sent
    case WStype_DISCONNECTED:                         // if a client is disconnected, then type == WStype_DISCONNECTED
    {
      #ifdef DEBUGMIO
        DEBUG_PRINT("Client " + String(num) + " disconnected");
      #endif
      delay(10);
      break;
    } 
    case WStype_CONNECTED:
    {                            // if a client is connected, then type == WStype_CONNECTED
      #ifdef DEBUGMIO
      DEBUG_PRINT("Client " + String(num) + " connected");
      #endif
      
      // in caso di connessione si mandano i vari campi al clien che si è connesso
      String str="";
      jsonConn(str);
      webSocket.sendTXT(num, str); //nuova connessione,mando i campi al nuovo client connesso
      #ifdef DEBUGMIO
        DEBUG_PRINT("Inviato WS " + str + " al client " + String(num));
      #endif
      break;
    }
    case WStype_TEXT:
    {                                 // if a client has sent data, then type == WStype_TEXT
      // try to decipher the JSON string received
      DeserializationError error = deserializeJson(doc_rx, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      else {
        // JSON string was received correctly, so information can be retrieved:
        const char* l_type = doc_rx["type"];  //questo è il tipo di informazione ,per adesso nel JS c'è solo 'bt'
        const int l_value = doc_rx["value"];
        #ifdef DEBUGMIO
        String rx="";
        serializeJson(doc_rx,rx);
          DEBUG_PRINT("Ricevuto WS: " + rx);
        #endif
        if(String(l_type) == "bt") {
          Comanda_Uscita(l_value);
        }
         else if(String(l_type) == "btreset") {
          ResettaUscite();
        }
      }
      #ifdef DEBUGMIO
      DEBUG_PRINT("");
      #endif
      
      break;
    }
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_PING:
    case WStype_PONG:
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
		break;
  }
}


void setupWs(){
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
void loopWS(){
  webSocket.loop();    // Update function for the webSockets 
}
#endif