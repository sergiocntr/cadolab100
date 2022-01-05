#pragma once
#ifndef _eep_h
#define _eep_h
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

void loop() {
  drd.loop();
}
#endif