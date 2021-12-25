#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>
#define INIT_LED LED_BUILTIN


// WiFi credentials
// ----------------

constexpr char WIFI_SSID[] = "your WiFi SSID";
constexpr char WIFI_PASS[] = "your WiFi password";

// Web server listening port
// -------------------------

constexpr uint16_t HTTP_PORT = 80;

// Serial monitor
// --------------

constexpr char PREAMBLE[] = R"PREAMBLE(

-------------------------------
ESP32 Web Controlled Thermostat
-------------------------------
   © 2020 Stéphane Calderoni
-------------------------------

-------------------------------
     Initialization process
-------------------------------
)PREAMBLE";

constexpr char CLOSING[] = "\n-------------------------------\n";

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------
uint32_t startRead;      // -> start time of reading

// Firmware operating modules
// --------------------------

AsyncWebServer server(HTTP_PORT); // -> Web server

// ----------------------------------------------------------------------------
// Initialization procedures
// ----------------------------------------------------------------------------

// Serial monitor initialization
// -----------------------------

void initSerial() {
    Serial.begin(115200);
    delay(500);
    Serial.println(PREAMBLE);
}

// LED indicator initialization
// ----------------------------

void initLEDs() {
    pinMode(INIT_LED, OUTPUT);
    pinMode(TEMP_LED, OUTPUT);
    Serial.println(F("1. LED indicators activated"));
}



// SPIFFS initialization
// ---------------------

/**
 * The web user interface will be stored on the ESP32 Flash memory file system
 * as 5 separate files :
 * - index.html  (the interface structure)
 * - index.css   (the graphical layout of the interface)
 * - index.js    (the dynamic interface management program)
 * - D7MR.woff2  (the font used for numeric displays)
 * - favicon.ico (the tiny icon for the browser)
 */

void initSPIFFS() {
    if (!LittleFS.begin()) {
        Serial.println(F("Cannot mount LittleFS volume..."));
        while(1) digitalWrite(INIT_LED, millis() % 200 < 20 ? HIGH : LOW);
    }
    Serial.println(F("5. LittleFS volume is mounted"));
}

// WiFi connection initialization
// ------------------------------

/**
 * A connection to the ambient WiFi network is required here to be able to
 * interact with an operator (who will access ESP32 through a web browser).
 */

void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.printf("6. Trying to connect to [%s] network ", WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.printf("\n7. Connected! => %s\n", WiFi.localIP().toString().c_str());
}


// ----------------------------------------------------------------------------
// HTTP route definition & request processing
// ----------------------------------------------------------------------------


String processor(const String &var)
{
    if (var == "PROGNR") {
       return String(Progetto, 1);
    } else if (var == "MIN_TEMP") {
        return String(MIN_TEMP, 1);
    } else if (var == "MAX_TEMP") {
        return String(MAX_TEMP, 1);
    } else if (var == "LOWER_TEMP") {
        return String(tempRange.lower, 1);
    } else if (var == "UPPER_TEMP") {
        return String(tempRange.upper, 1);
    }
    return String();
}

void onRootRequest(AsyncWebServerRequest *request) {
    request->send(FS, "/index.html", "text/html", false, processor);
}

// Method of fallback in case no request could be resolved
// -------------------------------------------------------

void onNotFound(AsyncWebServerRequest *request) {
    request->send(404);
}

// Sensor temperature reading query manager
// ----------------------------------------

void onTemp(AsyncWebServerRequest *request) {
    Serial.println(F("Received temperature request\n-> Performs a sensor reading"));
    float_t temp = readTemperature();
    
    if (isnan(temp)) {
        Serial.println(F("** Failed to read from DHT sensor!\n"));
        request->send(200, "text/plain", String("Error"));
    } else {
        checkForTriggers(temp);
        Serial.print(F("-> DHT sensor readout: "));
        Serial.printf("%.1f°C\n", temp);
        Serial.println(F("-> Sends the data back to the client\n"));
        request->send(200, "text/plain", String(temp));
    }
}

// Factory reset
// -------------

