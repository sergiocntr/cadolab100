#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DoubleResetDetector.h>

#include <pagine.h>
#include <wifi.h>
#include <eep.h>
// Number of seconds after reset during which a 
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 3
// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0
DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);

//QUESTO E' LA STRUCT PER LA MEMORIZZAZIONE E RECUPERO DEI DATI
wificredential login;

//QUESTI SONO I NOMI DEI CAMPI DELLA FORM HTML
const char* USER_MESSAGE = "us";  //USATO PER LOGIN UTENTE /SSID UTENTE
const char* PASSWORD_MESSAGE = "pa"; //USATO PER LOGIN UTENTE / PASSWORD WIFI UTENTE

AsyncWebServer server(80);
void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  if (drd.detectDoubleReset()) {
    Serial.println("Double Reset Detected");
    processWifiSetup();
    
  } else {

    Serial.println("No Double Reset Detected");
    digitalWrite(LED_BUILTIN, HIGH);
    //RECUPERO SSID E PASSWORD DALLA EEPROM
    loadCredentials(login);
    const char* _ssid = login.ssid;
    const char* _pw = login.pass;
    delay(10);
    SetupWifi(_ssid,_pw);

  }
   // Start server
  server.begin();
}
void processWifiSetup(){
  //SE DOPPIO RESET MOSTRO LA PAGINA PER REGISTRARE SSID E PASSWORD
    
    //BUILT IN LED ACCESO -> MODALITA' AP
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
    //ABILITO AP MODE NELL ESP
    setApMode();
    delay(10);
    //COME ROOT MOSTRO LA FORM PER L'INSERIMENTO DEL SSID E PASSWORD
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", setWifi_html);
      });
    //SE C'E' IL SUBMIT DELLA FORM VERIFICO I CAMPI E MEMORIZZO SSID E PASSWORD
    server.on("/accesso", HTTP_POST, [](AsyncWebServerRequest *request){
      if ((request->hasParam(USER_MESSAGE, true)) && (request->hasParam(PASSWORD_MESSAGE, true))) {
          const String _passWifi= request->getParam(PASSWORD_MESSAGE, true)->value();
          const String _ssid= request->getParam(USER_MESSAGE, true)->value();
          delay(10);
          strcpy(login.ssid, _ssid.c_str());
          strcpy(login.pass, _passWifi.c_str());
          delay(10);
          saveCredentials(login);
          //MOSTRO A SCHERMO L'INVITO A RIAVVIARE IL NODE PER CONNETTERSI ALLA RETE WIFI APPENA REGISTRATA
          request->send_P(200, "text/html", "<h2>OK! RIAVVIA IL NODE</h2>");
      } else {
          //SE NON HA I PARAMETRI TORNA ALLA FORM DI INSERIMENTO
          request->send_P(200, "text/html", setWifi_html);
      }
    });
}
void loop() {
  drd.loop();
}