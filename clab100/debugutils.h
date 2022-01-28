#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H
#pragma once
#include <Arduino.h>
#include <main.h>
  #if defined DEBUGMIO
  //#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
  #define DEBUG_PRINT(str)    \
     Serial.print(__LINE__);     \
     Serial.print(' ');      \
     Serial.println(str);
  #else
  #define DEBUG_PRINT(str)
  
  #endif
void blinkLed(uint8_t volte){
  for (uint8_t i = 0; i < volte; i++)
  {
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(250);
  }
}
#endif