void onReset(AsyncWebServerRequest *request) {
    // No point in writing in the EEPROM if it's never been done before...
    if (tempRange.initialized) {
        EEPROM.writeByte(ADDR_INIT_FLAG, 0xff);
        EEPROM.commit();
    }

    tempRange.initialized = false;
    tempRange.lower       = MIN_TEMP;
    tempRange.upper       = MAX_TEMP;

    Serial.println(F("\nFactory reset\n"));
    Serial.print(F("-> Temperature range is set to "));
    Serial.printf("[ %.1f°C , %.1f°C ]\n\n", tempRange.lower, tempRange.upper);

    // Requests are asynchronous and must always be resolved:
    request->send(200);
}

// ESP32 restart request manager
// -----------------------------

void onReboot(AsyncWebServerRequest *request) {
    // Requests are asynchronous and must always be resolved:
    request->send(200);

    Serial.println(CLOSING);
    Serial.println(F("Rebooting...\n"));
    Serial.flush();
    ESP.restart();
}

// Manager for queries to define the temperature range set by the operator
// -----------------------------------------------------------------------

void onSaveThresholds(AsyncWebServerRequest *request) {
    if (request->hasParam("lower") && request->hasParam("upper")) {
        float_t lower = request->getParam("lower")->value().toFloat();
        float_t upper = request->getParam("upper")->value().toFloat();
        Serial.printf("Temperature range received: [ %.1f°C , %.1f°C ]\n", lower, upper);
        saveTempRangeToEEPROM(lower, upper);
    }

    // Requests are asynchronous and must always be resolved:
    request->send(200);
}

// Definition of request handlers and server initialization
// --------------------------------------------------------

/**
 * This is where we will define the HTTP routes of the application,
 * as well as the handlers associated with each route.
 */

void initWebServer() {

    // Routes that simply return one of the files present on SPIFFS:

    /*
     * for some reason, this doesn't work:
     * -> server.serveStatic("/", SPIFFS, "/index.html");
     *
     * but this does:
     * -> server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
     *
     * and this messes up the rendering in the browser:
     * -> server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html").setTemplateProcessor(processor);
     *
     * So, I prefer to fall back on the classic method:
     */
    server.on("/", onRootRequest);

    server.serveStatic("/index.js",    SPIFFS, "/index.js");
    server.serveStatic("/index.css",   SPIFFS, "/index.css");
    server.serveStatic("/D7MR.woff2",  SPIFFS, "/D7MR.woff2");
    server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico");

    server.onNotFound(onNotFound);

    // Routes that correspond to dynamic processing by the microcontroller:

    server.on("/temp",           onTemp);
    server.on("/reset",          onReset);
    server.on("/reboot",         onReboot);
    server.on("/savethresholds", onSaveThresholds);

    // Server initialization

    server.begin();
    Serial.println(F("8. Web server started"));
}

// ----------------------------------------------------------------------------
// General initialization procedure
// ----------------------------------------------------------------------------

// Each module is initialized in turn, in a precise order:

void setup() {
    initSerial();
    initLEDs();
    initEEPROM();
    initTempRange();
    initTempSensor();
    initSPIFFS();
    initWiFi();
    initWebServer();

    Serial.println(CLOSING);
}

// ----------------------------------------------------------------------------
// LED indicator handlers
// ----------------------------------------------------------------------------

// WiFi connection indicator
// -------------------------

void flashWiFiBeacon() {
    digitalWrite(INIT_LED, millis() % 2000 < 50 ? HIGH : LOW);
}

// DHT reading indicator
// ---------------------

void flashTempBeacon() {
    if (readingTemperature) {
        readingTemperature = millis() - startRead < 50;
        digitalWrite(TEMP_LED, readingTemperature ? HIGH : LOW);
    }
}

// ----------------------------------------------------------------------------
// Main control loop
// ----------------------------------------------------------------------------

/**
 * All processing that is the responsibility of the web server is carried out
 * asynchronously. There is therefore not much to do in the main loop, except
 * to manage the operation of the LEDs.
 */

void loop() {
    flashWiFiBeacon();
    flashTempBeacon();
}