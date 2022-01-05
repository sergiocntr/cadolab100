#pragma once
#ifndef webser_h
#define webser_h
#include <main.h>
#include <eep.h>

AsyncWebServer server(serverPort);    
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
#pragma region STA
void setupServer(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(loginCred.usr, loginCred.passUsr))
      return request->requestAuthentication();
    request->send(SPIFFS, "/index.html", "text/html");
    // request->send(200, "text/plain", "Hello, world");
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  // Route to load index.js file
  server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.js", "text/javascript");
  });
  server.onNotFound(notFound);
  server.begin();

}
#pragma endregion STA
//
//--------------------------------------------------------------------------------
#pragma region AP
void setupAPServer(){
  //COME ROOT MOSTRO LA FORM PER L'INSERIMENTO DEL SSID E PASSWORD
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/login.html", "text/html");
    });
    // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  //SE C'E' IL SUBMIT DELLA FORM VERIFICO I CAMPI E MEMORIZZO SSID E PASSWORD
  server.on("/accesso", HTTP_POST, [](AsyncWebServerRequest *request){
    const char* USER_MESSAGE ="us";
    const char* PASSUSR_MESSAGE ="pa";
    const char* SSID_MESSAGE ="ssid";
    const char* PASSSSID_MESSAGE ="wifipa";
    if ((request->hasParam(USER_MESSAGE, true)) && (request->hasParam(PASSSSID_MESSAGE, true))) {
      const String _passWifi= request->getParam(PASSSSID_MESSAGE, true)->value();
      const String _ssid= request->getParam(SSID_MESSAGE, true)->value();
      const String _usr= request->getParam(USER_MESSAGE, true)->value();
      const String _passUsr= request->getParam(PASSUSR_MESSAGE, true)->value();
      delay(10);
      strcpy(loginCred.ssid, _ssid.c_str());
      strcpy(loginCred.passSsid, _passWifi.c_str());
      strcpy(loginCred.usr , _usr.c_str());
      strcpy(loginCred.passUsr, _passUsr.c_str());
      delay(10);
      saveCredentials();
      //MOSTRO A SCHERMO L'INVITO A RIAVVIARE IL NODE PER CONNETTERSI ALLA RETE WIFI APPENA REGISTRATA
      request->send_P(200, "text/html", "<h2>OK! RIAVVIA </h2>");
      ESP.restart();
    } else {
      //SE NON HA I PARAMETRI TORNA ALLA FORM DI INSERIMENTO
      request->send(SPIFFS, "/login.html", "text/html");
    }
  });
  server.onNotFound(notFound);
  server.begin();
}
#pragma endregion AP
#endif

