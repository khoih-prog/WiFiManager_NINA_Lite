/*********************************************************************************************************************************
  WiFiManager_NINA_Lite_SAMD.h
  For SAMD boards using WiFiNINA modules/shields, using much less code to support boards with smaller memory

  WiFiManager_NINA_WM_Lite is a library for the Mega, Teensy, SAM DUE, SAMD and STM32 boards 
  (https://github.com/khoih-prog/WiFiManager_NINA_Lite) to enable store Credentials in EEPROM/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_NINA_Lite
  Licensed under MIT license
  Version: 1.1.1

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
  **********************************************************************************************************************************/

#ifndef WiFiManager_NINA_Lite_SAMD_h
#define WiFiManager_NINA_Lite_SAMD_h

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(WIFININA_USE_SAMD)
    #undef WIFININA_USE_SAMD
  #endif
  #define WIFININA_USE_SAMD      true
#else
  #error This code is intended to run on the SAMD platform! Please check your Tools->Board setting.  
#endif

#define WIFIMANAGER_NINA_LITE_VERSION        "WiFiManager_NINA_Lite v1.1.1"

#include <WiFiWebServer.h>
// Include EEPROM-like API for FlashStorage
//#include <FlashAsEEPROM.h>                //https://github.com/cmaglie/FlashStorage
#include <FlashAsEEPROM_SAMD.h>                //https://github.com/khoih-prog/FlashStorage_SAMD
#include <WiFiManager_NINA_Lite_Debug.h>


#ifndef USING_CUSTOMS_STYLE
  #define USING_CUSTOMS_STYLE     false
#endif

#ifndef USING_CUSTOMS_HEAD_ELEMENT
  #define USING_CUSTOMS_HEAD_ELEMENT     false
#endif

#ifndef USING_CORS_FEATURE
  #define USING_CORS_FEATURE     false
#endif

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

// RTC Memory Address for the DoubleResetDetector_Generic to use
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

#if USE_DYNAMIC_PARAMETERS
  #warning Using Dynamic Parameters
  ///NEW
  extern uint16_t NUM_MENU_ITEMS;
  extern MenuItem myMenuItems [];
  bool *menuItemUpdated = NULL;
#else
  #warning Not using Dynamic Parameters
#endif

#define SSID_MAX_LEN      32
// WPA2 passwords can be up to 63 characters long.
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

#define HEADER_MAX_LEN            16
#define BOARD_NAME_MAX_LEN        24

typedef struct Configuration
{
  char header         [HEADER_MAX_LEN];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [BOARD_NAME_MAX_LEN];
  int  checkSum;
} WiFiNINA_Configuration;

// Currently CONFIG_DATA_SIZE  =   236  = (16 + 96 * 2 + 4 + 24)
uint16_t CONFIG_DATA_SIZE = sizeof(WiFiNINA_Configuration);

extern bool LOAD_DEFAULT_CONFIG_DATA;
extern WiFiNINA_Configuration defaultConfig;

// -- HTML page fragments

const char WIFININA_HTML_HEAD_START[] /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>SAMD_WM_NINA_Lite</title>";

