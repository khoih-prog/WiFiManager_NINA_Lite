/****************************************************************************************************************************
   WiFiManager_NINA_Lite_SAMD.h
   For SAMD boards using WiFiNINA modules/shields

   WiFiManager_NINA_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards (https://github.com/khoih-prog/WiFiManager_NINA_Lite)
   to enable store Credentials in EEPROM to easy configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services
   without Hardcoding.

   Built by Khoi Hoang https://github.com/khoih-prog/WIFININA_WM_Lite
   Licensed under MIT license
   Version: 1.0.0

   Version Modified By   Date        Comments
   ------- -----------  ----------   -----------
    1.0.0   K Hoang      26/03/2020  Initial coding
  *****************************************************************************************************************************/

#ifndef WiFiManager_NINA_Lite_SAMD_SAMD_h
#define WiFiManager_NINA_Lite_SAMD_SAMD_h

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) )
#if defined(ESP8266_AT_USE_SAMD)
#undef ESP8266_AT_USE_SAMD
#endif
#define ESP8266_AT_USE_SAMD      true
#endif

#if ( defined(ESP8266) || defined(ESP32) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) || \
      defined(CORE_TEENSY) || !(ESP8266_AT_USE_SAMD) )
#error This code is intended to run on the SAMD platform! Please check your Tools->Board setting.
#endif

#include <WiFiWebServer.h>
// Include EEPROM-like API for FlashStorage
#include <FlashAsEEPROM.h>                //https://github.com/cmaglie/FlashStorage
#include <WiFiManager_NINA_Lite_Debug.h>

//NEW
#define MAX_ID_LEN                5
#define MAX_DISPLAY_NAME_LEN      16

typedef struct
{
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
} MenuItem;
//

///NEW
extern uint16_t NUM_MENU_ITEMS;
extern MenuItem myMenuItems [];

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    2
typedef struct Configuration
{
  char header         [16];
  char wifi_ssid      [32];
  char wifi_pw        [32];
  int  checkSum;
} WiFiNINA_Configuration;

// Currently CONFIG_DATA_SIZE  =   84
uint16_t CONFIG_DATA_SIZE = sizeof(WiFiNINA_Configuration);

// -- HTML page fragments
const char WIFININA_HTML_HEAD[]     /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>SAMD_WM_Lite</title><style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style></head><div style=\"text-align:left;display:inline-block;min-width:260px;\"><fieldset><div><label>SSID</label><input value=\"[[id]]\"id=\"id\"><div></div></div>\
<div><label>PWD</label><input value=\"[[pw]]\"id=\"pw\"><div></div></div></fieldset>";
const char WIFININA_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char WIFININA_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char WIFININA_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char WIFININA_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";
const char WIFININA_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+val;\
request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);";

const char WIFININA_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char WIFININA_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char WIFININA_HTML_END[]          /*PROGMEM*/ = "</html>";
///

String IPAddressToString(IPAddress _address)
{
  String str = String(_address[0]);
  str += ".";
  str += String(_address[1]);
  str += ".";
  str += String(_address[2]);
  str += ".";
  str += String(_address[3]);
  return str;
}

class WiFiManager_NINA_Lite
{
    public:
    
    WiFiManager_NINA_Lite()
    {     
      // check for the presence of the shield
      if (WiFi.status() == WL_NO_SHIELD) 
      {
        DEBUG_WM1(F("NoESP"));
      }     
    }

    ~WiFiManager_NINA_Lite()
    {
    }
        
    bool connectWiFi(const char* ssid, const char* pass)
    {
      DEBUG_WM2(F("Con2:"), ssid);

      if ( WiFi.begin(ssid, pass) )  
      {
        displayWiFiData();
      }
      else
      {
        DEBUG_WM1(F("NoW"));
        return false;
      }

      DEBUG_WM1(F("WOK"));

      wifi_connected = true;

      return true;
    }
   
