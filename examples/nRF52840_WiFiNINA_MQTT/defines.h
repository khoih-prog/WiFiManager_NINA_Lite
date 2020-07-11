/****************************************************************************************************************************
   defines.h for nRF52840_WiFiNINA_MQTT.ino
   For nRF52 boards using WiFiNINA modules/shields, using much less code to support boards with smaller memory

   WiFiManager_NINA_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
   (https://github.com/khoih-prog/WiFiManager_NINA_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
   configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

   Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_NINA_Lite
   Licensed under MIT license
   Version: 1.0.5

   Version Modified By   Date        Comments
   ------- -----------  ----------   -----------
   1.0.0   K Hoang      26/03/2020  Initial coding
   1.0.1   K Hoang      27/03/2020  Fix SAMD soft-reset bug. Add support to remaining boards
   1.0.2   K Hoang      15/04/2020  Fix bug. Add SAMD51 support.
   1.0.3   K Hoang      24/04/2020  Fix bug. Add nRF5 (Adafruit, NINA_B302_ublox, etc.) support. Add MultiWiFi, HostName capability.
                                    SSID password maxlen is 63 now. Permit special chars # and % in input data.
   1.0.4   K Hoang      04/05/2020  Add Configurable Config Portal Title, Default Config Data and DRD. Update examples.
   1.0.5   K Hoang      11/07/2020  Modify LOAD_DEFAULT_CONFIG_DATA logic. Enhance MultiWiFi connection logic. Add MQTT examples.       
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT Serial
#define WIFININA_DEBUG_OUTPUT     Serial

#define WIFININA_DEBUG            true

#define DRD_GENERIC_DEBUG         true

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

#include "WiFiNINA_Pinout_Generic.h"

#include <WiFiManager_NINA_Lite_NRF52840.h>

#define HOST_NAME   "nRF52-MQTT-Controller"

#ifdef LED_BUILTIN
#define LED_PIN     LED_BUILTIN
#else
#define LED_PIN     13
#endif

#endif      //defines_h
