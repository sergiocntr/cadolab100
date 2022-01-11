#pragma once
#ifndef _EEP_H
#define _EEP_H
#include <EEPROM.h>
#include <main.h>
void loadCredentials() {
  EEPROM.begin(512);
  EEPROM.get(0, loginCred);
  EEPROM.end();// loginSt= EP_READ_SUCCESS; else loginSt= EP_READ_FAIL;
  delay(10);
   #ifdef DEBUGMIO
    Serial.print("RECOVERED SSID: ");
    Serial.println(loginCred.ssid);
    Serial.print("Password: ");
    Serial.println(loginCred.passSsid); 
    Serial.print("RECOVERED USER: ");
    Serial.println(loginCred.usr);
    Serial.print("User Password: ");
    Serial.println(loginCred.passUsr); 
    Serial.println("Done");
  delay(10);
  #endif
}
/** Store WLAN credentials to EEPROM */
void saveCredentials() {
  EEPROM.begin(512);
  EEPROM.put(0, loginCred);
  if(EEPROM.commit()) loginSt= EP_WRITE_SUCCESS; else loginSt= EP_WRITE_FAIL;
  EEPROM.end();
  delay(100);
   #ifdef DEBUGMIO
    Serial.print("Saving SSID: ");
    Serial.println(loginCred.ssid);
    Serial.print("Password: ");
    Serial.println(loginCred.passSsid); 
    Serial.print("RECOVERED USER: ");
    Serial.println(loginCred.usr);
    Serial.print("User Password: ");
    Serial.println(loginCred.passUsr);
    Serial.println("VERIFICA: ");
    EEPROM.begin(512);
    EEPROM.get(0, loginCred);
    EEPROM.end() ;
    delay(10);
    Serial.print("STORED SSID: ");
    Serial.println(loginCred.ssid);
    Serial.print("STORED Password: ");
    Serial.println(loginCred.passSsid); 
    Serial.print("STORED USER: ");
    Serial.println(loginCred.usr);
    Serial.print("STORED User Password: ");
    Serial.println(loginCred.passUsr); 
    Serial.println("Done");
    delay(10);
  #endif
}
#endif