/*********************************************************************************************************************************
  nRF52840_WiFiNINA_MQTT.ino
  For nRF52 boards using WiFiNINA modules/shields, using much less code to support boards with smaller memory
  
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

/****************************************************************************************************************************
  You have to modify file ./libraries/Adafruit_MQTT_Library/Adafruit_MQTT.cpp  as follows to avoid dtostrf error
   
  //#if defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) ||             \
  //    defined(ARDUINO_ARCH_SAMD)
  #if !( ESP32 || ESP8266 || defined(CORE_TEENSY) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3) || defined(STM32F4) || defined(STM32F7) )
  static char *dtostrf(double val, signed char width, unsigned char prec, char *sout) 
  {
    char fmt[20];
    sprintf(fmt, "%%%d.%df", width, prec);
    sprintf(sout, fmt, val);
    return sout;
  }
  #endif
 *****************************************************************************************************************************/

#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

#define LOCAL_DEBUG       true  //false

#include "Adafruit_MQTT.h"                //https://github.com/adafruit/Adafruit_MQTT_Library
#include "Adafruit_MQTT_Client.h"         //https://github.com/adafruit/Adafruit_MQTT_Library

// Create a WiFiClient class to connect to the MQTT server
WiFiClient *client                    = NULL;

Adafruit_MQTT_Client    *mqtt         = NULL;
Adafruit_MQTT_Publish   *Temperature  = NULL;
Adafruit_MQTT_Subscribe *LED_Control  = NULL;

// You have to get from a sensor. Here is just an example
uint32_t measuredTemp = 5;

WiFiManager_NINA_Lite* WiFiManager_NINA;

void heartBeatPrint(void)
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print("W");        // W means connected to WiFi
  else
    Serial.print("N");        // N means not connected to WiFi

  if (num == 40)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 5 == 0)
  {
    Serial.print(" ");
  }
}

void publishMQTT(void)
{
  MQTT_connect();

  if (Temperature->publish(measuredTemp))
  {
    //Serial.println(F("Failed to send value to Temperature feed!"));
    Serial.print("T");        // T means publishing OK
  }
  else
  {
    //Serial.println(F("Value to Temperature feed sucessfully sent!"));
    Serial.print("F");        // F means publishing failure
  }
}

