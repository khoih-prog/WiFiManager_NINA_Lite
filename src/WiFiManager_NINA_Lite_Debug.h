/****************************************************************************************************************************
   WiFiManager_NINA_Lite_Debug.h
   For Mega, Teensy, SAM DUE, SAMD and STM32 boards using WiFiNINA modules/shields

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

#ifndef WiFiManager_NINA_Lite_Debug_h
#define WiFiManager_NINA_Lite_Debug_h

#if !defined(WIFININA_DEBUG)
  #define WIFININA_DEBUG    false
#endif

  // Use these to always display
  #define INFO_WM1(p1)                 { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.println(p1); }
  #define INFO_WM2(p1,p2)              { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.print(p1); \
                                          WIFININA_DEBUG_OUTPUT.println(p2); }
  #define INFO_WM3(p1,p2,p3)           { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.print(p1); \
                                          WIFININA_DEBUG_OUTPUT.print(p2); WIFININA_DEBUG_OUTPUT.println(p3); }
  #define INFO_WM4(p1,p2,p3,p4)        { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.print(p1); \
                                          WIFININA_DEBUG_OUTPUT.print(p2); WIFININA_DEBUG_OUTPUT.print(p3); WIFININA_DEBUG_OUTPUT.println(p4); }
  #define INFO_WM6(p1,p2,p3,p4,p5,p6)  { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.print(p1); \
                                          WIFININA_DEBUG_OUTPUT.print(p2); WIFININA_DEBUG_OUTPUT.print(p3); WIFININA_DEBUG_OUTPUT.print(p4); \
                                          WIFININA_DEBUG_OUTPUT.print(p5); WIFININA_DEBUG_OUTPUT.println(p6); }
                                          
#if WIFININA_DEBUG
  #define DEBUG_WM1(p1)                 { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.println(p1); }
  #define DEBUG_WM2(p1,p2)              { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.print(p1); \
                                          WIFININA_DEBUG_OUTPUT.println(p2); }
  #define DEBUG_WM3(p1,p2,p3)           { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.print(p1); \
                                          WIFININA_DEBUG_OUTPUT.print(p2); WIFININA_DEBUG_OUTPUT.println(p3); }
  #define DEBUG_WM4(p1,p2,p3,p4)        { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.print(p1); \
                                          WIFININA_DEBUG_OUTPUT.print(p2); WIFININA_DEBUG_OUTPUT.print(p3); WIFININA_DEBUG_OUTPUT.println(p4); }
  #define DEBUG_WM6(p1,p2,p3,p4,p5,p6)  { WIFININA_DEBUG_OUTPUT.print(F("*NN: ")); WIFININA_DEBUG_OUTPUT.print(p1); \
                                          WIFININA_DEBUG_OUTPUT.print(p2); WIFININA_DEBUG_OUTPUT.print(p3); WIFININA_DEBUG_OUTPUT.print(p4); \
                                          WIFININA_DEBUG_OUTPUT.print(p5); WIFININA_DEBUG_OUTPUT.println(p6); }
#else
  #define DEBUG_WM1(p1)
  #define DEBUG_WM2(p1,p2)
  #define DEBUG_WM3(p1,p2,p3)
  #define DEBUG_WM4(p1,p2,p3,p4)
  #define DEBUG_WM6(p1,p2,p3,p4,p5,p6)
#endif

#endif    //WiFiManager_NINA_Lite_Debug_h
