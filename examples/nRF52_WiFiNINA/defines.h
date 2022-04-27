/****************************************************************************************************************************
  defines.h for nRF52840_WiFiNINA.ino
  For nRF52 boards using WiFiNINA modules/shields, using much less code to support boards with smaller memory
  
  WiFiManager_NINA_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_NINA_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.
  
  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_NINA_Lite
  Licensed under MIT license     
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT       Serial
#define WIFININA_DEBUG_OUTPUT           Serial

#define _WIFININA_LOGLEVEL_             1
#define _WIFIMULTI_LOGLEVEL_            1

#define DRD_GENERIC_DEBUG               true

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) )
  #if defined(WIFININA_USE_NRF528XX)
    #undef WIFININA_USE_NRF528XX
    #undef WIFI_USE_NRF528XX
  #endif
  #define WIFININA_USE_NRF528XX      true
  #define WIFI_USE_NRF528XX          true
#else
  #error This code is intended to run only on the NRF528XX boards ! Please check your Tools->Board setting.
#endif


#if defined(WIFININA_USE_NRF528XX)

  #if defined(NRF52840_FEATHER)
    #define BOARD_TYPE      "NRF52840_FEATHER"
  #elif defined(NRF52832_FEATHER)
    #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
    #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
    #define BOARD_TYPE      "NRF52840_ITSYBITSY"
  #elif defined(NRF52840_CIRCUITPLAY)
    #define BOARD_TYPE      "NRF52840_CIRCUITPLAY"
  #elif defined(NRF52840_CLUE)
    #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
    #define BOARD_TYPE      "NRF52840_METRO"
  #elif defined(NRF52840_PCA10056)
    #define BOARD_TYPE      "NRF52840_PCA10056"
  #elif defined(PARTICLE_XENON)
    #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(NINA_B302_ublox)
    #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
    #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #elif defined(NRF52_SERIES)
    #define BOARD_TYPE      "NRF52_SERIES"
  #else
    #define BOARD_TYPE      "NRF52 Unknown"
  #endif

#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START

/////////////////////////////////////////////

// Add customs headers from v1.1.0
#define USING_CUSTOMS_STYLE           true
#define USING_CUSTOMS_HEAD_ELEMENT    true
#define USING_CORS_FEATURE            true

/////////////////////////////////////////////

#define USE_WIFI_NINA                 true
#define USE_WIFI101                   false
#define USE_WIFI_CUSTOM               false

#if USE_WIFI_NINA

  #warning Using WIFININA_Generic Library
  #define SHIELD_TYPE     "WiFiNINA using WiFiNINA_Generic Library"

  #include "WiFiNINA_Pinout_Generic.h"
  
#elif USE_WIFI101

  #if defined(USE_WIFI_NINA)
    #undef USE_WIFI_NINA
  #endif
  
  #define USE_WIFI_NINA           false

  #define SHIELD_TYPE     "WINC1500 using WiFi101 Library"
  #warning Using WiFi101 Library

#elif USE_WIFI_CUSTOM

  #if defined(USE_WIFI_NINA)
    #undef USE_WIFI_NINA
  #endif
  
  #define USE_WIFI_NINA           false
  
  #if defined(USE_WIFI101)
    #undef USE_WIFI101
  #endif
  
  #define USE_WIFI101             false

  #define SHIELD_TYPE     "Custom using Custom WiFi Library"
  #warning Using Custom WiFi Library. You must include here or compile error
  
#else

  #define SHIELD_TYPE     "Default WiFi using WiFi Library"
  #warning Using fallback WiFi.h Library defined in WiFiWebServer Library.
  
#endif

/////////////////////////////////////////////

// Permit running CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET times before reset hardware
// to permit user another chance to config. Only if Config Data is valid.
// If Config Data is invalid, this has no effect as Config Portal will persist
#define RESET_IF_CONFIG_TIMEOUT                   true

// Permitted range of user-defined RETRY_TIMES_RECONNECT_WIFI between 2-5 times
#define RETRY_TIMES_RECONNECT_WIFI                3

// Permitted range of user-defined CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET between 2-100
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

// Config Timeout 120s (default 60s). Applicable only if Config Data is Valid
#define CONFIG_TIMEOUT                      120000L

// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW             false

// Max times to try WiFi per loop() iteration. To avoid blocking issue in loop()
// Default 1 if not defined, and minimum 1.
//#define MAX_NUM_WIFI_RECON_TRIES_PER_LOOP     2

// Default no interval between recon WiFi if lost
// Max permitted interval will be 10mins
// Uncomment to use. Be careful, WiFi reconnect will be delayed if using this method
// Only use whenever urgent tasks in loop() can't be delayed. But if so, it's better you have to rewrite your code, e.g. using higher priority tasks.
//#define WIFI_RECON_INTERVAL                   30000

// Default no interval between recon WiFi if lost
// Max permitted interval will be 10mins
// Uncomment to use. Be careful, WiFi reconnect will be delayed if using this method
// Only use whenever urgent tasks in loop() can't be delayed. But if so, it's better you have to rewrite your code, e.g. using higher priority tasks.
//#define WIFI_RECON_INTERVAL                   30000

/////////////////////////////////////////////

#define USE_DYNAMIC_PARAMETERS              true

/////////////////////////////////////////////

#define SCAN_WIFI_NETWORKS                  true

// To be able to manually input SSID, not from a scanned SSID lists
#define MANUAL_SSID_INPUT_ALLOWED           true

// From 2-15
#define MAX_SSID_IN_LIST                    6

/////////////////////////////////////////////

// Optional, to use Board Name in Menu
#define USING_BOARD_NAME                    true

/////////////////////////////////////////////

// Optional, to use Board Name in Menu
#define USING_CONFIG_MODE_LED               true

#if USING_CONFIG_MODE_LED
  #if defined(LED_BUILTIN)
    #define CONFIG_MODE_LED     LED_BUILTIN
  #else
    // Using default pin 13 for CONFIG_MODE_LED. To be changed as necessary
    #define CONFIG_MODE_LED     13
  #endif

  #define LED_ON      HIGH
  #define LED_OFF     LOW
#endif

/////////////////////////////////////////////

#include <WiFiManager_NINA_Lite_nRF52.h>

#define HOST_NAME   "nRF52-Master-Controller"

#endif      //defines_h
