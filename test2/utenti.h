#ifndef _utenti_h
#define _utenti_h
#include <main.h>

const char* fileUt = "/utenti.json";
File fileUtenti;
int checkUt=0;

int checkLogin(const String _utente,const String _password) 
{
  //DEBUG_PRINT(_utente);
  //return checkUt;
  if (!LittleFS.exists(fileUt)) //se non esiste
  {
    DEBUG_PRINT("(RD-UT) FILE NON TROVATO"); 
    return 1; //FILENONTROVATO
  }
  fileUtenti = LittleFS.open(fileUt, "r");//apre in lettura
  if (!fileUtenti) 
  {
    DEBUG_PRINT("(RD-UT) ERRORE Apertura File ");
    return checkUt;
  }
  delay(10);
  StaticJsonDocument<1024> doc;
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, fileUtenti);

  delay(10);
  if (error)
  {
    DEBUG_PRINT("(RD-UT) ERRORE JSON");
    delay(10);
    DEBUG_PRINT(error.c_str()); //errore di decodifica JSON;
    delay(10);
  }else
  {
    JsonArray arr = doc.as<JsonArray>();
      delay(10);
      DEBUG_PRINT("(RD-UT) LETTURA OK");
      for (JsonVariant value : arr) {
        //const char* name= value["ut"].as<char*>();
        //delay(10);
        const char* pass= value["pw"].as<const char*>();
        delay(10);
        //if(strcmp(_utente.c_str(),name)==0){
          delay(10);
          if(strcmp(_password.c_str(),pass)==0){
            delay(10);
            checkUt = value["id"].as<int>();
            DEBUG_PRINT("(RD-UT) UTENTE TROVATO");
            break;
        }
      delay(10);
    } 
  }    
  fileUtenti.close();
  return checkUt;
}
#endif