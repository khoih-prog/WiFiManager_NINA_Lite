## WiFiManager_NINA_Lite (Light Weight Credentials / WiFi Manager for WiFiNINA modules/shields)

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_NINA_Lite.svg?)](https://www.ardu-badge.com/WiFiManager_NINA_Lite)

#### New in v1.0.1

1. Use new  [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic) to provide support to many more boards (Teensy, AVR Mega, SAM DUE, SAMD51, STM32, etc.) running WiFiNINA. The original WiFiNINA library only supports Nano-33 IoT, Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2.
2. Use new [`FlashStorage_SAMD library`](https://github.com/khoih-prog/FlashStorage_SAMD) to provide EEPROM/FlashStorage support to SAMD51 boards (Itsy-Bitsy M4, etc).

#### New in v1.0.0

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM, SAMD EEPROM-emulated FlashStorage or SAM DUE DueFlashStorage***.

## Features

This library is a Light Weight Credentials / WiFi Manager for WiFiNINA modules/shields, specially designed to support ***Teensy, SAM DUE, SAMD (Nano-33 IoT, etc), STM32, etc. boards running WiFiNINA modules/shields.*** with smaller memory (64+K bytes)

The AVR-family boards (UNO, Nano, etc.) are ***not supported*** as they don't have enough memory to run Config Portal WebServer.

This is a Credentials / WiFi Connection Manager, permitting the addition of custom parameters to be configured in Config Portal. The parameters then will be saved automatically, ***without the complicated callback functions*** to handle data saving / retrieving.

If you have used the full-fledge WiFiManager such as :
1. [`Tzapu WiFiManager`](https://github.com/tzapu/WiFiManager)
2. [`Ken Taylor WiFiManager`](https://github.com/kentaylor/WiFiManager)
3. [`ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager)

and have to write complicated callback functions to save custom parameters in SPIFFS, you'd appreciate the simplicity of this Light-Weight Credentials / WiFiManager

The web configuration portal, served from the `WiFiNINA modules/shields` is operating as an access point (AP) with configurable static IP address or use default IP Address of 192.168.4.1

## Prerequisite
 1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 3. [`Teensy core 1.51 or later`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 4. [`Arduino SAM DUE core 1.6.12 or later`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.5 or later`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 6. [`Adafruit SAMD core 1.5.11 or later`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 7. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 8. [`Functional-VLPP library`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
 9. [`WiFiNINA_Generic library v1.5.0 or later`](https://github.com/khoih-prog/WiFiNINA_Generic)
10. [`WiFiWebServer library v1.0.1 or later`](https://github.com/khoih-prog/WiFiWebServer)
11. [`FlashStorage_SAMD library v1.0.0`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
12. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE


## How It Works

- The [SAMD_WiFiNINA](examples/SAMD_WiFiNINA) example shows how it works and should be used as the basis for a sketch that uses this library.
- The concept of [SAMD_WiFiNINA](examples/SAMD_WiFiNINA) is that a new `WiFiNINA module/shield` will start a WiFi configuration portal when powered up, but has no valid stored Credentials. 
- There are 6 more custom parameters added in the sketch which you can use in your program later. In the example, they are: 2 sets of Blynk Servers and Tokens, Blynk Port and MQTT Server.
- Using any WiFi enabled device with a browser (computer, phone, tablet) connect to the newly created AP and type in the configurable AP IP address (default 192.168.4.1). The Config Portal AP channel (default 10) is also configurable to avoid conflict with other APs.
- The Config Portal is auto-adjusted to fix the 2 static parameters (WiFi SSID/PWD) as well as 6 more dynamic custom parameters.
- After the custom data entered, and `Save` button pressed, the configuration data will be saved in host's non-volatile memory, then the board reboots.
- If there is valid stored Credentials, it'll go directly to connect to WiFi without starting / using the Config Portal.
- `WiFiNINA module/shield` will try to connect. If successful, the dynamic DHCP or configured static IP address will be displayed in the configuration portal. 
- The `WiFiNINA module/shield` WiFi Config Portal network and Web Server will shutdown to return control to the sketch code.

## Quick Start

The best and easiest way is to use `Arduino Library Manager`. Search for `WiFiManager_NINA_Lite`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_NINA_Lite.svg?)](https://www.ardu-badge.com/WiFiManager_NINA_Lite) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite) page.
2. Download the latest release `WiFiManager_NINA_Lite-master.zip`.
3. Extract the zip file to `WiFiManager_NINA_Lite-master` directory 
4. Copy whole `WiFiManager_NINA_Lite-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### Using
- Include in your sketch

```cpp
// Must be before #include <WiFiManager_NINA_Lite_SAMD.h>
// Start location in EEPROM to store config data. Default 0
// Config data Siz, not including your custom data, currently is 84 bytes)
#define EEPROM_START      0

#include <WiFiManager_NINA_Lite_SAMD.h>

WiFiManager_NINA_Lite* WiFiManager_NINA;
```

- To add custom parameters, just add

```
#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN]  = "";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN]   = "";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN]  = "";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN]   = "";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN]  = "";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN]   = "";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "pt", "Port",           Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mq", "MQTT Server",    MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

```

- If you don't need to add dynamic parameters, use the following in sketch

```
/////////////// Start dynamic Credentials ///////////////

MenuItem myMenuItems [] =
{
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;
/////// // End dynamic Credentials ///////////

```

- When you want to open a config portal, just add

```cpp
WiFiManager_NINA = new WiFiManager_NINA_Lite();
WiFiManager_NINA->begin();
```

- To not use default AP WiFi Channel 10 to avoid conflict with other WiFi APs, call 
```cpp
WiFiManager_NINA->setConfigPortalChannel(newChannel);
```

- To use different static AP IP (not use default `192.168.4.1`), call 
```cpp
WiFiManager_NINA->setConfigPortalIP(IPAddress(xxx,xxx,xxx,xxx));
```

While in AP mode, connect to it using its `SSID` (WIFININA_XXXXXX) / `Password` ("MyWIFININA_XXXXXX"), then open a browser to the Portal AP IP, default `192.168.4.1`, configure wifi then save. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect.


OnceCredentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.


Also see examples: 
1. [SAMD_WiFiNINA](examples/SAMD_WiFiNINA)
2. [Teensy40_WiFiNINA](examples/Teensy40_WiFiNINA)
3. [STM32_WiFiNINA](examples/STM32_WiFiNINA)
4. [SAM_DUE_WiFiNINA](examples/SAM_DUE_WiFiNINA)
5. [Mega_WiFiNINA](examples/Mega_WiFiNINA)


## So, how it works?
In `Configuration Portal Mode`, it starts an AP called `WIFININA_XXXXXX`. Connect to it using the `configurable password` you can define in the code. For example, `MyWIFININA_XXXXXX` (see examples):

After you connected, please, go to http://192.168.4.1 or newly configured AP IP, you'll see this `Main` page:

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_NINA_Lite/blob/master/pics/Main.png">
</p>

Enter your credentials, 

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_NINA_Lite/blob/master/pics/Input.png">
</p>

then click `Save`. 

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_NINA_Lite/blob/master/pics/Save.png">
</p>

The WiFi Credentials will be saved and the board connect to the selected WiFi AP.

If you're already connected to a listed WiFi AP and don't want to change anything, just select `Exit` from the `Main` page to reboot the board and connect to the previously-stored AP. The WiFi Credentials are still intact.


#### On Demand Configuration Portal

Sample Code

```cpp
/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT Serial
#define WIFININA_DEBUG_OUTPUT     Serial

#define WIFININA_DEBUG    true

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) /*|| defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__)*/  )
#if defined(WIFININA_USE_SAMD)
#undef WIFININA_USE_SAMD
#endif
#define WIFININA_USE_SAMD      true
#else
#error This code is intended to run only on the SAMD boards ! Please check your Tools->Board setting.
#endif

#if defined(WIFININA_USE_SAMD)

#if defined(ARDUINO_SAMD_ZERO)
#define BOARD_TYPE      "SAMD Zero"
#elif defined(ARDUINO_SAMD_MKR1000)
#define BOARD_TYPE      "SAMD MKR1000"
#elif defined(ARDUINO_SAMD_MKRWIFI1010)
#define BOARD_TYPE      "SAMD MKRWIFI1010"
#elif defined(ARDUINO_SAMD_NANO_33_IOT)
#define BOARD_TYPE      "SAMD NANO_33_IOT"
#elif defined(ARDUINO_SAMD_MKRFox1200)
#define BOARD_TYPE      "SAMD MKRFox1200"
#elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
#define BOARD_TYPE      "SAMD MKRWAN13X0"
#elif defined(ARDUINO_SAMD_MKRGSM1400)
#define BOARD_TYPE      "SAMD MKRGSM1400"
#elif defined(ARDUINO_SAMD_MKRNB1500)
#define BOARD_TYPE      "SAMD MKRNB1500"
#elif defined(ARDUINO_SAMD_MKRVIDOR4000)
#define BOARD_TYPE      "SAMD MKRVIDOR4000"
#elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
#define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
#elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
#define BOARD_TYPE      "SAMD ADAFRUIT_ITSYBITSY_M4_EXPRESS"
#elif ( defined(__SAMD21G18A__) || (__SAM3X8E__) || (__CPU_ARC__) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) )
#define BOARD_TYPE      "SAMD Board"
#else
#define BOARD_TYPE      "SAMD Unknown"
#endif
#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START      0

#include <WiFiManager_NINA_Lite_SAMD.h>

#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN]  = "";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN]   = "";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN]  = "";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN]   = "";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN]  = "";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN]   = "";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "pt", "Port",           Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mq", "MQTT Server",    MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

void heartBeatPrint(void)
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print("H");        // H means connected to WiFi
  else
    Serial.print("F");        // F means not connected to WiFi

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(" ");
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

  //KH
#define HEARTBEAT_INTERVAL    600000L
  // Print hearbeat every HEARTBEAT_INTERVAL (600) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

WiFiManager_NINA_Lite* WiFiManager_NINA;

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("\nStart SAMD_WiFiNINA on " + String(BOARD_TYPE));


  WiFiManager_NINA = new WiFiManager_NINA_Lite();

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //WiFiManager_NINA->setConfigPortalIP(IPAddress(192, 168, 120, 1));
  //WiFiManager_NINA->setConfigPortalChannel(1);

  WiFiManager_NINA->begin();
}

void displayCredentials(void)
{
  Serial.println("Your stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}

void loop()
{
  WiFiManager_NINA->run();

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

  check_status();
}
```

This is the terminal output when running [SAMD_WiFiNINA](examples/SAMD_WiFiNINA) example on ***Nano-33 IoT***:

1. Open Config Portal

```

Start SAMD_WiFiNINA on SAMD NANO_33_IOT
*NN: CrCCsum=6217,CrRCsum=825255525
*NN: CCSum=1983,RCSum=1752461166
*NN: InitEEPROM,sz=1080,Datasz=264
*NN: pdata=blank,len=34
*NN: pdata=blank,len=34
*NN: pdata=blank,len=34
*NN: pdata=blank,len=34
*NN: pdata=blank,len=6
*NN: pdata=blank,len=34
*NN: CrCCSum=3120
*NN: b:OpenPortal
*NN: SSID=WIFININA_E50AB22C,PW=MyWIFININA_E50AB22C
*NN: IP=192.168.4.1,CH=1
Your stored Credentials :
Blynk Server1 = blank
Token1 = blank
Blynk Server2 = blank
Token2 = blank
Port = blank
MQTT Server = blank
FFF
```

2. Got valid Credential from Config Portal, then connected to WiFi

```
Start SAMD_WiFiNINA on SAMD NANO_33_IOT
*NN: CrCCSum=7558,CrRCSum=7558
*NN: CCSum=2104,RCSum=2104
*NN: Hdr=WIFININA,SSID=HueNet1,PW=****
*NN: i=0,id=sv1,data=blynk1.duckdns.org
*NN: i=1,id=tk1,data=your-token1
*NN: i=2,id=sv2,data=blynk2.duckdns.org
*NN: i=3,id=tk2,data=your-token2
*NN: i=4,id=pt,data=8080
*NN: i=5,id=mq,data=mqtt.duckdns.org
*NN: con2WF:start
*NN: con2WF:spentMsec=0
*NN: Con2:HueNet1
*NN: IP=192.168.2.139
*NN: WOK
*NN: con2WF:OK
*NN: IP=192.168.2.139
*NN: b:WOK
Your stored Credentials :
Blynk Server1 = blynk1.duckdns.org
Token1 = your-token1
Blynk Server2 = blynk2.duckdns.org
Token2 = your-token2
Port = 8080
MQTT Server = mqtt.duckdns.org
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH

```

#### Debug
Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT Serial

#define WIFININA_DEBUG_OUTPUT    false
```

## Troubleshooting
If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `WiFiNINA module/shield` or this library version.

Sometimes, the library will only work if you update the `WiFiNINA module/shield` core to the newer or older version because some function compatibility.

### TO DO

1. Too many things to list, EEPROM, SPIFFS/FS/FAT FS (if available)
2. Find better and easier way to add more parameters.


#### New in v1.0.1

1. Use new  [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic) to provide support to many more boards (Teensy, AVR Mega, SAM DUE, SAMD51, STM32, etc.) running WiFiNINA. The original WiFiNINA library only supports Nano-33 IoT, Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2.
2. Use new [`FlashStorage_SAMD library`](https://github.com/khoih-prog/FlashStorage_SAMD) to provide EEPROM/FlashStorage support to SAMD51 boards (Itsy-Bitsy M4, etc).

#### New in v1.0.0

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM, SAMD EEPROM-emulated FlashStorage or SAM DUE DueFlashStorage***.
3. This is a Light-Weight Credentials / WiFi Connection Manager with fallback web configuration portal. Completely new to support ***Teensy, SAM DUE, SAMD, STM32, etc. boards running WiFiNINA modules/shields.*** with small memory (64+K bytes)
4. Config Portal AP SSID and Password will use 4 bytes of hardware unique macAddress, only for Teensy.

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

### Copyright

Copyright 2020- Khoi Hoang


