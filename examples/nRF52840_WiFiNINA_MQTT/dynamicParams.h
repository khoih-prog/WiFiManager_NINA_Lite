/****************************************************************************************************************************
   dynamicParams.h for nRF52840_WiFiNINA_MQTT.ino
   For nRF52 boards using WiFiNINA modules/shields, using much less code to support boards with smaller memory

   WiFiManager_NINA_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
   (https://github.com/khoih-prog/WiFiManager_NINA_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
   configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

   Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_NINA_Lite
   Licensed under MIT license
   Version: 1.0.4

   Version Modified By   Date        Comments
   ------- -----------  ----------   -----------
   1.0.0   K Hoang      26/03/2020  Initial coding
   1.0.1   K Hoang      27/03/2020  Fix SAMD soft-reset bug. Add support to remaining boards
   1.0.2   K Hoang      15/04/2020  Fix bug. Add SAMD51 support.
   1.0.3   K Hoang      24/04/2020  Fix bug. Add nRF5 (Adafruit, NINA_B302_ublox, etc.) support. Add MultiWiFi, HostName capability.
                                    SSID password maxlen is 63 now. Permit special chars # and % in input data.
   1.0.4   K Hoang      04/05/2020  Add Configurable Config Portal Title, Default Config Data and DRD. Update examples.        
 *****************************************************************************************************************************/

#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

#define USE_DYNAMIC_PARAMETERS      true

/////////////// Start dynamic Credentials ///////////////

//Defined in <WiFiManager_NINA_Lite_NRF52840.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define AIO_SERVER_LEN       20
#define AIO_SERVERPORT_LEN   6
#define AIO_USERNAME_LEN     20
#define AIO_KEY_LEN          40

// 
#define AIO_PUB_TOPIC_LEN    40
#define AIO_SUB_TOPIC_LEN    40

char AIO_SERVER     [AIO_SERVER_LEN + 1]        = "io.adafruit.com";
char AIO_SERVERPORT [AIO_SERVERPORT_LEN + 1]    = "1883";     //1883, or 8883 for SSL
char AIO_USERNAME   [AIO_USERNAME_LEN + 1]      = "private";
char AIO_KEY        [AIO_KEY_LEN + 1]           = "private";

char AIO_PUB_TOPIC  [AIO_PUB_TOPIC_LEN + 1]     = "/feeds/Temperature";
char AIO_SUB_TOPIC  [AIO_SUB_TOPIC_LEN + 1]     = "/feeds/LED_Control";

MenuItem myMenuItems [] =
{
  { "svr", "AIO_SERVER",      AIO_SERVER,     AIO_SERVER_LEN },
  { "prt", "AIO_SERVERPORT",  AIO_SERVERPORT, AIO_SERVERPORT_LEN },
  { "usr", "AIO_USERNAME",    AIO_USERNAME,   AIO_USERNAME_LEN },
  { "key", "AIO_KEY",         AIO_KEY,        AIO_KEY_LEN },
  { "pub", "AIO_PUB_TOPIC",   AIO_PUB_TOPIC,  AIO_PUB_TOPIC_LEN },
  { "sub", "AIO_SUB_TOPIC",   AIO_SUB_TOPIC,  AIO_SUB_TOPIC_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS


#endif      //dynamicParams_h
