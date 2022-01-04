/*
  CADOLAB100
  ESP32 DEV MODULE
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
  setupServer();
  setupWs();
  avvioda();
}

void loop(void)
{

  loopServer();
  loopWS();
  tempoTrascorso();
  delay(10);
}