const char WIFININA_HTML_HEAD_STYLE[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

const char WIFININA_HTML_HEAD_END[]   /*PROGMEM*/ = "</head><div style=\"text-align:left;display:inline-block;min-width:260px;\">\
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

//////////////////////////////////////////

//KH Add repeatedly used const
//KH, from v1.1.0
const char WM_HTTP_HEAD_CL[]         PROGMEM = "Content-Length";
const char WM_HTTP_HEAD_TEXT_HTML[]  PROGMEM = "text/html";
const char WM_HTTP_HEAD_TEXT_PLAIN[] PROGMEM = "text/plain";

const char WM_HTTP_CACHE_CONTROL[]   PROGMEM = "Cache-Control";
const char WM_HTTP_NO_STORE[]        PROGMEM = "no-cache, no-store, must-revalidate";
const char WM_HTTP_PRAGMA[]          PROGMEM = "Pragma";
const char WM_HTTP_NO_CACHE[]        PROGMEM = "no-cache";
const char WM_HTTP_EXPIRES[]         PROGMEM = "Expires";

const char WM_HTTP_CORS[]            PROGMEM = "Access-Control-Allow-Origin";
const char WM_HTTP_CORS_ALLOW_ALL[]  PROGMEM = "*";

//////////////////////////////////////////


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
#if USE_WIFI101
      if (WiFi.status() == WL_NO_SHIELD)
#else
      if (WiFi.status() == WL_NO_MODULE)
#endif      
      {
        WN_LOGERROR(F("NoWiFi"));
      }     
    }

    ~WiFiManager_NINA_Lite()
    {
      if (server)
        delete server;
    }
        
    bool connectWiFi(const char* ssid, const char* pass)
    {
      WN_LOGERROR1(F("Con2:"), ssid);
      
      setHostname();

      if ( WiFi.begin(ssid, pass) == WL_CONNECTED )  
      {
        displayWiFiData();
      }
      else
      {
        WN_LOGERROR(F("NoW"));
        return false;
      }

      WN_LOGERROR(F("WOK"));

      wifi_connected = true;

      return true;
    }
   
    void begin(const char* ssid,
               const char* pass )
    {
      WN_LOGERROR(F("conW"));
      connectWiFi(ssid, pass);
    }

    void begin(const char *iHostname = "")
    {
      #define RETRY_TIMES_CONNECT_WIFI			3
      
      if (iHostname[0] == 0)
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();
        
        String _hostname = "SAMD-WiFiNINA-" + randomNum;
        _hostname.toUpperCase();

        getRFC952_hostname(_hostname.c_str());
      }
      else
      {
        // Prepare and store the hostname only not NULL
        getRFC952_hostname(iHostname);
      }
      
      WN_LOGERROR1(F("Hostname="), RFC952_hostname);
      //////
      
      //// New DRD ////
      drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (drd->detectDoubleReset())
      {
        WN_LOGERROR(F("Double Reset Detected"));
     
        noConfigPortal = false;
      }
      //// New DRD ////
      
      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        WN_LOGERROR(F("======= Start Default Config Data ======="));
        displayConfigData(defaultConfig);
      }
      
      hadConfigData = getConfigData();
      
      isForcedConfigPortal = isForcedCP();
        
      //// New DRD/MRD ////
      //  noConfigPortal when getConfigData() OK and no MRD/DRD'ed
      if (hadConfigData && noConfigPortal && (!isForcedConfigPortal) )
      {
        hadConfigData = true;

        if (connectMultiWiFi(RETRY_TIMES_CONNECT_WIFI))
        {
          WN_LOGERROR(F("b:WOK"));
        }
        else
        {
          WN_LOGERROR(F("b:NoW"));
          // failed to connect to WiFi, will start configuration mode
          startConfigurationMode();
        }
      }
      else
      {      
        WN_LOGERROR(isForcedConfigPortal? F("bg: isForcedConfigPortal = true") : F("bg: isForcedConfigPortal = false"));
                     
        // If not persistent => clear the flag so that after reset. no more CP, even CP not entered and saved
        if (persForcedConfigPortal)
        {
          WN_LOGERROR1(F("bg:Stay forever in CP:"), isForcedConfigPortal ? F("Forced-Persistent") : (noConfigPortal ? F("No ConfigDat") : F("DRD/MRD")));
        }
        else
        {
          WN_LOGERROR1(F("bg:Stay forever in CP:"), isForcedConfigPortal ? F("Forced-non-Persistent") : (noConfigPortal ? F("No ConfigDat") : F("DRD/MRD")));
          clearForcedCP();
        }
          
        //To permit autoreset after timeout if DRD/MRD or non-persistent forced-CP 
        hadConfigData = isForcedConfigPortal ? true : (noConfigPortal ? false : true);
        
        // failed to connect to WiFi, will start configuration mode
        startConfigurationMode();
      }
    }


#ifndef RETRY_TIMES_RECONNECT_WIFI
  #define RETRY_TIMES_RECONNECT_WIFI   2