    void begin(const char* ssid,
               const char* pass )
    {
      DEBUG_WM1(F("conWiFi"));
      connectWiFi(ssid, pass);
    }

    void begin(void)
    {
      #define TIMEOUT_CONNECT_WIFI			30000
      
      if (getConfigData())
      {
        hadConfigData = true;

        if (connectToWifi(TIMEOUT_CONNECT_WIFI))
        {
          DEBUG_WM1(F("b:WOK"));
        }
        else
        {
          DEBUG_WM1(F("b:NoW"));
          // failed to connect to WiFi, will start configuration mode
          startConfigurationMode();
        }
      }
      else
      {
        INFO_WM1(F("b:OpenPortal"));
        // failed to connect to WiFi, will start configuration mode
        hadConfigData = false;
        startConfigurationMode();
      }
    }

#ifndef TIMEOUT_RECONNECT_WIFI
#define TIMEOUT_RECONNECT_WIFI   10000L
#else
    // Force range of user-defined TIMEOUT_RECONNECT_WIFI between 10-60s
#if (TIMEOUT_RECONNECT_WIFI < 10000L)
#warning TIMEOUT_RECONNECT_WIFI too low. Reseting to 10000
#undef TIMEOUT_RECONNECT_WIFI
#define TIMEOUT_RECONNECT_WIFI   10000L
#elif (TIMEOUT_RECONNECT_WIFI > 60000L)
#warning TIMEOUT_RECONNECT_WIFI too high. Reseting to 60000
#undef TIMEOUT_RECONNECT_WIFI
#define TIMEOUT_RECONNECT_WIFI   60000L
#endif
#endif

#ifndef RESET_IF_CONFIG_TIMEOUT
#define RESET_IF_CONFIG_TIMEOUT   true
#endif

#ifndef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET          10
#else
    // Force range of user-defined TIMES_BEFORE_RESET between 2-100
#if (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET < 2)
#warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too low. Reseting to 2
#undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   2
#elif (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET > 100)
#warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too high. Resetting to 100
#undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   100
#endif
#endif

    void run()
    {
      static int retryTimes = 0;

      // Lost connection in running. Give chance to reconfig.
      if ( !wifi_connected )
      {
        // If configTimeout but user hasn't connected to configWeb => try to reconnect WiFi
        // But if user has connected to configWeb, stay there until done, then reset hardware
        if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
        {
          retryTimes = 0;

          if (server)
          {
            server->handleClient();
          }
           
          return;
        }
        else
        {
#if RESET_IF_CONFIG_TIMEOUT
          // If we're here but still in configuration_mode, permit running TIMES_BEFORE_RESET times before reset hardware
          // to permit user another chance to config.
          if ( configuration_mode && (configTimeout != 0) )
          {
            if (++retryTimes <= CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET)
            {
              DEBUG_WM2(F("r:Wlost&TOut.ConW+B.Retry#"), retryTimes);
            }
            else
            {
              resetFunc();  //call reset
            }
          }
#endif

          // Not in config mode, try reconnecting before forcing to config mode
          if ( !wifi_connected )
          {
            DEBUG_WM1(F("r:Wlost.ReconW+B"));
            if (connectToWifi(TIMEOUT_RECONNECT_WIFI))
            {
              DEBUG_WM1(F("r:W+BOK"));
            }
          }
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        DEBUG_WM1(F("r:gotW+Bback"));
      }
    }

    void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
    }

    void setConfigPortalChannel(int channel = 10)
    {
      AP_channel = channel;
    }
    
    void setConfigPortal(String ssid = "", String pass = "")
    {
      portal_ssid = ssid;
      portal_pass = pass;
    }

    void setSTAStaticIPConfig(IPAddress ip)
    {
      static_IP = ip;
    }

    WiFiNINA_Configuration* getFullConfigData(WiFiNINA_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &WiFiNINA_config, sizeof(WiFiNINA_Configuration));

