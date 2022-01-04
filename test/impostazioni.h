#pragma once
#ifndef _impostazioni_h
#define _impostazioni_h
#define DEBUGMIO
/* PRIMA  LEGGE IL CONFIG
  SE NON C'E' ENTRA IN MODALITA INSERIMENTO SSID PASSWORD
  SI RIAVVIA
  SE NON SI COLLEGA AL WIFI ENTRA IN MODALITA INSERIMENTO SSID PASSWORD
  SE SI COLLEGA CHIEDE LA USER E PASS POCO QUI SOTTO
  SE SI LOGGA VA ALLA INDEX.HTML
*/
enum loginStates {
  EP_READ_FAIL, // lettura eeprom fallita
  EP_READ_SUCCESS, // il file è corrotto
  EP_WRITE_FAIL, // lettura eeprom fallita
  EP_WRITE_SUCCESS, // il file è corrotto
  SSID_NOT_FOUND, // ssid del file config non rilevato
  WIFI_NOT_CONN,  // password wifi sbagliata
  USER_NOT_FOUND, // è stato inserito un user non memorizzato
  WRONG_PASSWORD, // la password dell'user è sbagliata
  LOGIN_OK        //wifi connessa , utente loggato 
};

//struct accesso
struct loginCredential{
  char usr[30];
  char passUsr[30];
  char ssid[30];
  char passSsid[30];
};
//#define DEBUGMIOSTRONG
//  QUESTE PASSWORD SONO HARD CODED
//  E ABILITANO IL LOGIN
//  NON DOVREBBERO ESSERE admin admin ......
const char* http_username = "admin";
const char* http_password = "admin";
//
//  QUI SONO VALORI CHE VENGONO POPOLATI
//  NELLA LETTURA DEL CONFIG
//
const char* ssid     = "TIM-23836387";
const char* password= "51vEBuMvmALxNQHVIHQKkn52";
//char* ssid ;
//char* password ;
//
//  SOTTO QUESTA LINEA NON SI DOVREBBE CAMBIARE NIENTE
//
bool uscita[9];
const char* Progetto = "CADOLAB100";
const char* NomeProg = "RELE PASSO PASSO WEB";
const char* Versione = "ser wsocket 01";

const uint8_t serverPort = 80;
const uint8_t wbsktPort = 75;
IPAddress local_IP(192, 168, 1, 74);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);
#endif