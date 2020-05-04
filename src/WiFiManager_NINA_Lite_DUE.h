/****************************************************************************************************************************
   WiFiManager_NINA_Lite_DUE.h
   For SAM DUE boards using WiFiNINA modules/shields, using much less code to support boards with smaller memory

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

#ifndef WiFiManager_NINA_Lite_DUE_h
#define WiFiManager_NINA_Lite_DUE_h

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(WIFININA_USE_SAM_DUE)
  #undef WIFININA_USE_SAM_DUE
  #endif
  #define WIFININA_USE_SAM_DUE      true
  #warning Use SAM_DUE architecture from WiFiManager_NINA_Lite_DUE
#endif

#if ( defined(ESP8266) || defined(ESP32) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) || \
      defined(CORE_TEENSY) || defined(CORE_TEENSY) || !(WIFININA_USE_SAM_DUE) )
#error This code is intended to run on the SAM DUE platform! Please check your Tools->Board setting.
#endif

#include <WiFiWebServer.h>
#include <WiFiManager_NINA_Lite_Debug.h>

//Use DueFlashStorage to simulate EEPROM
#include <DueFlashStorage.h>                 //https://github.com/sebnil/DueFlashStorage

DueFlashStorage dueFlashStorageData;

///////// NEW for DRD /////////////
// These defines must be put before #include <DoubleResetDetector_Generic.h>
// to select where to store DoubleResetDetector_Generic's variable.
// Otherwise, library will use default EEPROM storage
#define  DRD_FLAG_DATA_SIZE     4

#ifndef DRD_GENERIC_DEBUG
#define DRD_GENERIC_DEBUG     false
#endif

#include <DoubleResetDetector_Generic.h>      //https://github.com/khoih-prog/DoubleResetDetector_Generic

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

DoubleResetDetector_Generic* drd;

///////// NEW for DRD /////////////

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

// New in v1.0.3

#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [24];
  int  checkSum;
} WiFiNINA_Configuration;

// Currently CONFIG_DATA_SIZE  =   236  = (16 + 96 * 2 + 4 + 24)
uint16_t CONFIG_DATA_SIZE = sizeof(WiFiNINA_Configuration);

///New from v1.0.4
extern bool LOAD_DEFAULT_CONFIG_DATA;
extern WiFiNINA_Configuration defaultConfig;

// -- HTML page fragments
const char WIFININA_HTML_HEAD[]     /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>SAM_DUE_WM_NINA_Lite</title><style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style></head><div style=\"text-align:left;display:inline-block;min-width:260px;\">\
<fieldset><div><label>WiFi SSID</label><input value=\"[[id]]\"id=\"id\"><div></div></div>\
<div><label>PWD</label><input value=\"[[pw]]\"id=\"pw\"><div></div></div>\
<div><label>WiFi SSID1</label><input value=\"[[id1]]\"id=\"id1\"><div></div></div>\
<div><label>PWD1</label><input value=\"[[pw1]]\"id=\"pw1\"><div></div></div></fieldset>\
<fieldset><div><label>Board Name</label><input value=\"[[nm]]\"id=\"nm\"><div></div></div></fieldset>";

const char WIFININA_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char WIFININA_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char WIFININA_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char WIFININA_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";
const char WIFININA_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);\
request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);\
udVal('id1',document.getElementById('id1').value);udVal('pw1',document.getElementById('pw1').value);\
udVal('nm',document.getElementById('nm').value);";

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
        DEBUG_WM1(F("NoNINA"));
      }
    }

    ~WiFiManager_NINA_Lite()
    {
      if (server)
        delete server;    
    }
        
    bool connectWiFi(const char* ssid, const char* pass)
    {
      DEBUG_WM2(F("Con2:"), ssid);
      
      // New in v1.0.3
      setHostname();
      ///

      if ( WiFi.begin(ssid, pass) == WL_CONNECTED )
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
      DEBUG_WM1(F("conW"));
      connectWiFi(ssid, pass);
    }

    // New in v1.0.3 
    void begin(const char *iHostname = "")
    {
      #define TIMEOUT_CONNECT_WIFI			10000
      
      // New in v1.0.3
      if (iHostname[0] == 0)
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();
        
        String _hostname = "DUE-WiFiNINA-" + randomNum;
        _hostname.toUpperCase();

        getRFC952_hostname(_hostname.c_str());
      }
      else
      {
        // Prepare and store the hostname only not NULL
        getRFC952_hostname(iHostname);
      }
      
      DEBUG_WM2(F("Hostname="), RFC952_hostname);
      //////
      
      //// New DRD ////
      drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (drd->detectDoubleReset())
      {
        DEBUG_WM1(F("Double Reset Detected"));
     
        noConfigPortal = false;
      }
      //// New DRD ////
      DEBUG_WM1(F("======= Start Default Config Data ======="));
      displayConfigData(defaultConfig);
      
      hadConfigData = getConfigData();
        
      DEBUG_WM1(noConfigPortal? F("bg: noConfigPortal = true") : F("bg: noConfigPortal = false"));

      //// New DRD ////
      //  noConfigPortal when getConfigData() OK and no DRD'ed
      if (hadConfigData && noConfigPortal)     
      //// New DRD //// 
      {
        hadConfigData = true;

        if (connectMultiWiFi(TIMEOUT_CONNECT_WIFI))
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
      // Check WiFi status every 2s and update status
      static unsigned long checkstatus_timeout = 0;
      #define WIFI_STATUS_CHECK_INTERVAL    2000L
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////
      
      if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
      {
        if (WiFi.status() == WL_CONNECTED)
        {
          wifi_connected = true;
        }
        else
        {
          wifi_connected = false;
        }
        
        checkstatus_timeout = millis() + WIFI_STATUS_CHECK_INTERVAL;
      }    
      
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
              DEBUG_WM2(F("r:Wlost&TOut.ConW.Retry#"), retryTimes);
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
            DEBUG_WM1(F("r:Wlost.ReconW"));
            
            if (connectMultiWiFi(TIMEOUT_CONNECT_WIFI))
            {
              DEBUG_WM1(F("r:WOK"));
            }
          }
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        DEBUG_WM1(F("r:gotWBack"));
      }
    }
    
    void setHostname(void)
    {
      if (RFC952_hostname[0] != 0)
      {
        WiFi.setHostname(RFC952_hostname);
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
    
    String getWiFiSSID(uint8_t index)
    { 
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WiFiNINA_config.WiFi_Creds[index].wifi_ssid));
    }

    String getWiFiPW(uint8_t index)
    {
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WiFiNINA_config.WiFi_Creds[index].wifi_pw));
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
      ipAddress = IPAddressToString(WiFi.localIP());

      return ipAddress;
    }

    void clearConfigData()
    {
      memset(&WiFiNINA_config, 0, sizeof(WiFiNINA_config));
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }

     //dueFlashStorage_put();
      saveConfigData();
    }
    
    bool isConfigDataValid(void)
    {
      return hadConfigData;
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
    
    uint16_t totalDataSize = 0;

    String macAddress = "";
    bool wifi_connected = false;

    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);
    int AP_channel = 10;

    String portal_ssid = "";
    String portal_pass = "";

    IPAddress static_IP   = IPAddress(0, 0, 0, 0);

    #define RFC952_HOSTNAME_MAXLEN      24
    char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

    char* getRFC952_hostname(const char* iHostname)
    {
      memset(RFC952_hostname, 0, sizeof(RFC952_hostname));

      size_t len = ( RFC952_HOSTNAME_MAXLEN < strlen(iHostname) ) ? RFC952_HOSTNAME_MAXLEN : strlen(iHostname);

      size_t j = 0;

      for (size_t i = 0; i < len - 1; i++)
      {
        if ( isalnum(iHostname[i]) || iHostname[i] == '-' )
        {
          RFC952_hostname[j] = iHostname[i];
          j++;
        }
      }
      // no '-' as last char
      if ( isalnum(iHostname[len - 1]) || (iHostname[len - 1] != '-') )
        RFC952_hostname[j] = iHostname[len - 1];

      return RFC952_hostname;
    }
    
    void displayConfigData(WiFiNINA_Configuration configData)
    {
      DEBUG_WM6(F("Hdr="),   configData.header, F(",SSID="), configData.WiFi_Creds[0].wifi_ssid,
                F(",PW="),   configData.WiFi_Creds[0].wifi_pw);
      DEBUG_WM4(F("SSID1="), configData.WiFi_Creds[1].wifi_ssid, F(",PW1="),  configData.WiFi_Creds[1].wifi_pw);     
      DEBUG_WM2(F("BName="), configData.board_name);     
                 
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        DEBUG_WM6("i=", i, ",id=", myMenuItems[i].id, ",data=", myMenuItems[i].pdata);
      }           
    }

    void displayWiFiData(void)
    {
      DEBUG_WM4(F("SSID="), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());
      DEBUG_WM2(F("IP="), localIP() );
    }

#define WIFININA_BOARD_TYPE   "WIFININA"
#define WM_NO_CONFIG             "blank"

#ifndef EEPROM_START
#define EEPROM_START     0
#warning EEPROM_START not defined. Set to 0
#endif

// Stating positon to store Blynk8266_WM_config
#define NINA_EEPROM_START    (EEPROM_START + DRD_FLAG_DATA_SIZE)


    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(WiFiNINA_config) - sizeof(WiFiNINA_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &WiFiNINA_config ) + index);
      }

      return checkSum;
    }
   
    bool checkDynamicData(void)
    {
      int checkSum = 0;
      int readCheckSum;
      
      uint16_t  byteCount = 0;
      
      //#define BUFFER_LEN            128
      //char readBuffer[BUFFER_LEN + 1];
      
      #define BIG_BUFFER_LEN        768     
      byte bigBuffer[BIG_BUFFER_LEN + 1];      
      
      uint16_t offset = NINA_EEPROM_START + sizeof(WiFiNINA_config);      
           
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
      
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      int totalLength = 0;
            
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        totalLength += myMenuItems[i].maxlen;
        
        if ( (totalLength > BIG_BUFFER_LEN) || (myMenuItems[i].maxlen > BIG_BUFFER_LEN) )
        {
          // Size too large, abort and flag false
          DEBUG_WM1(F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
                         
      // Both Buffers big enough, read all dynamicData to BigBuffer once 
      // as address need to be 4-byte aligned
      byte* dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      // Prepare buffer, more than enough
      memset(bigBuffer, 0, sizeof(bigBuffer));
      memcpy(bigBuffer, dataPointer, sizeof(bigBuffer));               
         
      // Don't need readBuffer
      // Now to split into individual piece to add to CSum
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = (char*) bigBuffer;
        
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, byteCount++)
        {
          *_pointer = bigBuffer[byteCount];
                  
          checkSum += *_pointer;  
        }    
      }
      
      memcpy(&readCheckSum, &bigBuffer[byteCount], sizeof(readCheckSum));
          
      DEBUG_WM4(F("ChkCrR:CrCCsum="), String(checkSum, HEX), F(",CrRCsum="), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum )
      {
        return false;
      }
      
      return true;    
    }
    
    bool dueFlashStorage_get(void)
    {
      uint16_t offset = NINA_EEPROM_START;
            
      byte* dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      memcpy(&WiFiNINA_config, dataPointer, sizeof(WiFiNINA_config));
      
      offset += sizeof(WiFiNINA_config);
           
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
            
      int checkSum = 0;
      int readCheckSum;
      
      uint16_t  byteCount = 0;
           
      byte buffer[768];
      
      dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      memcpy(buffer, dataPointer, sizeof(buffer));
      
      totalDataSize = sizeof(WiFiNINA_config) + sizeof(readCheckSum);
   
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
                      
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++, byteCount++)
        {
          *_pointer = buffer[byteCount];
          
          checkSum += *_pointer;  
         }     
      }
      
      memcpy(&readCheckSum, &buffer[byteCount], sizeof(readCheckSum));
      
      byteCount += sizeof(readCheckSum);      
      
      DEBUG_WM6(F("CrCCsum="), checkSum, F(",CrRCsum="), readCheckSum, F(",TotalDataSz="), totalDataSize);
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }    
    
    void dueFlashStorage_put(void)
    {
      uint16_t offset = NINA_EEPROM_START;
      
      dueFlashStorageData.write(offset, (byte *) &WiFiNINA_config, sizeof(WiFiNINA_config));
      
      offset += sizeof(WiFiNINA_config);
      
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
      
      int       checkSum = 0;
      uint16_t  byteCount = 0;
           
      // Use 2K buffer, if need more memory, can reduce this
      byte buffer[2048];
         
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        
        //DEBUG_WM4(F("pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, /*offset++,*/ byteCount++)
        {
          if (byteCount >= sizeof(buffer))
          {
            DEBUG_WM2(F("Danger:dynamic data too long >"), sizeof(buffer));
          }
          
          buffer[byteCount] = *_pointer;          
          checkSum += *_pointer;     
         }
      }
           
      memcpy(&buffer[byteCount], &checkSum, sizeof(checkSum));
      
      byteCount += sizeof(checkSum);
      
      dueFlashStorageData.write(offset, buffer, byteCount);
      
      DEBUG_WM4(F("CrCCSum="), checkSum, F(",byteCount="), byteCount);
    }    
 
    bool getConfigData()
    {
      bool dynamicDataValid;   
      
      hadConfigData = false;    
          
      // For DUE, DATA_LENGTH = ((IFLASH1_PAGE_SIZE/sizeof(byte))*4) = 1KBytes
      DEBUG_WM2(F("Simulate EEPROM, sz:"), DATA_LENGTH);

      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        // Load default dynamicData, if checkSum OK => valid data => load
        // otherwise, use default in sketch and just assume it's OK
        if (checkDynamicData())
        {
          DEBUG_WM1(F("Valid Stored Dynamic Data"));
          dueFlashStorage_get();
        }
        else
        {
          DEBUG_WM1(F("Ignore invalid Stored Dynamic Data"));
        }  
          
        dynamicDataValid = true;
      }
      else
      {           
        dynamicDataValid = dueFlashStorage_get();
      }  
                
      DEBUG_WM1(F("======= Start Stored Config Data ======="));
      displayConfigData(WiFiNINA_config);

      int calChecksum = calcChecksum();

      DEBUG_WM4(F("CCSum=0x"), String(calChecksum, HEX),
                 F(",RCSum=0x"), String(WiFiNINA_config.checkSum, HEX));

      if ( (strncmp(WiFiNINA_config.header, WIFININA_BOARD_TYPE, strlen(WIFININA_BOARD_TYPE)) != 0) ||
           (calChecksum != WiFiNINA_config.checkSum) || !dynamicDataValid )
      {
        // Including Credentials CSum
        DEBUG_WM2(F("InitCfgFile,sz="), sizeof(WiFiNINA_config));

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&WiFiNINA_config, &defaultConfig, sizeof(WiFiNINA_config));
        }
        else
        {
          memset(&WiFiNINA_config, 0, sizeof(WiFiNINA_config));

          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
              
          strcpy(WiFiNINA_config.WiFi_Creds[0].wifi_ssid,   WM_NO_CONFIG);
          strcpy(WiFiNINA_config.WiFi_Creds[0].wifi_pw,     WM_NO_CONFIG);
          strcpy(WiFiNINA_config.WiFi_Creds[1].wifi_ssid,   WM_NO_CONFIG);
          strcpy(WiFiNINA_config.WiFi_Creds[1].wifi_pw,     WM_NO_CONFIG);
          strcpy(WiFiNINA_config.board_name, WM_NO_CONFIG);
          
          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
        }
    
        strcpy(WiFiNINA_config.header, WIFININA_BOARD_TYPE);
        
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
        {
          DEBUG_WM4(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
        
        // Don't need
        WiFiNINA_config.checkSum = 0;

        saveConfigData();
        
       //dueFlashStorage_put();

        return false;
      }
      else if ( !strncmp(WiFiNINA_config.WiFi_Creds[0].wifi_ssid,       WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WiFiNINA_config.WiFi_Creds[0].wifi_pw,         WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WiFiNINA_config.WiFi_Creds[1].wifi_ssid,       WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WiFiNINA_config.WiFi_Creds[1].wifi_pw,         WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strlen(WiFiNINA_config.WiFi_Creds[0].wifi_ssid) || 
                !strlen(WiFiNINA_config.WiFi_Creds[1].wifi_ssid) ||
                !strlen(WiFiNINA_config.WiFi_Creds[0].wifi_pw)   ||
                !strlen(WiFiNINA_config.WiFi_Creds[1].wifi_pw)  )
      {
        // If SSID, PW ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(WiFiNINA_config);
      }

      return true;
    }

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      WiFiNINA_config.checkSum = calChecksum;
      
      DEBUG_WM4(F("SaveData,sz="), totalDataSize, F(",chkSum="), calChecksum);

      dueFlashStorage_put();
    }

    bool connectMultiWiFi(int timeout)
    {
      int sleep_time = 250;
      uint8_t status;
      
      unsigned long currMillis;

      DEBUG_WM1(F("Connecting MultiWifi..."));

      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        DEBUG_WM1(F("UseStatIP"));
        WiFi.config(static_IP);
      }
      
      for (int i = 0; i < NUM_WIFI_CREDENTIALS; i++)
      {
        currMillis = millis();
        
        setHostname();
        
        while ( !wifi_connected && ( 0 < timeout ) && ( (millis() - currMillis) < (unsigned long) timeout )  )
        {
          DEBUG_WM2(F("con2WF:spentMsec="), millis() - currMillis);
          
          status = WiFi.begin(WiFiNINA_config.WiFi_Creds[i].wifi_ssid, WiFiNINA_config.WiFi_Creds[i].wifi_pw);

          if (status == WL_CONNECTED)
          {
            wifi_connected = true;
            // To exit for loop
            i = NUM_WIFI_CREDENTIALS;
            break;
          }
          else
          {
            delay(sleep_time);
          }
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
    void createHTML(String& root_html_template)
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
      
      return;     
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
          String result;
          createHTML(result);

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          if ( RFC952_hostname[0] != 0 )
          {
            // Replace only if Hostname is valid
            result.replace("SAM_DUE_WM_NINA_Lite", RFC952_hostname);
          }
          else if ( WiFiNINA_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("SAM_DUE_WM_NINA_Lite", WiFiNINA_config.board_name);
          }

          result.replace("[[id]]",     WiFiNINA_config.WiFi_Creds[0].wifi_ssid);
          result.replace("[[pw]]",     WiFiNINA_config.WiFi_Creds[0].wifi_pw);
          result.replace("[[id1]]",    WiFiNINA_config.WiFi_Creds[1].wifi_ssid);
          result.replace("[[pw1]]",    WiFiNINA_config.WiFi_Creds[1].wifi_pw);
          result.replace("[[nm]]",     WiFiNINA_config.board_name);
          
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
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WiFiNINA_config.WiFi_Creds[0].wifi_ssid) - 1)
            strcpy(WiFiNINA_config.WiFi_Creds[0].wifi_ssid, value.c_str());
          else
            strncpy(WiFiNINA_config.WiFi_Creds[0].wifi_ssid, value.c_str(), sizeof(WiFiNINA_config.WiFi_Creds[0].wifi_ssid) - 1);
        }
        else if (key == "pw")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WiFiNINA_config.WiFi_Creds[0].wifi_pw) - 1)
            strcpy(WiFiNINA_config.WiFi_Creds[0].wifi_pw, value.c_str());
          else
            strncpy(WiFiNINA_config.WiFi_Creds[0].wifi_pw, value.c_str(), sizeof(WiFiNINA_config.WiFi_Creds[0].wifi_pw) - 1);
        }
        else if (key == "id1")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WiFiNINA_config.WiFi_Creds[1].wifi_ssid) - 1)
            strcpy(WiFiNINA_config.WiFi_Creds[1].wifi_ssid, value.c_str());
          else
            strncpy(WiFiNINA_config.WiFi_Creds[1].wifi_ssid, value.c_str(), sizeof(WiFiNINA_config.WiFi_Creds[1].wifi_ssid) - 1);
        }
        else if (key == "pw1")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WiFiNINA_config.WiFi_Creds[1].wifi_pw) - 1)
            strcpy(WiFiNINA_config.WiFi_Creds[1].wifi_pw, value.c_str());
          else
            strncpy(WiFiNINA_config.WiFi_Creds[1].wifi_pw, value.c_str(), sizeof(WiFiNINA_config.WiFi_Creds[1].wifi_pw) - 1);
        }
        else if (key == "nm")
        {
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WiFiNINA_config.board_name) - 1)
            strcpy(WiFiNINA_config.board_name, value.c_str());
          else
            strncpy(WiFiNINA_config.board_name, value.c_str(), sizeof(WiFiNINA_config.board_name) - 1);
        }
        
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
        {
          if (key == myMenuItems[i].id)
          {
            DEBUG_WM4(F("h:"), myMenuItems[i].id, F("="), value.c_str() );
            number_items_Updated++;

            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

            if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
              strcpy(myMenuItems[i].pdata, value.c_str());
            else
              strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
          }
        }

        server->send(200, "text/html", "OK");

        // NEW
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
        {
          DEBUG_WM1(F("h:UpdFlash"));

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

      // start access point, AP only,default channel 10
      WiFi.beginAP(portal_ssid.c_str(), portal_pass.c_str(), AP_channel);

      if (!server)
      {
        server = new WiFiWebServer;
      }

      // Don't know if it's working or not. Can we use ESP8266_Lib wifi TCP server for this ??

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


#endif    //WiFiManager_NINA_Lite_DUE_h