      return (configData);
    }

    String localIP(void)
    {
      uint16_t indexNextLine;

      ipAddress = IPAddressToString(WiFi.localIP());
      ipAddress.replace("+CIFSR:STAIP,\"", "");
      ipAddress.replace("\"", "");

      indexNextLine = ipAddress.indexOf("\n");
      ipAddress = ipAddress.substring(0, indexNextLine);

      return ipAddress;
    }

    void clearConfigData()
    {
      memset(&WiFiNINA_config, 0, sizeof(WiFiNINA_config));
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen);
      }

      EEPROM_put();
    }

    void resetFunc()
    {
      void(*resetFunc)(void) = 0;
      resetFunc();
    }

  private:
    String ipAddress = "0.0.0.0";

    WiFiWebServer* server = NULL;
    
    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;

    WiFiNINA_Configuration WiFiNINA_config;

    String macAddress = "";
    bool wifi_connected = false;

    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);
    int AP_channel = 10;

    String portal_ssid = "";
    String portal_pass = "";

    IPAddress static_IP   = IPAddress(0, 0, 0, 0);

    void displayConfigData(void)
    {
      DEBUG_WM6(F("Hdr="), WiFiNINA_config.header, F(",SSID="), WiFiNINA_config.wifi_ssid,
                 F(",PW="),   WiFiNINA_config.wifi_pw);
                 
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        DEBUG_WM6("i=", i, ",id=", myMenuItems[i].id, ",data=", myMenuItems[i].pdata);
      }           
    }

    void displayWiFiData(void)
    {
      DEBUG_WM2(F("IP="), localIP());
    }

