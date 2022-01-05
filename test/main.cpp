/*
  CADOLAB100
  
  UPDATE SPEED: 230400
 */
#include <main.h>
#ifdef ESP32
  #define USE_SPIFFS            true
  #define ESP_DRD_USE_EEPROM    true
  #define DRD_ADDRESS           1024
#else  
  // RTC Memory Address for the DoubleResetDetector to use
  #define DRD_ADDRESS 0
#endif

// Number of seconds after reset during which a 
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 5
DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);



void APRoutines(){
  //BUILT IN LED ACCESO -> MODALITA' AP
  Serial.println(loginSt);
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
#endif
bool check =true;  
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    loginSt = FS_FAIL_TO_LOAD;
    check=false;
  }
if(check)
{
  Serial.println("LittleFS ok ");
  loginSt = FS_LOAD_OK;
  if (drd.detectDoubleReset()) 
  {
    Serial.println("Double Reset Detected");
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
Serial.println("Prima del while : " + String(check));
if(check)  
{
  setupServer();
  setupWs();
  avvioda();
  
  blinkLed(loginSt);
  while(1){
  loopWS();
  tempoTrascorso();
  delay(10);
}
  
  }
}

void loop(void)
{

  
}