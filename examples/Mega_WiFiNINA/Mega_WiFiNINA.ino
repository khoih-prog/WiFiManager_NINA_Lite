/****************************************************************************************************************************
  Mega_WiFiNINA.ino
  For AVR or Generic boards using WiFiNINA Modules/Shields, using much less code to support boards with smaller memory
  
  WiFiManager_NINA_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_NINA_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.
  
  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_NINA_Lite
  Licensed under MIT license
  Version: 1.3.0

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      26/03/2020  Initial coding
  1.0.1   K Hoang      27/03/2020  Fix SAMD soft-reset bug. Add support to remaining boards
  1.0.2   K Hoang      15/04/2020  Fix bug. Add SAMD51 support.
  1.0.3   K Hoang      24/04/2020  Fix bug. Add nRF5 (Adafruit, NINA_B302_ublox, etc.) support. Add MultiWiFi, HostName capability.
                                   SSID password maxlen is 63 now. Permit special chars # and % in input data.
  1.0.4   K Hoang      04/05/2020  Add Configurable Config Portal Title, Default Config Data and DRD. Update examples.
  1.0.5   K Hoang      11/07/2020  Modify LOAD_DEFAULT_CONFIG_DATA logic. Enhance MultiWiFi connection logic. Add MQTT examples.
  1.1.0   K Hoang      19/02/2021  Optimize code and use better FlashStorage_SAMD and FlashStorage_STM32.
                                   Add customs HTML header feature. Fix bug.
  1.1.1   K Hoang      13/03/2021  Fix USE_DYNAMIC_PARAMETERS bug.
  1.1.2   K Hoang      30/03/2021  Fix MultiWiFi connection bug.
  1.1.3   K Hoang      12/04/2021  Fix invalid "blank" Config Data treated as Valid.
  1.2.0   K Hoang      14/04/2021  Optional one set of WiFi Credentials. Enforce WiFi PWD minimum 8 chars
  1.3.0   Michael H    21/04/2021  Enable scan of WiFi networks for selection in Configuration Portal
  **********************************************************************************************************************************/
  
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

void heartBeatPrint(void)
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print(F("H"));        // H means connected to WiFi
  else
    Serial.print(F("F"));        // F means not connected to WiFi
  
  if (num == 80) 
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0) 
  {
    Serial.print(F(" "));
  }
} 

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define HEARTBEAT_INTERVAL    600000L
  // Print hearbeat every HEARTBEAT_INTERVAL (600) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

WiFiManager_NINA_Lite* WiFiManager_NINA;

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStarting Mega_WiFiNINA on ")); Serial.println(BOARD_TYPE);
  Serial.println(WIFIMANAGER_NINA_LITE_VERSION);

  WiFiManager_NINA = new WiFiManager_NINA_Lite();

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //WiFiManager_NINA->setConfigPortalIP(IPAddress(192, 168, 120, 1));
  WiFiManager_NINA->setConfigPortalChannel(0);

  // Set customized DHCP HostName
  WiFiManager_NINA->begin(HOST_NAME);
  //Or use default Hostname "Mega-WiFiNINA-XXXXXX"
  //WiFiManager_NINA->begin();
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials(void)
{
  Serial.println("\nYour stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  WiFiManager_NINA->run();
  check_status();

#if USE_DYNAMIC_PARAMETERS
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
#endif
}
