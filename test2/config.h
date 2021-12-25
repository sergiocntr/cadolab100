#pragma once
#ifndef _config100_h
#define _config100_h
#include <ArduinoJson.h>
#include "FS.h"
#include <LittleFS.h>

// more and possibly updated information can be found at:
// https://arduinojson.org/v6/example/config/

bool loadConfig(DynamicJsonDocument &doc) {
  File configFile = LittleFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }
  //DynamicJsonDocument doc(512);
  auto error = deserializeJson(doc, configFile);
  configFile.close();
  if (error) {
    Serial.println("Failed to parse config file");
    return false;
  }
    return true;
}
bool ConfigFile_Save_Variable(String VarName, String VarValue) {
  Serial.print("ConfigFile_Save_Variable: ");
  Serial.print(VarName); Serial.print("="); Serial.print(VarValue);

  File configFile = LittleFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("- failed to open config file for writing");
    return false;
  }

  DynamicJsonDocument doc(512);
  auto error =  deserializeJson(doc, configFile);
  if (error) {
    Serial.println("Failed to parse config file");
    return false;
  }
  serializeJson(doc, Serial);
  configFile.close();
  //
  doc[VarName] = VarValue;
  //
  configFile = LittleFS.open("/config.json", "w");
  serializeJson(doc, configFile);
  serializeJson(doc, Serial);
  configFile.close();
  Serial.println("");
  Serial.println(" - config.json saved - OK.");
  return true;
}
bool saveConfig(DynamicJsonDocument &doc) {
 File configFile = LittleFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  serializeJson(doc, configFile);
  configFile.close();
  return true;
}

bool setupFS() {
  //Serial.begin(115200);
  //Serial.println("");
  //delay(1000);
  //Serial.println("Mounting FS...");

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return false;
  }
  return true;

  
}
#endif