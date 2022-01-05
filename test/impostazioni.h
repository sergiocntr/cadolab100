#pragma once
#ifndef _impostazioni_h
#define _impostazioni_h
#define DEBUGMIO
const char* Progetto = "CADOLAB100";
const char* NomeProg = "RELE PASSO PASSO WEB";
const char* Versione = "ser wsocket 01";
//  QUESTE PASSWORD SONO HARD CODED
//  E ABILITANO IL LOGIN
//  
const char* ssidAP     = "ESP8266-Access-Point";
const char* passwordAP = "123456789";

/* PRIMA  LEGGE EEPROM
  SE NON C'E' ENTRA IN MODALITA INSERIMENTO SSID PASSWORD WIFI
  SI RIAVVIA
  SE NON SI COLLEGA AL WIFI ENTRA IN MODALITA INSERIMENTO SSID PASSWORD WIFI
  SE SI COLLEGA CHIEDE LA USER E PASS MESSA IN REGISTRAZIONE
  SE SI LOGGA VA ALLA INDEX.HTML
  SE NO MANDA IN NOT AUTH
*/
enum loginStates {
  INIT, 
  FS_FAIL_TO_LOAD,
  FS_LOAD_OK,
  DDR_DETECTED,       //abbiamo un doppio reset
  EP_READ_FAIL,     // lettura eeprom fallita
  EP_READ_SUCCESS,  // lettura eeprom ok
  EP_WRITE_FAIL,    // scrittura eeprom fallita
  EP_WRITE_SUCCESS, // scrittura eeprom ok
  WIFI_CONF_ERR,    // wificonfid error
  SSID_NOT_FOUND,   // ssid del file config non rilevato
  WIFI_NOT_CONN,    // password wifi sbagliata
  WIFI_AP_MODE,    // password wifi sbagliata
  WIFI_CONN_OK,     // collegato al wifi
  USER_NOT_FOUND,   // è stato inserito un user non memorizzato
  WRONG_PASSWORD,   // la password dell'user è sbagliata
  LOGIN_OK          // wifi connessa , utente loggato 
};

//struct accesso
struct loginCredential{
  char usr[30];
  char passUsr[30];
  char ssid[30];
  char passSsid[30];
};

//  **************************************************
//  SOTTO QUESTA LINEA NON SI DOVREBBE CAMBIARE NIENTE
//  **************************************************
#ifdef ESP32
  #define USE_SPIFFS            true
  #define ESP_DRD_USE_EEPROM    true
  #define DRD_ADDRESS           1024
#else  
  // RTC Memory Address for the DoubleResetDetector to use
  #define DRD_ADDRESS 0
#endif

// Number of seconds after reset during which a 
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 3
DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
bool uscita[9];
enum loginStates loginSt ;
loginCredential loginCred;

const uint8_t serverPort = 80;
const uint8_t wbsktPort = 75;
IPAddress local_IP(192, 168, 1, 74);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);
#endif