#else
  // Force range of user-defined RETRY_TIMES_RECONNECT_WIFI between 2-5 times
  #if (RETRY_TIMES_RECONNECT_WIFI < 2)
    #warning RETRY_TIMES_RECONNECT_WIFI too low. Reseting to 2
    #undef RETRY_TIMES_RECONNECT_WIFI
    #define RETRY_TIMES_RECONNECT_WIFI   2
  #elif (RETRY_TIMES_RECONNECT_WIFI > 5)
    #warning RETRY_TIMES_RECONNECT_WIFI too high. Reseting to 5
    #undef RETRY_TIMES_RECONNECT_WIFI
    #define RETRY_TIMES_RECONNECT_WIFI   5
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
      static bool wifiDisconnectedOnce = false;
      
      // Lost connection in running. Give chance to reconfig.
      // Check WiFi status every 5s and update status
      // Check twice to be sure wifi disconnected is real
      static unsigned long checkstatus_timeout = 0;
      #define WIFI_STATUS_CHECK_INTERVAL    5000L
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////
         
      if ( !configuration_mode && (millis() > checkstatus_timeout) )
      {       
        if (WiFi.status() == WL_CONNECTED)
        {
          wifi_connected = true;
        }
        else
        {
          if (wifiDisconnectedOnce)
          {
            wifiDisconnectedOnce = false;
            wifi_connected = false;
            WN_LOGERROR(F("r:Check&WLost"));
          }
          else
          {
            wifiDisconnectedOnce = true;
          }
        }
        
        checkstatus_timeout = millis() + WIFI_STATUS_CHECK_INTERVAL;
      }    

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
            //WN_LOGDEBUG(F("r:handleClient"));
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
              WN_LOGERROR1(F("r:WLost&TOut.ConW.Retry#"), retryTimes);
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
            WN_LOGERROR(F("r:WLost.ReconW"));
            
            if (connectMultiWiFi(RETRY_TIMES_RECONNECT_WIFI))
            {
              WN_LOGERROR(F("r:WOK"));
            }
          }
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        WN_LOGERROR(F("r:gotWBack"));
      }
    }
    
    //////////////////////////////////////////////
    
    void setHostname()
    {
      if (RFC952_hostname[0] != 0)
      {
#if USE_WIFI101
        WiFi.hostname(RFC952_hostname);
#elif USE_WIFI_NINA    
        WiFi.setHostname(RFC952_hostname);
#endif        
      }
    }
    
    //////////////////////////////////////////////

    void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
    }
    
    //////////////////////////////////////////////

    #define MIN_WIFI_CHANNEL      1
    #define MAX_WIFI_CHANNEL      11    // Channel 13 is flaky, because of bad number 13 ;-)

    int setConfigPortalChannel(int channel = 1)
    {
      // If channel < MIN_WIFI_CHANNEL - 1 or channel > MAX_WIFI_CHANNEL => channel = 1
      // If channel == 0 => will use random channel from MIN_WIFI_CHANNEL to MAX_WIFI_CHANNEL
      // If (MIN_WIFI_CHANNEL <= channel <= MAX_WIFI_CHANNEL) => use it
      if ( (channel < MIN_WIFI_CHANNEL - 1) || (channel > MAX_WIFI_CHANNEL) )
        AP_channel = 1;
      else if ( (channel >= MIN_WIFI_CHANNEL - 1) && (channel <= MAX_WIFI_CHANNEL) )
        AP_channel = channel;

      return AP_channel;
    }
    
    //////////////////////////////////////////////
    
    void setConfigPortal(String ssid = "", String pass = "")
    {
      portal_ssid = ssid;
      portal_pass = pass;
    }
    
    //////////////////////////////////////////////

    void setSTAStaticIPConfig(IPAddress ip)
    {
      static_IP = ip;
    }
    
    //////////////////////////////////////////////
    
    String getWiFiSSID(uint8_t index)
    { 
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WIFININA_config.WiFi_Creds[index].wifi_ssid));
    }
    
    //////////////////////////////////////////////

    String getWiFiPW(uint8_t index)
    {
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WIFININA_config.WiFi_Creds[index].wifi_pw));
    }
    
    //////////////////////////////////////////////

    bool getWiFiStatus()
    {
      return wifi_connected;
    }
    
    //////////////////////////////////////////////
    
    WiFiNINA_Configuration* getFullConfigData(WiFiNINA_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &WIFININA_config, sizeof(WiFiNINA_Configuration));

      return (configData);
    }
    
    //////////////////////////////////////////////

    String localIP()
    {
      ipAddress = IPAddressToString(WiFi.localIP());

      return ipAddress;
    }
    
    //////////////////////////////////////////////

    void clearConfigData()
    {
      memset(&WIFININA_config, 0, sizeof(WIFININA_config));
      
#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }
#endif

      saveConfigData();
    }
    
    //////////////////////////////////////////////
    
    bool isConfigDataValid()
    {
      return hadConfigData;
    }
    
    //////////////////////////////////////////////
    
    // Forced CP => Flag = 0xBEEFBEEF. Else => No forced CP
    // Flag to be stored at (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE) 
    // to avoid corruption to current data
    //#define FORCED_CONFIG_PORTAL_FLAG_DATA              ( (uint32_t) 0xDEADBEEF)
    //#define FORCED_PERS_CONFIG_PORTAL_FLAG_DATA         ( (uint32_t) 0xBEEFDEAD)
    
    const uint32_t FORCED_CONFIG_PORTAL_FLAG_DATA       = 0xDEADBEEF;
    const uint32_t FORCED_PERS_CONFIG_PORTAL_FLAG_DATA  = 0xBEEFDEAD;
    
    #define FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE     4
    
    void resetAndEnterConfigPortal()
    {
      persForcedConfigPortal = false;
      
      setForcedCP(false);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////
    
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    void resetAndEnterConfigPortalPersistent()
    {
      persForcedConfigPortal = true;
      
      setForcedCP(true);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////

    void resetFunc()
    {    
      // Best one. Possibly don't need the WDT
      NVIC_SystemReset();
      
#if ( defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__)  )
      // For SAMD51
      // see Table 17-5 Timeout Period (valid values 0-11)
      WDT->CONFIG.reg = 5; 
      WDT->CTRLA.reg = WDT_CTRLA_ENABLE;
      // To check if OK or bit.ENABLE/CLEAR
      while (WDT->SYNCBUSY.bit.WEN == 1);
      
      // use the WDT watchdog timer to force a system reset.
      WDT->CLEAR.reg= 0x00;
      // To check if OK or bit.ENABLE/CLEAR
      while (WDT->SYNCBUSY.bit.WEN == 1);
#else   
      // For SAMD21, etc
      // see Table 17-5 Timeout Period (valid values 0-11)
      WDT->CONFIG.reg = 5; 
      WDT->CTRL.reg = WDT_CTRL_ENABLE;
      while (WDT->STATUS.bit.SYNCBUSY == 1);
      
      // use the WDT watchdog timer to force a system reset.
      WDT->CLEAR.reg= 0x00;
      while (WDT->STATUS.bit.SYNCBUSY == 1);
#endif      
    }

    //////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
    // New from v1.1.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"

#if USING_CUSTOMS_STYLE
    //sets a custom style, such as color
    // "<style>div,input{padding:5px;font-size:1em;}
    // input{width:95%;}body{text-align: center;}
    // button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}
    // fieldset{border-radius:0.3rem;margin:0px;}</style>";
    void setCustomsStyle(const char* CustomsStyle = WIFININA_HTML_HEAD_STYLE) 
    {
      WIFININA_HTML_HEAD_CUSTOMS_STYLE = CustomsStyle;
      WN_LOGDEBUG1(F("Set CustomsStyle to : "), WIFININA_HTML_HEAD_CUSTOMS_STYLE);
    }
    
    const char* getCustomsStyle()
    {
      WN_LOGDEBUG1(F("Get CustomsStyle = "), WIFININA_HTML_HEAD_CUSTOMS_STYLE);
      return WIFININA_HTML_HEAD_CUSTOMS_STYLE;
    }
#endif

#if USING_CUSTOMS_HEAD_ELEMENT    
    //sets a custom element to add to head, like a new style tag
    void setCustomsHeadElement(const char* CustomsHeadElement = NULL) 
    {
      _CustomsHeadElement = CustomsHeadElement;
      WN_LOGDEBUG1(F("Set CustomsHeadElement to : "), _CustomsHeadElement);
    }
    
    const char* getCustomsHeadElement()
    {
      WN_LOGDEBUG1(F("Get CustomsHeadElement = "), _CustomsHeadElement);
      return _CustomsHeadElement;
    }
#endif
    
#if USING_CORS_FEATURE   
    void setCORSHeader(const char* CORSHeaders = NULL)
    {     
      _CORS_Header = CORSHeaders;

      WN_LOGDEBUG1(F("Set CORS Header to : "), _CORS_Header);
    }
    
    const char* getCORSHeader()
    {      
      WN_LOGDEBUG1(F("Get CORS Header = "), _CORS_Header);
      return _CORS_Header;
    }
#endif
          
    //////////////////////////////////////


  private:
    String ipAddress = "0.0.0.0";

    WiFiWebServer* server = NULL;
    
    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;
    
    bool isForcedConfigPortal   = false;
    bool persForcedConfigPortal = false;

    WiFiNINA_Configuration WIFININA_config;
    
    uint16_t totalDataSize = 0;

    String macAddress = "";
    bool wifi_connected = false;

    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);
    int AP_channel = 10;

    String portal_ssid = "";
    String portal_pass = "";

    IPAddress static_IP   = IPAddress(0, 0, 0, 0);

    /////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
#if USING_CUSTOMS_STYLE
    const char* WIFININA_HTML_HEAD_CUSTOMS_STYLE = NULL;
#endif
    
#if USING_CUSTOMS_HEAD_ELEMENT
    const char* _CustomsHeadElement = NULL;
#endif
    
#if USING_CORS_FEATURE    
    const char* _CORS_Header        = WM_HTTP_CORS_ALLOW_ALL;   //"*";
#endif
       
    //////////////////////////////////////
    
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
      WN_LOGERROR5(F("Hdr="),   configData.header, F(",SSID="), configData.WiFi_Creds[0].wifi_ssid,
                   F(",PW="),   configData.WiFi_Creds[0].wifi_pw);
      WN_LOGERROR3(F("SSID1="), configData.WiFi_Creds[1].wifi_ssid, F(",PW1="),  configData.WiFi_Creds[1].wifi_pw);     
      WN_LOGERROR1(F("BName="), configData.board_name);
                 
#if USE_DYNAMIC_PARAMETERS     
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        WN_LOGERROR5("i=", i, ",id=", myMenuItems[i].id, ",data=", myMenuItems[i].pdata);
      }
