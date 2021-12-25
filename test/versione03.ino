/*
  CADOLAB100
  ESP32 DEV MODULE
  UPDATE SPEED: 230400
 */
#include "wifi.h"
#include "webserver.h"
void setup(void)
{  
  Serial.begin(9600);
  inizializza_wifi();
  startTime();
}

void loop(void)
{

  Pubblica_Web();
  tempoTrascorso();
  delay(10);
}