void subscribeMQTT(void)
{
  Adafruit_MQTT_Subscribe *subscription;

  MQTT_connect();

  while ((subscription = mqtt->readSubscription(5000)))
  {
    if (subscription == LED_Control)
    {
      Serial.print(F("\nGot: "));
      Serial.println((char *)LED_Control->lastread);

      if (!strcmp((char*) LED_Control->lastread, "ON"))
      {
        digitalWrite(LED_PIN, HIGH);
      }
      else
      {
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

  //KH
#define HEARTBEAT_INTERVAL    5000L
  // Print WiFi hearbeat, Publish MQTT Topic every HEARTBEAT_INTERVAL (5) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      // MQTT related jobs
      publishMQTT();
      subscribeMQTT();
    }

    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

void deleteOldInstances(void)
{
  // Delete previous instances
  if (mqtt)
  {
    delete mqtt;
    mqtt = NULL;
    Serial.println("Deleting old MQTT object");
  }

  if (Temperature)
  {
    delete Temperature;
    Temperature = NULL;
    Serial.println("Deleting old Temperature object");
  }
}

#define USE_GLOBAL_TOPIC    true

#if USE_GLOBAL_TOPIC
String completePubTopic;
String completeSubTopic;
#endif

void createNewInstances(void)
{
  if (!client)
  {
    client = new WiFiClient;

    if (client)
    {
      Serial.println("\nCreating new WiFi client object OK");
    }
    else
      Serial.println("\nCreating new WiFi client object failed");
  }

  // Create new instances from new data
  if (!mqtt)
  {
    // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
    mqtt = new Adafruit_MQTT_Client(client, AIO_SERVER, atoi(AIO_SERVERPORT), AIO_USERNAME, AIO_KEY);

    if (mqtt)
    {
      Serial.println("Creating new MQTT object OK");
      Serial.println(String("AIO_SERVER = ")    + AIO_SERVER    + ", AIO_SERVERPORT = "  + AIO_SERVERPORT);
      Serial.println(String("AIO_USERNAME = ")  + AIO_USERNAME  + ", AIO_KEY = "         + AIO_KEY);
    }
    else
      Serial.println("Creating new MQTT object failed");
  }

  if (!Temperature)
  {
#if USE_GLOBAL_TOPIC
    completePubTopic = String(AIO_USERNAME) + String(AIO_PUB_TOPIC);
#else
    // Must be static or global
    static String completePubTopic = String(AIO_USERNAME) + String(AIO_PUB_TOPIC);
#endif

    Temperature = new Adafruit_MQTT_Publish(mqtt, completePubTopic.c_str());
    Serial.println(String("Creating new MQTT_Pub_Topic,  Temperature = ") + completePubTopic);

    if (Temperature)
    {
      Serial.println("Creating new Temperature object OK");
      Serial.println(String("Temperature MQTT_Pub_Topic = ")  + completePubTopic);

    }
    else
      Serial.println("Creating new Temperature object failed");
  }

  if (!LED_Control)
  {
#if USE_GLOBAL_TOPIC
    completeSubTopic = String(AIO_USERNAME) + String(AIO_SUB_TOPIC);
#else
    // Must be static or global
    static String completeSubTopic = String(AIO_USERNAME) + String(AIO_SUB_TOPIC);
#endif

    LED_Control = new Adafruit_MQTT_Subscribe(mqtt, completeSubTopic.c_str());

    Serial.println(String("Creating new AIO_SUB_TOPIC, LED_Control = ") + completeSubTopic);

    if (LED_Control)
    {
      Serial.println("Creating new LED_Control object OK");
      Serial.println(String("LED_Control AIO_SUB_TOPIC = ")  + completeSubTopic);

      mqtt->subscribe(LED_Control);
    }
    else
      Serial.println("Creating new LED_Control object failed");
  }
}

void MQTT_connect()
{
  int8_t ret;

  createNewInstances();

  // Return if already connected
  if (mqtt->connected())
  {
    return;
  }

#if LOCAL_DEBUG
  Serial.println("\nConnecting to WiFi MQTT (3 attempts)...");
#endif

  uint8_t attempt = 3;

  while ( (ret = mqtt->connect()) )
  {
    // connect will return 0 for connected
    Serial.println(mqtt->connectErrorString(ret));

#if LOCAL_DEBUG
    Serial.println("Another attemtpt to connect to MQTT in 5 seconds...");
#endif

    mqtt->disconnect();
    delay(5000);  // wait 5 seconds
    attempt--;

    if (attempt == 0)
    {
      Serial.println("WiFi MQTT connection failed. Continuing with program...");
      return;
    }
  }

#if LOCAL_DEBUG
  Serial.println("WiFi MQTT connection successful!");
#endif
}

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input,select{padding:5px;font-size:1em;}input,select{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  pinMode(LED_PIN, OUTPUT);

  delay(200);

  Serial.print(F("\nStarting nRF52_WiFiNINA_MQTT on ")); Serial.println(BOARD_TYPE);
  Serial.println(WIFIMANAGER_NINA_LITE_VERSION);

  WiFiManager_NINA = new WiFiManager_NINA_Lite();

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //WiFiManager_NINA->setConfigPortalIP(IPAddress(192, 168, 120, 1));
  WiFiManager_NINA->setConfigPortalChannel(0);

#if USING_CUSTOMS_STYLE
  WiFiManager_NINA->setCustomsStyle(NewCustomsStyle);
#endif

#if USING_CUSTOMS_HEAD_ELEMENT
  WiFiManager_NINA->setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
#endif

#if USING_CORS_FEATURE  
  WiFiManager_NINA->setCORSHeader("Your Access-Control-Allow-Origin");
#endif

  // Set customized DHCP HostName
  WiFiManager_NINA->begin(HOST_NAME);
  //Or use default Hostname "nRF52-WiFiNINA-XXXXXX"
  //WiFiManager_NINA->begin();
  
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials()
{
  Serial.println(F("\nYour stored Credentials :"));

  for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.print(myMenuItems[i].displayName);
    Serial.print(F(" = "));
    Serial.println(myMenuItems[i].pdata);
  }
}

void displayCredentialsInLoop()
{
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
}

#endif

void loop()
{
  WiFiManager_NINA->run();
  check_status();

#if USE_DYNAMIC_PARAMETERS
  displayCredentialsInLoop();
#endif  
}
