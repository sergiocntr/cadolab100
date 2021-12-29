// ***************************
// IMPOSTAZIONI.H
// ***************************
#pragma once
#ifndef _impostazioni_h
#define _impostazioni_h
#include <debugutils.h>
#define DEBUGMIO
//#define DEBUGMIOSTRONG
//const char* ssid = "*****************";
//const char* password = "**********";
const char* ssid = "TIM-23836387";
const char* password = "51vEBuMvmALxNQHVIHQKkn52";
const uint8_t serverPort = 80;
const uint8_t wbsktPort = 75;
IPAddress local_IP(192, 168, 1, 74);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);
#endif