/****************************************************************************************************************************
   defines.h for Teensy40_WiFiNINA_MQTT.ino
   For Teensy boards using WiFiNINA modules/shields, using much less code to support boards with smaller memory

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

#define WIFININA_DEBUG            false //true

#define DRD_GENERIC_DEBUG         false //true

#if ( defined(ESP8266) || defined(ESP32) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) || !defined(CORE_TEENSY) )
#error This code is intended to run on Teensy platform! Please check your Tools->Board setting.
#endif

#ifdef CORE_TEENSY

#if defined(__IMXRT1062__)
// For Teensy 4.0
#define BOARD_TYPE      "TEENSY 4.0"
#elif defined(__MK66FX1M0__)
#define BOARD_TYPE "Teensy 3.6"
#elif defined(__MK64FX512__)
#define BOARD_TYPE "Teensy 3.5"
#elif defined(__MKL26Z64__)
#define BOARD_TYPE "Teensy LC"
#elif defined(__MK20DX256__)
#define BOARD_TYPE "Teensy 3.2" // and Teensy 3.1 (obsolete)
#elif defined(__MK20DX128__)
#define BOARD_TYPE "Teensy 3.0"
#elif defined(__AVR_AT90USB1286__)
#error Teensy 2.0++ not supported yet
#elif defined(__AVR_ATmega32U4__)
#error Teensy 2.0 not supported yet
#else
// For Other Boards
#define BOARD_TYPE      "Unknown Teensy Board"
#endif
#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START     0

#include "WiFiNINA_Pinout_Generic.h"

#include <WiFiManager_NINA_Lite_Teensy.h>

#define HOST_NAME   "Teensy-Master-Controller"

#ifdef LED_BUILTIN
#define LED_PIN     LED_BUILTIN
#else
#define LED_PIN     13
#endif


#endif      //defines_h