#endif               
    }

    void displayWiFiData()
    {
      WN_LOGERROR3(F("SSID="), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());
      WN_LOGERROR1(F("IP="), localIP() );
    }

#define WIFININA_BOARD_TYPE       "WIFININA"
#define WM_NO_CONFIG              "blank"

// DRD_FLAG_DATA_SIZE is 4, to store DRD flag, defined in DRD
#if (EEPROM_SIZE < DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
  #error EEPROM_SIZE must be > CONFIG_DATA_SIZE.
#endif

#ifndef EEPROM_START
  #define EEPROM_START     0
  #warning EEPROM_START not defined. Set to 0
#else
  #if (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE)
    #error EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif

// Stating positon to store Blynk8266_WM_config
#define CONFIG_EEPROM_START    (EEPROM_START + DRD_FLAG_DATA_SIZE)

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(WIFININA_config) - sizeof(WIFININA_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &WIFININA_config ) + index);
      }

      return checkSum;
    }
    
    //////////////////////////////////////////////
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;
    
      WN_LOGERROR(isPersistent ? F("setForcedCP Persistent") : F("setForcedCP non-Persistent"));

      EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);      
      EEPROM.commit();
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, 0);     
      EEPROM.commit();
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;

      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false
      EEPROM.get(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
     
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////
    
#if USE_DYNAMIC_PARAMETERS
    
    bool checkDynamicData(void)
    {
      // It's too bad that emulate EEPROM.read()/write() can only deal with bytes. 
      // Have to read/write each byte. To rewrite the library
      
      int checkSum = 0;
      int readCheckSum;
      
      uint16_t offset = CONFIG_EEPROM_START + sizeof(WIFININA_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      #define BUFFER_LEN      128
      char readBuffer[BUFFER_LEN + 1];
                     
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > BUFFER_LEN)
        {
          // Size too large, abort and flag false
          WN_LOGERROR(F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
         
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;
        
        // Prepare buffer, more than enough
        memset(readBuffer, 0, sizeof(readBuffer));
        
        // Read more than necessary, but OK and easier to code
        EEPROM.get(offset, readBuffer);
        // NULL terminated
        readBuffer[myMenuItems[i].maxlen] = 0;
   
        WN_LOGDEBUG3(F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);      
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }   
        
        offset += myMenuItems[i].maxlen;    
      }

      EEPROM.get(offset, readCheckSum);
                  
      WN_LOGERROR3(F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////
    
    bool EEPROM_getDynamicData()
    {          
      int checkSum = 0;
      int readCheckSum;
      
      totalDataSize = sizeof(WIFININA_config) + sizeof(readCheckSum);
          
      // Using FORCED_CONFIG_PORTAL_FLAG_DATA
      //offset += FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      uint16_t offset = CONFIG_EEPROM_START + sizeof(WIFININA_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      
      uint8_t* _pointer;
   
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        _pointer = (uint8_t *) myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, offset++)
        {
          *_pointer = EEPROM.read(offset);          
          checkSum += *_pointer;  
        }       
      }

      EEPROM.get(offset, readCheckSum);
         
      WN_LOGERROR3(F("CrCCSum="), String(checkSum, HEX), F(",CrRCSum="), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
     
      return true;
    }
    
    //////////////////////////////////////////////
    
    void EEPROM_putDynamicData()
    {
      // It's too bad that emulate EEPROM.read()/writ() can only deal with bytes. 
      // Have to read/write each byte. To rewrite the library          
      int checkSum = 0;
      
      // Using FORCED_CONFIG_PORTAL_FLAG_DATA
      //offset += FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      uint16_t offset = CONFIG_EEPROM_START + sizeof(WIFININA_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      uint8_t* _pointer;
    
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        _pointer = (uint8_t *) myMenuItems[i].pdata;
      
        WN_LOGDEBUG3(F("pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          EEPROM.write(offset, *_pointer);
          
          checkSum += *_pointer;     
        }
      }

      EEPROM.put(offset, checkSum);
     
      WN_LOGERROR1(F("CrCCSum=0x"), String(checkSum, HEX));
      
      EEPROM.commit();
    }

#endif

    //////////////////////////////////////////////
 
    void NULLTerminateConfig()
    {
      //#define HEADER_MAX_LEN      16
      //#define SERVER_MAX_LEN      32
      //#define TOKEN_MAX_LEN       36
      
      // NULL Terminating to be sure
      WIFININA_config.header[HEADER_MAX_LEN - 1] = 0;
      WIFININA_config.WiFi_Creds[0].wifi_ssid[SSID_MAX_LEN - 1] = 0;
      WIFININA_config.WiFi_Creds[0].wifi_pw  [PASS_MAX_LEN - 1] = 0;
      WIFININA_config.WiFi_Creds[1].wifi_ssid[SSID_MAX_LEN - 1] = 0;
      WIFININA_config.WiFi_Creds[1].wifi_pw  [PASS_MAX_LEN - 1] = 0;
      WIFININA_config.board_name[BOARD_NAME_MAX_LEN - 1]  = 0;
    }
            
    //////////////////////////////////////////////
    
    bool EEPROM_get()
    {      
      EEPROM.get(CONFIG_EEPROM_START, WIFININA_config);
      
      NULLTerminateConfig();
      
      return true;
    }
    
    //////////////////////////////////////////////
    
    void EEPROM_put()
    {
      EEPROM.put(CONFIG_EEPROM_START, WIFININA_config);
      EEPROM.commit();      
    }
    
    //////////////////////////////////////////////
    
    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      WIFININA_config.checkSum = calChecksum;
      
      WN_LOGERROR5(F("SaveEEPROM,Sz="), EEPROM.length(), F(",DataSz="), totalDataSize, F(",WCSum=0x"), String(calChecksum, HEX));
      
      EEPROM_put();
      
#if USE_DYNAMIC_PARAMETERS        
      EEPROM_putDynamicData();
#endif
    }
    
    //////////////////////////////////////////////
    
    void loadAndSaveDefaultConfigData()
    {
      // Load Default Config Data from Sketch
      memcpy(&WIFININA_config, &defaultConfig, sizeof(WIFININA_config));
      strcpy(WIFININA_config.header, WIFININA_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
          
      WN_LOGERROR(F("======= Start Loaded Config Data ======="));
      displayConfigData(WIFININA_config);    
    }
    
    //////////////////////////////////////////////
    
    bool getConfigData()
    {
      bool dynamicDataValid = true;
      int calChecksum; 
      
      hadConfigData = false; 
      
      // Use new LOAD_DEFAULT_CONFIG_DATA logic
      if (LOAD_DEFAULT_CONFIG_DATA)
      {     
        // Load Config Data from Sketch
        loadAndSaveDefaultConfigData();
        
        // Don't need Config Portal anymore
        return true; 
      }
      else
      {   
        // Get config data
        EEPROM_get();
        
        // Verify ChkSum
        calChecksum = calcChecksum();

        WN_LOGERROR3(F("CCSum=0x"), String(calChecksum, HEX),
                     F(",RCSum=0x"), String(WIFININA_config.checkSum, HEX));
        
#if USE_DYNAMIC_PARAMETERS        
        // Load stored dynamic data from EEPROM
        dynamicDataValid = checkDynamicData();              
#endif
       
        // If checksum = 0 => FlashStorage has been cleared (by uploading new FW, etc) => force to CP
        if ( (calChecksum != 0) && (calChecksum == WIFININA_config.checkSum) )
        {           
          if (dynamicDataValid)
          {
#if USE_DYNAMIC_PARAMETERS          
            // CkSum verified, Now get valid config/ dynamic data
            EEPROM_getDynamicData();
            
            WN_LOGERROR(F("Valid Stored Dynamic Data"));
#endif            
            WN_LOGERROR(F("======= Start Stored Config Data ======="));
            displayConfigData(WIFININA_config);
            
            // Don't need Config Portal anymore
            return true;
          }
          else
          {
            // Invalid Stored config data => Config Portal
            WN_LOGERROR(F("Invalid Stored Dynamic Data. Load default from Sketch"));
            
            // Load Default Config Data from Sketch, better than just "blank"
            loadAndSaveDefaultConfigData();
                             
            // Need Config Portal here as data can be just dummy
            // Even if you don't open CP, you're OK on next boot if your default config data is valid 
            return false;
          }      
        }
      }

      if ( (strncmp(WIFININA_config.header, WIFININA_BOARD_TYPE, strlen(WIFININA_BOARD_TYPE)) != 0) ||
           (calChecksum != WIFININA_config.checkSum) || !dynamicDataValid || 
           ( (calChecksum == 0) && (WIFININA_config.checkSum == 0) ) )   
      {
        // Including Credentials CSum
        WN_LOGERROR1(F("InitCfgFile,sz="), sizeof(WIFININA_config));

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&WIFININA_config, &defaultConfig, sizeof(WIFININA_config));
        }
        else
        {
          memset(&WIFININA_config, 0, sizeof(WIFININA_config));

#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
#endif
              
          strcpy(WIFININA_config.WiFi_Creds[0].wifi_ssid,   WM_NO_CONFIG);
          strcpy(WIFININA_config.WiFi_Creds[0].wifi_pw,     WM_NO_CONFIG);
          strcpy(WIFININA_config.WiFi_Creds[1].wifi_ssid,   WM_NO_CONFIG);
          strcpy(WIFININA_config.WiFi_Creds[1].wifi_pw,     WM_NO_CONFIG);
          strcpy(WIFININA_config.board_name, WM_NO_CONFIG);
          
#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif          
        }
    
        strcpy(WIFININA_config.header, WIFININA_BOARD_TYPE);
        
#if USE_DYNAMIC_PARAMETERS
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          WN_LOGDEBUG3(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
#endif
        
        // Don't need
        WIFININA_config.checkSum = 0;

        saveConfigData();
        
        return false;   
      }
      else if ( !strncmp(WIFININA_config.WiFi_Creds[0].wifi_ssid,       WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WIFININA_config.WiFi_Creds[0].wifi_pw,         WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WIFININA_config.WiFi_Creds[1].wifi_ssid,       WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(WIFININA_config.WiFi_Creds[1].wifi_pw,         WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strlen(WIFININA_config.WiFi_Creds[0].wifi_ssid) || 
                !strlen(WIFININA_config.WiFi_Creds[1].wifi_ssid) ||
                !strlen(WIFININA_config.WiFi_Creds[0].wifi_pw)   ||
                !strlen(WIFININA_config.WiFi_Creds[1].wifi_pw)  )
      {
        // If SSID, PW ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(WIFININA_config);
      }

      return true;
    }

    //////////////////////////////////////////////
    
    bool connectMultiWiFi(int retry_time)
    {
      int sleep_time  = 250;
      int index       = 0;
      uint8_t status;
                       
      static int lastConnectedIndex = 255;

      WN_LOGDEBUG(F("ConMultiWifi"));

      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        WN_LOGDEBUG(F("UseStatIP"));
        WiFi.config(static_IP);
      }
    
      if (lastConnectedIndex != 255)
      {
        index = (lastConnectedIndex + 1) % NUM_WIFI_CREDENTIALS;                       
        WN_LOGDEBUG3(F("Using index="), index, F(", lastConnectedIndex="), lastConnectedIndex);
      }
      
      WN_LOGERROR3(F("con2WF:SSID="), WIFININA_config.WiFi_Creds[index].wifi_ssid,
                F(",PW="), WIFININA_config.WiFi_Creds[index].wifi_pw);
             
      while ( !wifi_connected && ( 0 < retry_time ) )
      {      
        WN_LOGDEBUG1(F("Remaining retry_time="), retry_time);
        
        status = WiFi.begin(WIFININA_config.WiFi_Creds[index].wifi_ssid, WIFININA_config.WiFi_Creds[index].wifi_pw); 
            
        // Need restart WiFi at beginning of each cycle 
        if (status == WL_CONNECTED)
        {
          wifi_connected = true;          
          lastConnectedIndex = index;                                     
          WN_LOGDEBUG1(F("WOK, lastConnectedIndex="), lastConnectedIndex);
          
          break;
        }
        else
        {
          delay(sleep_time);
          retry_time--;
        }         
      }
          
      if (retry_time <= 0)
      {      
        WN_LOGERROR3(F("Failed using index="), index, F(", retry_time="), retry_time);             
      }  

      if (wifi_connected)
      {
        WN_LOGERROR(F("con2WF:OK"));
        displayWiFiData();
      }
      else
      {
        WN_LOGERROR(F("con2WF:failed"));  
        // Can't connect, so try another index next time. Faking this index is OK and lost
        lastConnectedIndex = index;  
      }

      return wifi_connected;  
    }

    //////////////////////////////////////////////
    
    // NEW
    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template  = WIFININA_HTML_HEAD_START;
      
  #if USING_CUSTOMS_STYLE
      // Using Customs style when not NULL
      if (WIFININA_HTML_HEAD_CUSTOMS_STYLE)
        root_html_template  += WIFININA_HTML_HEAD_CUSTOMS_STYLE;
      else
        root_html_template  += WIFININA_HTML_HEAD_STYLE;
  #else     
      root_html_template  += WIFININA_HTML_HEAD_STYLE;
  #endif
      
  #if USING_CUSTOMS_HEAD_ELEMENT
      if (_CustomsHeadElement)
        root_html_template += _CustomsHeadElement;
  #endif          
      
      root_html_template += String(WIFININA_HTML_HEAD_END) + WIFININA_FLDSET_START;
   
#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(WIFININA_HTML_PARAM);

        pitem.replace("{b}", myMenuItems[i].displayName);
        pitem.replace("{v}", myMenuItems[i].id);
        pitem.replace("{i}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(WIFININA_FLDSET_END) + WIFININA_HTML_BUTTON + WIFININA_HTML_SCRIPT;     

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(WIFININA_HTML_SCRIPT_ITEM);
        
        pitem.replace("{d}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(WIFININA_HTML_SCRIPT_END) + WIFININA_HTML_END;
      
      return;     
    }
       
    //////////////////////////////////////////////

    void serverSendHeaders()
    {
      WN_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_CACHE_CONTROL:"), WM_HTTP_CACHE_CONTROL, "=", WM_HTTP_NO_STORE);
      server->sendHeader(WM_HTTP_CACHE_CONTROL, WM_HTTP_NO_STORE);
      
#if USING_CORS_FEATURE
      // New from v1.1.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"
      WN_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_CORS:"), WM_HTTP_CORS, " : ", _CORS_Header);
      server->sendHeader(WM_HTTP_CORS, _CORS_Header);
#endif
     
      WN_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_PRAGMA:"), WM_HTTP_PRAGMA, " : ", WM_HTTP_NO_CACHE);
      server->sendHeader(WM_HTTP_PRAGMA, WM_HTTP_NO_CACHE);
      
      WN_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_EXPIRES:"), WM_HTTP_EXPIRES, " : ", "-1");
      server->sendHeader(WM_HTTP_EXPIRES, "-1");
    }
       
    //////////////////////////////////////////////

    void handleRequest()
    {
      if (server)
      {        
        String key    = server->arg("key");
        String value  = server->arg("value");

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          // New from v1.1.0         
          serverSendHeaders();        
          //////
          
          String result;
          createHTML(result);

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          if ( RFC952_hostname[0] != 0 )
          {
            // Replace only if Hostname is valid
            result.replace("SAMD_WM_NINA_Lite", RFC952_hostname);
          }
          else if ( WIFININA_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("SAMD_WM_NINA_Lite", WIFININA_config.board_name);
          }

          result.replace("[[id]]",     WIFININA_config.WiFi_Creds[0].wifi_ssid);
          result.replace("[[pw]]",     WIFININA_config.WiFi_Creds[0].wifi_pw);
          result.replace("[[id1]]",    WIFININA_config.WiFi_Creds[1].wifi_ssid);
          result.replace("[[pw1]]",    WIFININA_config.WiFi_Creds[1].wifi_pw);
          result.replace("[[nm]]",     WIFININA_config.board_name);
          
#if USE_DYNAMIC_PARAMETERS          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
          }
#endif


          WN_LOGDEBUG1(F("h:HTML page size:"), result.length());
          WN_LOGDEBUG1(F("h:HTML="), result);
          
          server->send(200, "text/html", result);

          return;
        }

        if (number_items_Updated == 0)
        {
          memset(&WIFININA_config, 0, sizeof(WIFININA_config));
          strcpy(WIFININA_config.header, WIFININA_BOARD_TYPE);
        }

#if USE_DYNAMIC_PARAMETERS
        if (!menuItemUpdated)
        {
          // Don't need to free
          menuItemUpdated = new bool[NUM_MENU_ITEMS];
          
          if (menuItemUpdated)
          {
            for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
            {           
              // To flag item is not yet updated
              menuItemUpdated[i] = false;       
            }
            
            WN_LOGDEBUG1(F("h: Init menuItemUpdated :" ), NUM_MENU_ITEMS);                    
          }
          else
          {
            WN_LOGERROR(F("h: Error can't alloc memory for menuItemUpdated" ));
          }
        }  
#endif

        static bool id_Updated  = false;
        static bool pw_Updated  = false;
        static bool id1_Updated = false;
        static bool pw1_Updated = false;
        static bool nm_Updated  = false;
          
        if (!id_Updated && (key == String("id")))
        {   
          WN_LOGDEBUG(F("h:repl id"));
          id_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFININA_config.WiFi_Creds[0].wifi_ssid) - 1)
            strcpy(WIFININA_config.WiFi_Creds[0].wifi_ssid, value.c_str());
          else
            strncpy(WIFININA_config.WiFi_Creds[0].wifi_ssid, value.c_str(), sizeof(WIFININA_config.WiFi_Creds[0].wifi_ssid) - 1);
        }
        else if (!pw_Updated && (key == String("pw")))
        {    
          WN_LOGDEBUG(F("h:repl pw"));
          pw_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFININA_config.WiFi_Creds[0].wifi_pw) - 1)
            strcpy(WIFININA_config.WiFi_Creds[0].wifi_pw, value.c_str());
          else
            strncpy(WIFININA_config.WiFi_Creds[0].wifi_pw, value.c_str(), sizeof(WIFININA_config.WiFi_Creds[0].wifi_pw) - 1);
        }
        else if (!id1_Updated && (key == String("id1")))
        {   
          WN_LOGDEBUG(F("h:repl id1"));
          id1_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFININA_config.WiFi_Creds[1].wifi_ssid) - 1)
            strcpy(WIFININA_config.WiFi_Creds[1].wifi_ssid, value.c_str());
          else
            strncpy(WIFININA_config.WiFi_Creds[1].wifi_ssid, value.c_str(), sizeof(WIFININA_config.WiFi_Creds[1].wifi_ssid) - 1);
        }
        else if (!pw1_Updated && (key == String("pw1")))
        {    
          WN_LOGDEBUG(F("h:repl pw1"));
          pw1_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFININA_config.WiFi_Creds[1].wifi_pw) - 1)
            strcpy(WIFININA_config.WiFi_Creds[1].wifi_pw, value.c_str());
          else
            strncpy(WIFININA_config.WiFi_Creds[1].wifi_pw, value.c_str(), sizeof(WIFININA_config.WiFi_Creds[1].wifi_pw) - 1);
        }
        else if (!nm_Updated && (key == String("nm")))
        {
          WN_LOGDEBUG(F("h:repl nm"));
          nm_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WIFININA_config.board_name) - 1)
            strcpy(WIFININA_config.board_name, value.c_str());
          else
            strncpy(WIFININA_config.board_name, value.c_str(), sizeof(WIFININA_config.board_name) - 1);
        }
        else
        {
        
#if USE_DYNAMIC_PARAMETERS        
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {           
            if ( !menuItemUpdated[i] && (key == myMenuItems[i].id) )
            {
              WN_LOGDEBUG3(F("h:"), myMenuItems[i].id, F("="), value.c_str() );
              
              menuItemUpdated[i] = true;
              
              number_items_Updated++;

              // Actual size of pdata is [maxlen + 1]
              memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

              if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
                strcpy(myMenuItems[i].pdata, value.c_str());
              else
                strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
                
              break;  
            }
          }
#endif
        }
        
        WN_LOGDEBUG1(F("h:items updated ="), number_items_Updated);
        WN_LOGDEBUG3(F("h:key ="), key, ", value =", value);

        server->send(200, "text/html", "OK");

