#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H
#pragma once
#include <Arduino.h>
//#define DEBUGMIO
  #if defined DEBUGMIO
  //#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
  #define DEBUG_PRINT(str)    \
     Serial.print(__LINE__);     \
     Serial.print(' ');      \
     Serial.println(str);
  #else
  #define DEBUG_PRINT(str)
  
  #endif

#endif