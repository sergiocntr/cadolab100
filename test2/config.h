
#pragma once
#ifndef _config_h
#define _config_h
#include <main.h>
bool readconfig() 
{
  if (SPIFFS.exists("/config.txt")) //se esiste
  {
    File file = SPIFFS.open("/config.txt", "r");//apre in lettura
    if (file) 
    {
      Serial.println("(RD-CFG) File aperto");
      StaticJsonDocument<512> doc;

  // Deserialize the JSON document
      DeserializationError error = deserializeJson(doc, file);
      if (error)
        Serial.println(F("Failed to read file, using default configuration"));

      // Copy values from the JsonDocument to the Config
      strlcpy(ssid,                  // <- destination
              doc["ssid"] | "apHotspot",  // <- source
              sizeof(ssid));         // <- destination's capacity
      strlcpy(password,                  // <- destination
              doc["ssidPass"] | "apHotspot",  // <- source
              sizeof(password));         // <- destination's capacity

      // Close the file (Curiously, File's destructor doesn't close the file)
      file.close();
      Serial.println("(RD-CFG) LETTURA OK");
      return true;
    } 
    else 
    { Serial.println("(RD-CFG) ERRORE LETTURA"); login = CONFIG_ERR_LET; return false; } //errore di lettura
  } 
  else 
  { Serial.println("(RD-CFG) FILE NON TROVATO"); login = CONFIG_NO_FILE; return false; }
}

// **************************************

bool saveconfig() //salva configurazione
{  
  File file=SPIFFS.open("/config.txt","w"); //Apre uin scrittura sovrascrivendo
  if (file) 
  {
   
    file.close();
    return true;
    //Serial.println("(SV-CFG) OK");
  } 
  else 
  {
    Serial.println("(SV-CFG) ERR");
    return false;
  }
}


// Loads the configuration from a file
void loadConfiguration(const char *filename, Config &config) {
  // Open file for reading
  File file = SD.open(filename);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
  config.port = doc["port"] | 2731;
  strlcpy(config.hostname,                  // <- destination
          doc["hostname"] | "example.com",  // <- source
          sizeof(config.hostname));         // <- destination's capacity

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}


bool saveWifiCredentials(){

File file=SPIFFS.open("/config.txt","w"); //Apre uin scrittura sovrascrivendo
  if (file) 
  {
   
    file.close();
    return true;
    //Serial.println("(SV-CFG) OK");
  } 
  else 
  {
    Serial.println("(SV-CFG) ERR");
    return false;
  }
  StaticJsonDocument<96> doc;
// Set the values in the document
  doc["ssid"] = ssid;
  doc["ssidPass"] = password;

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }
  file.close();
}
#endif