#if USE_DYNAMIC_PARAMETERS        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
#else
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
#endif 
        {
          WN_LOGERROR(F("h:UpdEEPROM"));

          saveConfigData();
          
          // Done with CP, Clear CP Flag here if forced
          if (isForcedConfigPortal)
            clearForcedCP();

          WN_LOGERROR(F("h:Rst"));

          // TO DO : what command to reset
          // Delay then reset the board after save data
          delay(1000);
          resetFunc();  //call reset
        }
      }   // if (server)
    }
    
    //////////////////////////////////////////////

#ifndef CONFIG_TIMEOUT
  #warning Default CONFIG_TIMEOUT = 60s
  #define CONFIG_TIMEOUT			60000L
#endif

    void startConfigurationMode()
    {
      WiFi.config(portal_apIP);

      if ( (portal_ssid == "") || portal_pass == "" )
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();

        portal_ssid = "WIFININA_" + randomNum;
        portal_pass = "MyWIFININA_" + randomNum;
      }
      
      // start access point, AP only, channel 10
           
      uint16_t channel;
     
      // Use random channel if  AP_channel == 0     
      if (AP_channel == 0)
        channel = (millis() % MAX_WIFI_CHANNEL) + 1;
      else
        channel = AP_channel;

      WN_LOGERROR3(F("SSID="), portal_ssid, F(",PW="), portal_pass);
      WN_LOGERROR3(F("IP="), portal_apIP, F(",CH="), channel);

#if USE_ESP_AT_SHIELD
      // start access point, AP only,default channel 10
      WiFi.beginAP(portal_ssid.c_str(), channel, portal_pass.c_str(), ENC_TYPE_WPA2_PSK, true);
#else
      // start access point, AP only,default channel 10
      WiFi.beginAP(portal_ssid.c_str(), portal_pass.c_str(), channel);
#endif
      

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
      {
        configTimeout = millis() + CONFIG_TIMEOUT;
                      
        WN_LOGDEBUG3(F("s:millis() = "), millis(), F(", configTimeout = "), configTimeout);
      }
      else
      {
        configTimeout = 0;
               
        WN_LOGDEBUG(F("s:configTimeout = 0"));    
      }

      configuration_mode = true;
    }
};


#endif    //WiFiManager_NINA_Lite_SAMD_h
