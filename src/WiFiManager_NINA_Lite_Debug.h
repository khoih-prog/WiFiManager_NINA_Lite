/*********************************************************************************************************************************
  WiFiManager_NINA_Lite_Debug.h
  For Mega, Teensy, SAM DUE, SAMD and STM32 boards using WiFiNINA modules/shields

  WiFiManager_NINA_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_NINA_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_NINA_Lite
  Licensed under MIT license
  Version: 1.6.3

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      26/03/2020  Initial coding
  ...
  1.6.0   K Hoang      05/01/2022  Configurable WIFI_RECON_INTERVAL. Add support to RP2040 using arduino-pico core
  1.6.1   K Hoang      26/01/2022  Update to be compatible with new FlashStorage libraries. Add support to more SAMD/STM32 boards
  1.6.2   K Hoang      18/02/2022  Optional Board_Name in Menu. Optimize code by using passing by reference
  1.6.3   K Hoang      20/02/2022  Add optional CONFIG_MODE_LED. Add function to
  **********************************************************************************************************************************/

#ifndef WiFiManager_NINA_Lite_Debug_h
#define WiFiManager_NINA_Lite_Debug_h

#if !defined(WIFININA_DEBUG)
  #define WIFININA_DEBUG    false
#endif

#ifdef WIFININA_DEBUG_OUTPUT
  #define DBG_PORT_WN       WIFININA_DEBUG_OUTPUT
#else
  #define DBG_PORT_WN       Serial
#endif

// Change _WIFININA_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _WIFININA_LOGLEVEL_
  #define _WIFININA_LOGLEVEL_       0
#endif

//////////////////////////////////////////

const char WN_MARK[] = "[WN] ";

#define WN_PRINT_MARK   DBG_PORT_WN.print(WN_MARK)

#define WN_PRINT        DBG_PORT_WN.print
#define WN_PRINTLN      DBG_PORT_WN.println

//////////////////////////////////////////

#define WN_LOGERROR0(x)     if(_WIFININA_LOGLEVEL_>0) { WN_PRINT(x); }
#define WN_LOGERROR(x)      if(_WIFININA_LOGLEVEL_>0) { WN_PRINT_MARK; WN_PRINTLN(x); }
#define WN_LOGERROR1(x,y)   if(_WIFININA_LOGLEVEL_>0) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINTLN(y); }
#define WN_LOGERROR2(x,y,z) if(_WIFININA_LOGLEVEL_>0) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINTLN(z); }
#define WN_LOGERROR3(x,y,z,w) if(_WIFININA_LOGLEVEL_>0) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINT(z); WN_PRINTLN(w); }
#define WN_LOGERROR5(x,y,z,w,xx,yy) if(_WIFININA_LOGLEVEL_>0) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINT(z); WN_PRINT(w); WN_PRINT(xx); WN_PRINTLN(yy); }

//////////////////////////////////////////

#define WN_LOGWARN0(x)     if(_WIFININA_LOGLEVEL_>1) { WN_PRINT(x); }
#define WN_LOGWARN(x)      if(_WIFININA_LOGLEVEL_>1) { WN_PRINT_MARK; WN_PRINTLN(x); }
#define WN_LOGWARN1(x,y)   if(_WIFININA_LOGLEVEL_>1) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINTLN(y); }
#define WN_LOGWARN2(x,y,z) if(_WIFININA_LOGLEVEL_>1) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINTLN(z); }
#define WN_LOGWARN3(x,y,z,w) if(_WIFININA_LOGLEVEL_>1) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINT(z); WN_PRINTLN(w); }
#define WN_LOGWARN5(x,y,z,w,xx,yy) if(_WIFININA_LOGLEVEL_>1) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINT(z); WN_PRINT(w); WN_PRINT(xx); WN_PRINTLN(yy); }

//////////////////////////////////////////

#define WN_LOGINFO0(x)     if(_WIFININA_LOGLEVEL_>2) { WN_PRINT(x); }
#define WN_LOGINFO(x)      if(_WIFININA_LOGLEVEL_>2) { WN_PRINT_MARK; WN_PRINTLN(x); }
#define WN_LOGINFO1(x,y)   if(_WIFININA_LOGLEVEL_>2) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINTLN(y); }
#define WN_LOGINFO2(x,y,z) if(_WIFININA_LOGLEVEL_>3) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINTLN(z); }
#define WN_LOGINFO3(x,y,z,w) if(_WIFININA_LOGLEVEL_>3) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINT(z); WN_PRINTLN(w); }
#define WN_LOGINFO5(x,y,z,w,xx,yy) if(_WIFININA_LOGLEVEL_>2) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINT(z); WN_PRINT(w); WN_PRINT(xx); WN_PRINTLN(yy); }

//////////////////////////////////////////

#define WN_LOGDEBUG0(x)     if(_WIFININA_LOGLEVEL_>3) { WN_PRINT(x); }
#define WN_LOGDEBUG(x)      if(_WIFININA_LOGLEVEL_>3) { WN_PRINT_MARK; WN_PRINTLN(x); }
#define WN_LOGDEBUG1(x,y)   if(_WIFININA_LOGLEVEL_>3) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINTLN(y); }
#define WN_LOGDEBUG2(x,y,z) if(_WIFININA_LOGLEVEL_>3) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINTLN(z); }
#define WN_LOGDEBUG3(x,y,z,w) if(_WIFININA_LOGLEVEL_>3) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINT(z); WN_PRINTLN(w); }
#define WN_LOGDEBUG5(x,y,z,w,xx,yy) if(_WIFININA_LOGLEVEL_>3) { WN_PRINT_MARK; WN_PRINT(x); WN_PRINT(y); WN_PRINT(z); WN_PRINT(w); WN_PRINT(xx); WN_PRINTLN(yy); }

//////////////////////////////////////////

#endif    //WiFiManager_NINA_Lite_Debug_h
