/*
  CADOLAB100
  
  UPDATE SPEED: 230400
 */
#include <main.h>
void setup(void)
{  
#ifdef DEBUGMIO
  Serial.begin(9600);
#endif
  if(inizializza_wifi()){
    blinkLed(2);
  };
  startTime();
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }else
  {
    Serial.println("LittleFS ok ");
  }
  setupServer();
  setupWs();
  avvioda();
}

void loop(void)
{

  loopWS();
  tempoTrascorso();
  delay(10);
}