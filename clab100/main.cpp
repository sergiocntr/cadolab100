
#include <main.h>
void APRoutines(){
  //BUILT IN LED ACCESO -> MODALITA' AP
  DEBUG_PRINT(loginSt);
  delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    loginSt = WIFI_AP_MODE;
    delay(10);
    setAPMode();      //WIFI AP MODE ON
    setupAPServer();  //SERVER FOR LOGIN CREDENTIALS


}
void setup(void)
{
  pinMode(LED_BUILTIN,OUTPUT) ;
  digitalWrite(LED_BUILTIN, HIGH);
#ifdef DEBUGMIO
  Serial.begin(9600);
  DEBUG_PRINT("");
  delay(20);
#endif
bool check =true;  
  if(!SPIFFS.begin()){
    DEBUG_PRINT("-> An Error has occurred while mounting LittleFS");
    loginSt = FS_FAIL_TO_LOAD;
    check=false;
  }
if(check)
{
  DEBUG_PRINT("1 LittleFS ok ");
  loginSt = FS_LOAD_OK;
  if (drd.detectDoubleReset()) 
  {
    DEBUG_PRINT("Double Reset Detected");
    loginSt = DDR_DETECTED;
    blinkLed(loginSt);
    delay(1000);
    //->AP Mode
    APRoutines();
    check=false;
  }
}
if(check)
{
  startTime();
//
// RECUPERO CREDENZIALI
//
  loadCredentials();
  if(!inizializza_wifi()) 
  {
    //-> AP mode
    APRoutines();
    check=false;
  }
}
DEBUG_PRINT("Prima del while : " + String(check));
if(check)  
{
  setupServer();
  setupWs();
  avvioda();
  delay(10);
  blinkLed(loginSt);
  while(1){
    //loopWS();
    //delay(5);
    tempoTrascorso();
    delay(10);
    #ifdef ESP8266
    MDNS.update();
    #endif
  }
  
  }
}

void loop(void)
{

  
}