#define WIFININA_BOARD_TYPE   "WIFININA"
#define NO_CONFIG           "blank"

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(WiFiNINA_config) - sizeof(WiFiNINA_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &WiFiNINA_config ) + index);
      }

      return checkSum;
    }

    uint16_t totalDataSize = 0;
    
    bool EEPROM_get()
    {
      // It's too bad that emulate EEPROM.read()/writ() can only deal with bytes. 
      // Have to read/write each byte. To rewrite the library
      
      uint16_t offset = EEPROM_START;
                
      uint8_t* _pointer = (uint8_t *) &WiFiNINA_config;
      
      for (int i = 0; i < sizeof(WiFiNINA_config); i++, _pointer++, offset++)
      {              
        *_pointer = EEPROM.read(offset);
      }
           
      int checkSum = 0;
      int readCheckSum;
      
      totalDataSize = sizeof(WiFiNINA_config) + sizeof(readCheckSum);
   
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        _pointer = (uint8_t *) myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, offset++)
        {
          *_pointer = EEPROM.read(offset);          
          checkSum += *_pointer;  
         }       
      }
      
      _pointer = (uint8_t *) &readCheckSum;
      
      for (int i = 0; i < sizeof(readCheckSum); i++, _pointer++, offset++)
      {                  
        *_pointer = EEPROM.read(offset);
      }
         
      DEBUG_WM4(F("CrCCSum="), checkSum, F(",CrRCSum="), readCheckSum);
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }    
    
    void EEPROM_put()
    {
      // It's too bad that emulate EEPROM.read()/writ() can only deal with bytes. 
      // Have to read/write each byte. To rewrite the library
      
      uint16_t offset = EEPROM_START;
           
      uint8_t* _pointer = (uint8_t *) &WiFiNINA_config;
      
      for (int i = 0; i < sizeof(WiFiNINA_config); i++, _pointer++, offset++)
      {              
        EEPROM.write(offset, *_pointer);
      }
           
      int checkSum = 0;
    
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        _pointer = (uint8_t *) myMenuItems[i].pdata;
        
        DEBUG_WM4(F("pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          EEPROM.write(offset, *_pointer);
          
          checkSum += *_pointer;     
         }
      }
      
      _pointer = (uint8_t *) &checkSum;
      
      for (int i = 0; i < sizeof(checkSum); i++, _pointer++, offset++)
      {              
        EEPROM.write(offset, *_pointer);
      }
      
      EEPROM.commit();
      
      DEBUG_WM2(F("CrCCSum="), checkSum);
    }   
    
    bool getConfigData()
    {
      bool credDataValid;   
      
      hadConfigData = false;     
      
      credDataValid = EEPROM_get();

      int calChecksum = calcChecksum();

      DEBUG_WM4(F("CCSum="), calChecksum, F(",RCSum="), WiFiNINA_config.checkSum);

      if ( (strncmp(WiFiNINA_config.header, WIFININA_BOARD_TYPE, strlen(WIFININA_BOARD_TYPE)) != 0) ||
           (calChecksum != WiFiNINA_config.checkSum) || !credDataValid )
      {
        memset(&WiFiNINA_config, 0, sizeof(WiFiNINA_config));
        
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
        {
          memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen);
        }

        // Including Credentials CSum
        DEBUG_WM4(F("InitEEPROM,sz="), EEPROM.length(), F(",Datasz="), totalDataSize);
        
        // doesn't have any configuration
        strcpy(WiFiNINA_config.header,           WIFININA_BOARD_TYPE);
        strcpy(WiFiNINA_config.wifi_ssid,        NO_CONFIG);
        strcpy(WiFiNINA_config.wifi_pw,          NO_CONFIG);
        
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
        {
          strncpy(myMenuItems[i].pdata, NO_CONFIG, myMenuItems[i].maxlen - 1);
        }

        // Don't need
        WiFiNINA_config.checkSum = 0;

        EEPROM_put();

        return false;
      }
      else if ( !strncmp(WiFiNINA_config.wifi_ssid,       NO_CONFIG, strlen(NO_CONFIG) ) ||
                !strncmp(WiFiNINA_config.wifi_pw,         NO_CONFIG, strlen(NO_CONFIG) ) ||
                !strlen(WiFiNINA_config.wifi_ssid) ||
                !strlen(WiFiNINA_config.wifi_pw)  )
      {
        // If SSID, PW ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData();
      }

      return true;
    }

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      WiFiNINA_config.checkSum = calChecksum;
      
      DEBUG_WM6(F("SaveEEPROM,sz="), EEPROM.length(), F(",Datasz="), totalDataSize, F(",CSum="), calChecksum);

      EEPROM_put();
    }

    bool connectToWifi(int timeout)
    {
      int sleep_time = 250;
      unsigned long currMillis = millis();

      DEBUG_WM1(F("con2WF:start"));

      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        DEBUG_WM1(F("UseStatIP"));
        WiFi.config(static_IP);
      }

      while ( !wifi_connected && ( 0 < timeout ) && ( (millis() - currMillis) < (unsigned long) timeout )  )
      {
        DEBUG_WM2(F("con2WF:spentMsec="), millis() - currMillis);

        if (connectWiFi(WiFiNINA_config.wifi_ssid, WiFiNINA_config.wifi_pw))
        {
          wifi_connected = true;
        }
        else
        {
          delay(sleep_time);
          timeout -= sleep_time;
        }
      }

      if (wifi_connected)
      {
        DEBUG_WM1(F("con2WF:OK"));
        displayWiFiData();
      }
      else
      {
        DEBUG_WM1(F("con2WF:failed"));
      }

      return wifi_connected;
    }

    // NEW
    String root_html_template;
       
    String createHTML(void)
    {
      String pitem;
      
      root_html_template = String(WIFININA_HTML_HEAD)  + WIFININA_FLDSET_START;
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(WIFININA_HTML_PARAM);

        pitem.replace("{b}", myMenuItems[i].displayName);
        pitem.replace("{v}", myMenuItems[i].id);
        pitem.replace("{i}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
      
      root_html_template += String(WIFININA_FLDSET_END) + WIFININA_HTML_BUTTON + WIFININA_HTML_SCRIPT;     
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(WIFININA_HTML_SCRIPT_ITEM);
        
        pitem.replace("{d}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
      
      root_html_template += String(WIFININA_HTML_SCRIPT_END) + WIFININA_HTML_END;
      
      return root_html_template;     
    }

    void handleRequest()
    {
      if (server)
      {
        String key    = server->arg("key");
        String value  = server->arg("value");

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          String result = createHTML();

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          result.replace("[[id]]",     WiFiNINA_config.wifi_ssid);
          result.replace("[[pw]]",     WiFiNINA_config.wifi_pw);
          
          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
          }

          server->send(200, "text/html", result);

          return;
        }

        if (number_items_Updated == 0)
        {
          memset(&WiFiNINA_config, 0, sizeof(WiFiNINA_config));
          strcpy(WiFiNINA_config.header, WIFININA_BOARD_TYPE);
        }

        if (key == "id")
        {
          DEBUG_WM2(F("h:id="), value.c_str() );
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WiFiNINA_config.wifi_ssid) - 1)
            strcpy(WiFiNINA_config.wifi_ssid, value.c_str());
          else
            strncpy(WiFiNINA_config.wifi_ssid, value.c_str(), sizeof(WiFiNINA_config.wifi_ssid) - 1);
        }
        else if (key == "pw")
        {
          DEBUG_WM2(F("h:pw="), value.c_str() )
          number_items_Updated++;          
          if (strlen(value.c_str()) < sizeof(WiFiNINA_config.wifi_pw) - 1)
            strcpy(WiFiNINA_config.wifi_pw, value.c_str());
          else
            strncpy(WiFiNINA_config.wifi_pw, value.c_str(), sizeof(WiFiNINA_config.wifi_pw) - 1);
        }
        
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
        {
          if (key == myMenuItems[i].id)
          {
            DEBUG_WM4(F("h:"), myMenuItems[i].id, F("="), value.c_str() );
            number_items_Updated++;

            if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen - 1)
              strcpy(myMenuItems[i].pdata, value.c_str());
            else
              strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen - 1);
          }
        }

        server->send(200, "text/html", "OK");

        // NEW
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
        {
          DEBUG_WM1(F("h:UpdEEPROM"));

          saveConfigData();

          DEBUG_WM1(F("h:Rst"));

          // TO DO : what command to reset
          // Delay then reset the board after save data
          delay(1000);
          resetFunc();  //call reset
        }
      }   // if (server)
    }

    void startConfigurationMode()
    {
#define CONFIG_TIMEOUT			60000L
      //WiFi.reset();

      //WiFi.configAP(portal_apIP);
      WiFi.config(portal_apIP);

      if ( (portal_ssid == "") || portal_pass == "" )
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();

        portal_ssid = "WIFININA_" + randomNum;
        portal_pass = "MyWIFININA_" + randomNum;
      }

      INFO_WM4(F("SSID="), portal_ssid, F(",PW="), portal_pass);
      INFO_WM4(F("IP="), portal_apIP, F(",CH="), AP_channel);

      // start access point, AP only, channel 10
      
      //WiFi.beginAP(portal_ssid.c_str(), AP_channel, portal_pass.c_str(), ENC_TYPE_WPA2_PSK, true);
      WiFi.beginAP(portal_ssid.c_str(), portal_pass.c_str(), AP_channel);
      

      if (!server)
      {
        server = new WiFiWebServer;
      }

      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1

      if (server)
      {
        server->on("/", [this](){ handleRequest(); });
        server->begin();
      }

      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
        configTimeout = millis() + CONFIG_TIMEOUT;
      else
        configTimeout = 0;

      configuration_mode = true;
    }
};


#endif    //WiFiManager_NINA_Lite_SAMD_SAMD_h
