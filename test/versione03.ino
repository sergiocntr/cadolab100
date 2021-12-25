/*
  CADOLAB100
  ESP32 DEV MODULE
  UPDATE SPEED: 230400
 */
#include "wifi.h"
#include "webserver.h"
void setup(void)
{  
#ifdef DEBUGMIO
  Serial.begin(9600);
#endif
  inizializza_wifi();
  startTime();
  avvioda();
}

void loop(void)
{

  Pubblica_Web();
  tempoTrascorso();
  delay(10);
}