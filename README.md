## WiFiManager_NINA_Lite (Light Weight Credentials / WiFi Manager for WiFiNINA modules/shields)

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_NINA_Lite.svg?)](https://www.ardu-badge.com/WiFiManager_NINA_Lite)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiManager_NINA_Lite.svg)](https://github.com/khoih-prog/WiFiManager_NINA_Lite/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiManager_NINA_Lite/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiManager_NINA_Lite.svg)](http://github.com/khoih-prog/WiFiManager_NINA_Lite/issues)

---
---

## Table of Contents

* [Why do we need this WiFiManager_NINA_Lite library](#why-do-we-need-this-wifimanager_nina_lite-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported WiFi shields/modules](#currently-supported-wifi-shieldsmodules)
* [Changelog](#changelog)
  * [Release v1.2.0](#release-v120)
  * [Release v1.1.3](#release-v113)
  * [Release v1.1.2](#release-v112)
  * [Release v1.1.1](#release-v111)
  * [Major Release v1.1.0](#major-release-v110)
  * [Release v1.0.5](#release-v105)
  * [Major Release v1.0.4](#major-release-v104)
  * [Major Release v1.0.3](#major-release-v103)
  * [Release v1.0.2](#release-v102)
  * [Release v1.0.1](#release-v101)
  * [Release v1.0.0](#release-v100)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
* [How It Works](#how-it-works)
* [How to use](#how-to-use)
  * [ 1. Basic usage](#1-basic-usage)
  * [ 2. Add custom parameters](#2-add-custom-parameters)
  * [ 3. Not using custom parameters](#3-not-using-custom-parameters)
  * [ 4. To open Config Portal](#4-to-open-config-portal)
  * [ 5. To use different AP WiFi Channel](#5-to-use-different-ap-wifi-channel)
  * [ 6. To use different static AP IP from default](#6-to-use-different-static-ap-ip-from-default)
  * [ 7. To use custom DHCP HostName](#7-to-use-custom-dhcp-hostname)
  * [ 8. To use custom HTML Style](#8-to-use-custom-html-style)
  * [ 9. To use custom Head Elements](#9-to-use-custom-head-elements)
  * [10. To use CORS Header](#10-to-use-cors-header)
  * [11. To use and input only one set of WiFi SSID and PWD](#11-to-use-and-input-only-one-set-of-wifi-ssid-and-pwd)
* [Examples](#examples)
  * [ 1. SAMD_WiFiNINA](examples/SAMD_WiFiNINA)
  * [ 2. SAMD_WiFiNINA_MQTT](examples/SAMD_WiFiNINA_MQTT)
  * [ 3. nRF52_WiFiNINA](examples/nRF52_WiFiNINA)
  * [ 4. nRF52_WiFiNINA_MQTT](examples/nRF52_WiFiNINA_MQTT)
  * [ 5. Teensy_WiFiNINA](examples/Teensy_WiFiNINA)
  * [ 6. Teensy_WiFiNINA_MQTT](examples/Teensy_WiFiNINA_MQTT)
  * [ 7. STM32_WiFiNINA](examples/STM32_WiFiNINA)
  * [ 8. STM32_WiFiNINA_MQTT](examples/STM32_WiFiNINA_MQTT)
  * [ 9. SAM_DUE_WiFiNINA](examples/SAM_DUE_WiFiNINA)
  * [10. SAM_DUE_WiFiNINA_MQTT](examples/SAM_DUE_WiFiNINA_MQTT)
  * [11. Mega_WiFiNINA](examples/Mega_WiFiNINA)
* [So, how it works?](#so-how-it-works)
* [Important Notes](#important-notes)
* [How to use default Credentials and have them pre-loaded onto Config Portal](#how-to-use-default-credentials-and-have-them-pre-loaded-onto-config-portal)
  * [1. To always load Default Credentials and override Config Portal data](#1-to-always-load-default-credentials-and-override-config-portal-data)
  * [2. To load Default Credentials when there is no valid Credentials](#2-to-load-default-credentials-when-there-is-no-valid-credentials)
  * [3. Example of Default Credentials](#3-example-of-default-credentials)
* [How to add dynamic parameters from sketch](#how-to-add-dynamic-parameters-from-sketch)
* [Important Notes for using Dynamic Parameters' ids](#important-notes-for-using-dynamic-parameters-ids)
* [Example SAMD_WiFiNINA](#example-samd_wifinina)
  * [1. File SAMD_WiFiNINA.ino](#1-file-samd_wifininaino)
  * [2. File defines.h](#2-file-definesh)
  * [3. File Credentials.h](#3-file-credentialsh)
  * [4. File dynamicParams.h](#4-file-dynamicparamsh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. Open Config Portal](#1-open-config-portal)
  * [2. Received data from Config Portal](#2-received-data-from-config-portal)
  * [3. Got valid Credential from Config Portal, then connected to WiFi](#3-got-valid-credential-from-config-portal-then-connected-to-wifi)
  * [4. Lost a WiFi and autoconnect to another WiFi AP](#4-lost-a-wifi-and-autoconnect-to-another-wifi-ap)
  * [5. Reopen Config Portal if can't connect to any of the 2 WiFi APs](#5-reopen-config-portal-if-cant-connect-to-any-of-the-2-wifi-aps)
  * [6. DRD Not Detected](#6-drd-not-detected) 
  * [7. DRD detected and Config Portal is forcefully opened](#7-drd-detected-and-config-portal-is-forcefully-opened)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [WiFiManager_NINA_Lite library](https://github.com/khoih-prog/WiFiManager_NINA_Lite)

#### Features

If you have used the full-fledge WiFiManager such as :

1. [`Tzapu WiFiManager`](https://github.com/tzapu/WiFiManager)
2. [`Ken Taylor WiFiManager`](https://github.com/kentaylor/WiFiManager)
3. [`Khoi Hoang ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager)

and have to write **complicated callback functions** to save custom parameters in SPIFFS/LittleFS/EEPROM, you'd appreciate the simplicity of this Light-Weight Credentials / WiFiManager.

This library is a Light Weight Credentials / WiFi Manager for WiFiNINA (WiFiNINA, WINC1500/WiFi101, etc.) modules/shields, specially designed to support **Teensy, SAM DUE, SAMD21 (Nano-33 IoT, Itsy-Bitsy M0, etc), SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.), STM32F (F1, F2, F3, F4, F7, Nucleo-144, etc.), nRF52 (Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, NINA_B302_ublox, NINA_B112_ublox, etc.), etc. boards running WiFiNINA modules/shields.** with smaller memory (64+K bytes)

The AVR-family boards (UNO, Nano, etc.) are **not supported** as they don't have enough memory to run Config Portal WebServer.

This is a Credentials / WiFi Connection Manager, permitting the addition of custom parameters to be configured in Config Portal. The parameters then will be saved automatically, **without the complicated callback functions** to handle data saving / retrieving.

You can also specify DHCP HostName, static AP and STA IP. Use much less memory compared to full-fledge WiFiManager. Config Portal will be auto-adjusted to match the number of dynamic custom parameters. Credentials are saved in EEPROM, FlashStorage or DueFlashStorage.

The web configuration portal, served from the `WiFiNINA modules/shields` is operating as an access point (AP) with configurable static IP address or use default IP Address of 192.168.4.1

New recent features:

- **MultiWiFi** feature for configuring/auto(re)connecting **WiFiNINA (WiFiNINA, WINC1500/WiFi101, etc.)** shields to the available MultiWiFi APs at runtime.
- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- **Powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
- Optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input.
- Dynamic custom parameters to be saved **automatically in non-volatile memory, such as Teensy EEPROM, SAMD EEPROM-emulated FlashStorage_SAMD, STM32F/L/H/G/WB/MP1 EEPROM-emulated FlashStorage_STM32 or SAM DUE DueFlashStorage**.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
- Configurable **Customs HTML Headers**, including Customs Style, Customs Gead Elements, CORS Header.

#### Currently supported Boards

This [**WiFiManager_NINA_Lite** library](https://github.com/khoih-prog/WiFiManager_NINA_Lite) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 2. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 3. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 4. **SAM DUE** 
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0)**
 6. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash)**
  - Nucleo-144
  - Nucleo-64
  - Discovery
  - Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
  - STM32L0, STM32L1, STM32L4
  - STM32G0, STM32G4
  - STM32H7
  - STM32WB
  - STM32MP1
  - LoRa boards
  - 3-D printer boards
  - Generic Flight Controllers
  - Midatronics boards


#### Currently supported WiFi shields/modules

1. WiFiNINA using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
2. WiFi101 using [`WiFi101 library v0.16.1+`](https://github.com/arduino-libraries/WiFi101)
3. u-blox W101, W102 using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)

---
---

## Changelog

### Release v1.2.0

1. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
2. Enforce WiFi Password minimum length of 8 chars
3. Enhance MultiWiFi connection logic

### Release v1.1.3

1. Fix invalid "blank" or NULL Config Data treated as Valid. Check [WiFiManager connection attempt to unconfigured ("blank") SSID after restart on SAMD #8](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/8)
2. Fix compiler warnings.


### Release v1.1.2

1. Fix MultiWiFi connection bug. Check [SAMD MultiWiFi issues when first WiFi SSID configured in CP is invalid or not available #6](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/6)

### Release v1.1.1

1. Fix USE_DYNAMIC_PARAMETERS bug.

#### Major Release v1.1.0

1. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header.
2. Add support to boards using WiFi101 library such as MKR1000
3. Fix Config Portal Bug. 
4. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
5. Use more efficient [FlashStorage_SAMD v1.1.0](https://github.com/khoih-prog/FlashStorage_SAMD) and [FlashStorage_STM32 v1.0.0](https://github.com/khoih-prog/FlashStorage_STM32)
6. Optimize code
7. Add Version String 

### Release v1.0.5

1. Modify LOAD_DEFAULT_CONFIG_DATA logic.
4. Enhance MultiWiFi connection logic. 
5. Add Adafruit MQTT examples.

#### Major Release v1.0.4

1. Configurable **Config Portal Title** to be either HostName, BoardName or default undistinguishable names.
2. Optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input.
3. **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
4. Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
5. Add Board Name

Thanks to [Thor Johnson](https://github.com/thorathome) to test, suggest and encourage to add those new features in [**Blynk_WM Library**](https://github.com/khoih-prog/Blynk_WM), such as Default Credentials/Dynamic Params, Configurable Config Portal Title, DRD. Now those features are speading fast into libraries having similar functionalities.

#### Major Release v1.0.3

1. **Multiple WiFi Credentials (SSID, Password)** and system will autoconnect to the available WiFi AP. It will then autoreconnect to the remaining WiFi AP if the current connection is lost.
2. Add support to **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
3. WiFi Password max length is 63, according to WPA2 standard
4. Permit to input special chars such as **%** and **#** into data fields.
5. Add option to have built-in, yet configurable RFC-952-conformed DHCP hostname.
6. Fix bug

#### Release v1.0.2

1. Fix bug
2. Add support to **SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.

#### Release v1.0.1

1. Use new [**WiFiNINA_Generic library**](https://github.com/khoih-prog/WiFiNINA_Generic) to provide support to many more boards (Teensy, AVR Mega, SAM DUE, SAMD51, STM32, etc.) running WiFiNINA. The original WiFiNINA library only supports Nano-33 IoT, Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2.
2. Use new [**FlashStorage_SAMD library**](https://github.com/khoih-prog/FlashStorage_SAMD) to provide EEPROM/FlashStorage support to SAMD51 boards (Itsy-Bitsy M4, etc).

#### Release v1.0.0

1. New **powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved **automatically in EEPROM, SAMD EEPROM-emulated FlashStorage or SAM DUE DueFlashStorage**.

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.9.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 3. [`Teensy core 1.51`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 4. [`Arduino SAM DUE core 1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.11+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.6.7+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.1+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v0.21.0+`](https://www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 9. [`Functional-VLPP library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
10. [`WiFiNINA_Generic library v1.8.5+`](https://github.com/khoih-prog/WiFiNINA_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic)
11. [`WiFi101 library v0.16.1+`](https://github.com/arduino-libraries/WiFi101) if using WINC1500/WiFi101 shields (MKR1000, etc.). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFi101.svg?)](https://www.ardu-badge.com/WiFi101)
12. [`WiFiWebServer library v1.1.1+`](https://github.com/khoih-prog/WiFiWebServer). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiWebServer.svg?)](https://www.ardu-badge.com/WiFiWebServer)
13. [`FlashStorage_SAMD library v1.1.0+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.). [![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases/latest)
14. [`FlashStorage_STM32 library v1.0.1+`](https://github.com/khoih-prog/FlashStorage_STM32) for STM32F/L/H/G/WB/MP1 boards. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32)
15. [`DueFlashStorage library v1.0.0+`](https://github.com/sebnil/DueFlashStorage) for SAM DUE. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DueFlashStorage.svg?)](https://www.ardu-badge.com/DueFlashStorage)
16. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52
17. [`DoubleResetDetector_Generic v1.0.3+`](https://github.com/khoih-prog/DoubleResetDetector_Generic). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)

---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**WiFiManager_NINA_Lite**](https://github.com/khoih-prog/WiFiManager_NINA_Lite), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_NINA_Lite.svg?)](https://www.ardu-badge.com/WiFiManager_NINA_Lite) for more detailed instructions.

### Manual Install

1. Navigate to [**WiFiManager_NINA_Lite**](https://github.com/khoih-prog/WiFiManager_NINA_Lite) page.
2. Download the latest release `WiFiManager_NINA_Lite-master.zip`.
3. Extract the zip file to `WiFiManager_NINA_Lite-master` directory 
4. Copy the whole 
  - `WiFiManager_NINA_Lite-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**WiFiManager_NINA_Lite** library](https://platformio.org/lib/show/7159/WiFiManager_NINA_Lite) by using [Library Manager](https://platformio.org/lib/show/7159/WiFiManager_NINA_Lite/installation). Search for **WiFiManager_NINA_Lite** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 0.21.0](Packages_Patches/adafruit/hardware/nrf52/0.21.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0). 

Supposing the Adafruit nRF52 version is 0.21.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.13/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.13. These files must be copied into the directory:

- `./arduino-1.8.13/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.10](Packages_Patches/arduino/hardware/samd/1.8.10) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.10).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.7) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.7). 

Supposing the Adafruit SAMD core version is 1.6.7. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.7/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

#### 7. For STM32 boards

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`


---
---

## How It Works

- The [**SAMD_WiFiNINA**](examples/SAMD_WiFiNINA) example shows how it works and should be used as the basis for a sketch that uses this library.
- The concept of [**SAMD_WiFiNINA**](examples/SAMD_WiFiNINA) is that a new `WiFiNINA module/shield` will start a WiFi configuration portal when powered up, but has no valid stored Credentials or can't connect to WiFi APs after a pre-determined time.
- There are 6 more custom parameters added in the sketch which you can use in your program later. In the example, they are: 2 sets of Blynk Servers and Tokens, Blynk Port and MQTT Server.
- Using any WiFi enabled device with a browser (computer, phone, tablet) connect to the newly created AP and type in the configurable AP IP address (default 192.168.4.1). The Config Portal AP channel (default 10) is also configurable to avoid conflict with other APs.
- The Config Portal is **auto-adjusted** to fix the 4 static parameters (WiFi SSIDs/PWDs) as well as 6 more dynamic custom parameters.
- After the custom data entered, and **Save** button pressed, the configuration data will be saved in host's non-volatile memory, then the board reboots.
- If there is valid stored Credentials, it'll go directly to connect to one of the **MultiWiFi APs** without starting / using the Config Portal.
- `WiFiNINA module/shield` will try to connect. If successful, the dynamic DHCP and/or configured static IP address will be displayed in the configuration portal. 
- The `WiFiNINA module/shield` WiFi Config Portal network and Web Server will shutdown to return control to the sketch code.
- In the operation, if the current WiFi connection is lost because of any reason, the system will **auto(Re)connect** to the remaining WiFi AP.
- **If system can't connect to any of the 2 WiFi APs, the Config Portal will start**, after some pre-determined time, to permit user to update the Credentials.

---

### How to use

#### 1. Basic usage

- Include in your sketch

```cpp
// Must be before #include <WiFiManager_NINA_Lite_SAMD.h>
// Start location in EEPROM to store config data. Default 0
// Config data Size, not including your custom data, currently is 84 bytes)
#define EEPROM_START      0

#include <WiFiManager_NINA_Lite_SAMD.h>

WiFiManager_NINA_Lite* WiFiManager_NINA;
```

#### 2. Add custom parameters

- To add custom parameters, just add

```
#define USE_DYNAMIC_PARAMETERS      true

/////////////// Start dynamic Credentials ///////////////

//Defined in <WiFiManager_NINA_Lite_Teensy.h>
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

#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN + 1]  = "";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN + 1]   = "";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN + 1]  = "";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN + 1]   = "";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN + 1]  = "";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "prt", "Port",           Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mqt", "MQTT Server",    MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS

```

#### 3. Not using custom parameters

- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS      false
```

#### 4. To open Config Portal

- When you want to open a config portal, just add

```cpp
WiFiManager_NINA = new WiFiManager_NINA_Lite();
WiFiManager_NINA->begin();
```

#### 5. To use different AP WiFi Channel

- To not use default AP WiFi Channel 10 to avoid conflict with other WiFi APs : 

```cpp
WiFiManager_NINA->setConfigPortalChannel(newChannel);
```

- To use random AP WiFi Channel to avoid conflict with other WiFi APs : 

```cpp
WiFiManager_NINA->setConfigPortalChannel(0);
```

#### 6. To use different static AP IP from default

- To use different static AP IP (not use default `192.168.4.1`), call

```cpp
WiFiManager_NINA->setConfigPortalIP(IPAddress(xxx,xxx,xxx,xxx));
```

#### 7. To use custom DHCP HostName

- To set custom DHCP HostName :
 
```
  // Set customized DHCP HostName
  WiFiManager_NINA->begin("SAMD-WiFiNINA-ABCDEF");
```
 
or just use the default Hostname, for example "SAMD-WiFiNINA-XXXXXX" for SAMD

```
  //Or use default Hostname "SAMD-WiFiNINA-XXXXXX"
  //WiFiManager_NINA->begin();
```

#### 8. To use custom HTML Style

```
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

...

WiFiManager_NINA->setCustomsStyle(NewCustomsStyle);
```

#### 9. To use custom Head Elements


```
WiFiManager_NINA->setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
```

#### 10. To use CORS Header

```
WiFiManager_NINA->setCORSHeader("Your Access-Control-Allow-Origin");
```

While in AP mode, connect to it using its `SSID` (WIFININA_XXXXXX) / `Password` ("MyWIFININA_XXXXXX"), then open a browser to the Portal AP IP, default `192.168.4.1`, configure wifi then click **Save**. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect.


Once Credentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.

#### 11. To use and input only one set of WiFi SSID and PWD

#### 11.1 If you need to use and input only one set of WiFi SSID/PWD.

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       true
```
But it's always advisable to use and input both sets for reliability.
 
#### 11.2 If you need to use both sets of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       false
```

---
---

### Examples

 1. [SAMD_WiFiNINA](examples/SAMD_WiFiNINA)
 2. [SAMD_WiFiNINA_MQTT](examples/SAMD_WiFiNINA_MQTT)
 3. [nRF52840_WiFiNINA](examples/nRF52840_WiFiNINA)
 4. [nRF52840_WiFiNINA_MQTT](examples/nRF52840_WiFiNINA_MQTT)
 5. [Teensy40_WiFiNINA](examples/Teensy40_WiFiNINA)
 6. [Teensy40_WiFiNINA_MQTT](examples/Teensy40_WiFiNINA_MQTT)
 7. [STM32_WiFiNINA](examples/STM32_WiFiNINA)
 8. [STM32_WiFiNINA_MQTT](examples/STM32_WiFiNINA_MQTT)
 9. [SAM_DUE_WiFiNINA](examples/SAM_DUE_WiFiNINA)
10. [SAM_DUE_WiFiNINA_MQTT](examples/SAM_DUE_WiFiNINA_MQTT)
11. [Mega_WiFiNINA](examples/Mega_WiFiNINA)

---
---

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

---

### Important Notes

1. Now you can use special chars such as **~, !, @, #, $, %, ^, &, _, -, space,etc.** thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in [**Blynk_WM**](https://github.com/khoih-prog/Blynk_WM) to permit input special chars such as **%** and **#** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
2. The SSIDs, Passwords must be input (or to make them different from **blank**). Otherwise, the Config Portal will re-open until those fields have been changed. If you don't need any field, just input anything or use duplicated data from similar field.
3. WiFi password max length now is 63 chars according to WPA2 standard.

---

### How to use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

#### 1. To always load [Default Credentials](examples/SAMD_WiFiNINA/Credentials.h) and override Config Portal data

```
// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

#### 2. To load [Default Credentials](examples/SAMD_WiFiNINA/Credentials.h) when there is no valid Credentials.

Config Portal data input will be override DEFAULT_CONFIG_DATA

```
// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

#### 3. Example of [Default Credentials](examples/SAMD_WiFiNINA/Credentials.h)

```cpp
/// Start Default Config Data //////////////////

/*
#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header, just add board_name 
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [24];
  int  checkSum;
} WiFiNINA_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

// This feature is primarily used in development to force a known set of values as Config Data
// It will NOT force the Config Portal to activate. Use DRD or erase Config Data with Blynk.clearConfigData()

// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
//bool LOAD_DEFAULT_CONFIG_DATA = true;

// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;

WiFiNINA_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "WIFININA",
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
  "SSID1",  "password1",
  "SSID2",  "password2",
  //char board_name     [24];
  "Air-Control",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

WiFiNINA_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////
```

### How to add dynamic parameters from sketch

Example of [Default dynamicParams](examples/SAMD_WiFiNINA/dynamicParams.h)

- To add custom parameters, just modify the example below

```
#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in <WiFiManager_NINA_Lite_SAMD.h>
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

#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN + 1]  = "account.duckdns.org";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN + 1]   = "token1";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN + 1]  = "account.ddns.net";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN + 1]   = "token2";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN + 1]  = "8080";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt.duckdns.org";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "prt", "Port",          Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mqt", "MQTT Server",   MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS


#endif      //dynamicParams_h

```
- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS     false
```

or

```
/////////////// Start dynamic Credentials ///////////////

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
/////// // End dynamic Credentials ///////////

```
---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be **unique**.

Please be noted that the following **reserved names are already used in library**:

```
"id"    for WiFi SSID
"pw"    for WiFi PW
"id1"   for WiFi1 SSID
"pw1"   for WiFi1 PW
"nm"    for Board Name
```
---
---

### Example [SAMD_WiFiNINA](examples/SAMD_WiFiNINA)

Please take a look at other examples, as well.

#### 1. File [SAMD_WiFiNINA.ino](examples/SAMD_WiFiNINA/SAMD_WiFiNINA.ino)

```cpp
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

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
#define HEARTBEAT_INTERVAL    20000L
  // Print hearbeat every HEARTBEAT_INTERVAL (20) seconds.
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

  Serial.print(F("\nStarting SAMD_WiFiNINA on ")); Serial.println(BOARD_TYPE);
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
  //Or use default Hostname "SAMD-WiFiNINA-XXXXXX"
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
```
---

#### 2. File [defines.h](examples/SAMD_WiFiNINA/defines.h)

```cpp
#ifndef defines_h
#define defines_h

/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT       Serial
#define WIFININA_DEBUG_OUTPUT           Serial

#define _WIFININA_LOGLEVEL_             2

#define DRD_GENERIC_DEBUG               true

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD21G18A__) )
  #if defined(WIFININA_USE_SAMD)
    #undef WIFININA_USE_SAMD
    #undef WIFI_USE_SAMD
  #endif
  #define WIFININA_USE_SAMD      true
  #define WIFI_USE_SAMD          true
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
  #elif defined(__SAMD21E18A__)
    #define BOARD_TYPE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
    #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
    #define BOARD_TYPE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
    #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
    #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
    #define BOARD_TYPE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
    #define BOARD_TYPE      "CPU_ARC"
  #elif defined(__SAMD51__)
    #define BOARD_TYPE      "SAMD51"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

#endif

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes)
#define EEPROM_START      0
#define EEPROM_SIZE       (2 * 1024)

/////////////////////////////////////////////

// Add customs headers from v1.1.0
#define USING_CUSTOMS_STYLE           true
#define USING_CUSTOMS_HEAD_ELEMENT    true
#define USING_CORS_FEATURE            true

/////////////////////////////////////////////

#define USE_WIFI_NINA                 true
#define USE_WIFI101                   false
#define USE_WIFI_CUSTOM               false

#if USE_WIFI_NINA

  #warning Using WIFININA_Generic Library
  #define SHIELD_TYPE     "WiFiNINA using WiFiNINA_Generic Library"

  #include "WiFiNINA_Pinout_Generic.h"
  
#elif USE_WIFI101

  #if defined(USE_WIFI_NINA)
    #undef USE_WIFI_NINA
  #endif
  
  #define USE_WIFI_NINA           false

  #define SHIELD_TYPE     "WINC1500 using WiFi101 Library"
  #warning Using WiFi101 Library

#elif USE_WIFI_CUSTOM

  #if defined(USE_WIFI_NINA)
    #undef USE_WIFI_NINA
  #endif
  
  #define USE_WIFI_NINA           false
  
  #if defined(USE_WIFI101)
    #undef USE_WIFI101
  #endif
  
  #define USE_WIFI101             false

  #define SHIELD_TYPE     "Custom using Custom WiFi Library"
  #warning Using Custom WiFi Library. You must include here or compile error
  
#else

  #define SHIELD_TYPE     "Default WiFi using WiFi Library"
  #warning Using fallback WiFi.h Library defined in WiFiWebServer Library.
  
#endif

/////////////////////////////////////////////

// Force some params in Blynk, only valid for library version 1.0.1 and later
#define TIMEOUT_RECONNECT_WIFI                    10000L
#define RESET_IF_CONFIG_TIMEOUT                   true
#define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET    5

// Config Timeout 120s (default 60s)
#define CONFIG_TIMEOUT                      120000L

#define USE_DYNAMIC_PARAMETERS              true

/////////////////////////////////////////////

#include <WiFiManager_NINA_Lite_SAMD.h>

#define HOST_NAME   "SAMD-Master-Controller"

#endif      //defines_h
```
---

#### 3. File [Credentials.h](examples/SAMD_WiFiNINA/Credentials.h)

```cpp
#ifndef Credentials_h
#define Credentials_h

#include "defines.h"

/// Start Default Config Data //////////////////

/*
#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header, just add board_name 
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [24];
  int  checkSum;
} WiFiNINA_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      false

#if TO_LOAD_DEFAULT_CONFIG_DATA

// This feature is primarily used in development to force a known set of values as Config Data
// It will NOT force the Config Portal to activate. Use DRD or erase Config Data with Blynk.clearConfigData()

// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
//bool LOAD_DEFAULT_CONFIG_DATA = true;

// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;


WiFiNINA_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "WIFININA",
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
  "SSID1",  "password1",
  "SSID2",  "password2",
  //char board_name     [24];
  "SAMD-Control",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

WiFiNINA_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////


#endif    //Credentials_h
```
---

#### 4. File [dynamicParams.h](examples/SAMD_WiFiNINA/dynamicParams.h)

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in <WiFiManager_NINA_Lite_SAMD.h>
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

#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN + 1]  = "account.duckdns.org";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN + 1]   = "token1";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN + 1]  = "account.ddns.net";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN + 1]   = "token2";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN + 1]  = "8080";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt.duckdns.org";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "prt", "Port",          Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mqt", "MQTT Server",   MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS


#endif      //dynamicParams_h
```

---
---


### Debug Terminal output Samples

This is the terminal output when running [**SAMD_WiFiNINA**](examples/SAMD_WiFiNINA) example on **Nano-33 IoT**:

#### 1. Open Config Portal

```
Starting SAMD_WiFiNINA on SAMD NANO_33_IOT
WiFiManager_NINA_Lite v1.2.0
[WN] Hostname=SAMD-Master-Controller
Flag read = 0xffffffff
No doubleResetDetected
SetFlag write = 0xd0d01234
[WN] ======= Start Default Config Data =======
[WN] Hdr=WIFININA,SSID=SSID1,PW=password1
[WN] SSID1=SSID2,PW1=password2
[WN] BName=SAMD-Control
[WN] i=0,id=sv1,data=account.duckdns.org
[WN] i=1,id=tk1,data=token1
[WN] i=2,id=sv2,data=account.ddns.net
[WN] i=3,id=tk2,data=token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=mqtt.duckdns.org
[WN] ChkCrR:CrCCsum=0xaf50,CrRCsum=0xffffffff
[WN] CCSum=0x1360,RCSum=0x0
[WN] Invalid Stored Dynamic Data. Load default from Sketch
[WN] SaveEEPROM,sz=1024,Datasz=0,CSum=0x109a
[WN] CrCCSum=0x1981
[WN] ======= Start Loaded Config Data =======
[WN] Hdr=WIFININA,SSID=SSID1,PW=password1
[WN] SSID1=SSID2,PW1=password2
[WN] BName=SAMD-Control
[WN] i=0,id=sv1,data=account.duckdns.org
[WN] i=1,id=tk1,data=token1
[WN] i=2,id=sv2,data=account.ddns.net
[WN] i=3,id=tk2,data=token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=mqtt.duckdns.org
[WN] b:StayInCfgPortal:NoCfgDat
[WN] SSID=WIFININA_51F485,PW=MyWIFININA_51F485
[WN] IP=192.168.4.1,CH=10
WiFi-beginAP3: return1 = 7
WiFi-beginAP3: return2 = 7
F
Your stored Credentials :
Blynk Server1 = account.duckdns.org
Token1 = token1
Blynk Server2 = account.ddns.net
Token2 = token2
Port = 8080
MQTT Server = mqtt.duckdns.org
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
FFFFFFFFF 
```

#### 2. Received data from Config Portal

```
Start SAMD_WiFiNINA on SAMD NANO_33_IOT
WiFiManager_NINA_Lite v1.2.0
[WN] Hostname=SAMD-WIFININA51F485
[WN] CrCCSum=44880,CrRCSum=-1
[WN] CCSum=53040,RCSum=-1
[WN] InitEEPROM,sz=1024,Datasz=392
[WN] pdata=blank,len=34
[WN] pdata=blank,len=34
[WN] pdata=blank,len=34
[WN] pdata=blank,len=34
[WN] pdata=blank,len=6
[WN] pdata=blank,len=34
[WN] CrCCSum=3120
[WN] b:OpenPortal
[WN] SSID=WIFININA_B18D0F,PW=MyWIFININA_B18D0F
[WN] IP=192.168.4.1,CH=10
WiFi-beginAP3: return1 = 7
WiFi-beginAP3: return2 = 7
FYour stored Credentials :
Blynk Server1 = blank
Token1 = blank
Blynk Server2 = blank
Token2 = blank
Port = blank
MQTT Server = blank
FFFFFFFFF 
[WN] h:sv1=BlynkServer1
[WN] h:tk1=Token1
[WN] h:sv2=BlynkServer2
[WN] h:tk2=Token2
[WN] h:pt=8080
[WN] h:mq=mqtt-server
[WN] h:UpdEEPROM
[WN] SaveEEPROM,sz=1024,Datasz=392,CSum=3612
[WN] pdata=BlynkServer1,len=34
[WN] pdata=Token1,len=34
[WN] pdata=BlynkServer2,len=34
[WN] pdata=Token2,len=34
[WN] pdata=8080,len=6
[WN] pdata=mqtt-server,len=34
[WN] CrCCSum=4880
[WN] h:Rst
```

#### 3. Got valid Credential from Config Portal, then connected to WiFi

```
Start SAMD_WiFiNINA on SAMD NANO_33_IOT
WiFiManager_NINA_Lite v1.2.0
[WN] Hostname=SAMD-Master-Controller
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[WN] ======= Start Default Config Data =======
[WN] Hdr=WIFININA,SSID=SSID1,PW=password1
[WN] SSID1=SSID2,PW1=password2
[WN] BName=SAMD-Control
[WN] i=0,id=sv1,data=account.duckdns.org
[WN] i=1,id=tk1,data=token1
[WN] i=2,id=sv2,data=account.ddns.net
[WN] i=3,id=tk2,data=token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=mqtt.duckdns.org
[WN] ChkCrR:CrCCsum=0x21ce,CrRCsum=0x21ce
[WN] CCSum=0x1246,RCSum=0x1246
[WN] CrCCsum=0x21ce,CrRCsum=0x21ce
[WN] Valid Stored Dynamic Data
[WN] ======= Start Stored Config Data =======
[WN] Hdr=WIFININA,SSID=HueNet1,PW=****
[WN] SSID1=HueNet2,PW1=****
[WN] BName=Air-Control
[WN] i=0,id=sv1,data=new_account.duckdns.org
[WN] i=1,id=tk1,data=new_token1
[WN] i=2,id=sv2,data=new_account.ddns.net
[WN] i=3,id=tk2,data=new_token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=new_mqtt.duckdns.org
[WN] ConMultiWifi
[WN] con2WF:SSID=HueNet1,PW=****
[WN] Remaining retry_time=3
WiFi-begin: return1 = 3
WiFi-begin: return2 = 3
[WN] WOK, lastConnectedIndex=0
[WN] con2WF:OK
[WN] SSID=HueNet1,RSSI=-21
[WN] IP=192.168.2.105
[WN] b:WOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
H
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org

HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
```

#### 4. Lost a WiFi and autoconnect to another WiFi AP

```
[WN] r:Check&WLost                      <=== Lost primary WiFi
[WN] r:WLost.ReconW
[WN] ConMultiWifi
[WN] Using index=1, lastConnectedIndex=0
[WN] con2WF:SSID=HueNet2,PW=****        <=== Connect secondary WiFi
[WN] Remaining retry_time=2
WiFi-begin: return1 = 3
WiFi-begin: return2 = 3
[WN] WOK, lastConnectedIndex=1
[WN] con2WF:OK                          <=== Success
[WN] SSID=HueNet2,RSSI=-48
[WN] IP=192.168.2.105
[WN] r:WOK
HHHHHHHHHH HHHHHHHHHH
```

#### 5. Reopen Config Portal if can't connect to any of the 2 WiFi APs

```
Start SAMD_WiFiNINA on SAMD NANO_33_IOT
WiFiManager_NINA_Lite v1.2.0
[WN] Hostname=SAMD-Master-Controller
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[WN] ======= Start Default Config Data =======
[WN] Hdr=WIFININA,SSID=SSID1,PW=password1
[WN] SSID1=SSID2,PW1=password2
[WN] BName=SAMD-Control
[WN] i=0,id=sv1,data=account.duckdns.org
[WN] i=1,id=tk1,data=token1
[WN] i=2,id=sv2,data=account.ddns.net
[WN] i=3,id=tk2,data=token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=mqtt.duckdns.org
[WN] ChkCrR:CrCCsum=0x21ce,CrRCsum=0x21ce
[WN] CCSum=0x1246,RCSum=0x1246
[WN] CrCCsum=0x21ce,CrRCsum=0x21ce
[WN] Valid Stored Dynamic Data
[WN] ======= Start Stored Config Data =======
[WN] Hdr=WIFININA,SSID=HueNet1,PW=****
[WN] SSID1=HueNet2,PW1=****
[WN] BName=Air-Control
[WN] i=0,id=sv1,data=new_account.duckdns.org
[WN] i=1,id=tk1,data=new_token1
[WN] i=2,id=sv2,data=new_account.ddns.net
[WN] i=3,id=tk2,data=new_token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=new_mqtt.duckdns.org
[WN] ConMultiWifi
[WN] con2WF:SSID=SSID,PW=password
[WN] Remaining retry_time=3
WiFi-begin: return1 = 4
WiFi-begin: return2 = 4
[WN] Remaining retry_time=2
WiFi-begin: return1 = 4
WiFi-begin: return2 = 4
[WN] Remaining retry_time=1
WiFi-begin: return1 = 4
WiFi-begin: return2 = 4
[WN] Failed using index=0, retry_time=0
[WN] con2WF:failed
[WN] b:NoW
[WN] SSID=WIFININA_51F485,PW=MyWIFININA_51F485
[WN] IP=192.168.4.1,CH=10
WiFi-beginAP3: return1 = 7
WiFi-beginAP3: return2 = 7
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org
FF
```

#### 6. DRD Not Detected:

```
Start SAMD_WiFiNINA on SAMD NANO_33_IOT
WiFiManager_NINA_Lite v1.2.0
[WN] Hostname=SAMD-Master-Controller
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[WN] ======= Start Default Config Data =======
[WN] Hdr=WIFININA,SSID=SSID1,PW=password1
[WN] SSID1=SSID2,PW1=password2
[WN] BName=SAMD-Control
[WN] i=0,id=sv1,data=account.duckdns.org
[WN] i=1,id=tk1,data=token1
[WN] i=2,id=sv2,data=account.ddns.net
[WN] i=3,id=tk2,data=token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=mqtt.duckdns.org
[WN] ChkCrR:CrCCsum=0x21ce,CrRCsum=0x21ce
[WN] CCSum=0x1246,RCSum=0x1246
[WN] CrCCsum=0x21ce,CrRCsum=0x21ce
[WN] Valid Stored Dynamic Data
[WN] ======= Start Stored Config Data =======
[WN] Hdr=WIFININA,SSID=HueNet1,PW=****
[WN] SSID1=HueNet2,PW1=****
[WN] BName=Air-Control
[WN] i=0,id=sv1,data=new_account.duckdns.org
[WN] i=1,id=tk1,data=new_token1
[WN] i=2,id=sv2,data=new_account.ddns.net
[WN] i=3,id=tk2,data=new_token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=new_mqtt.duckdns.org
[WN] ConMultiWifi
[WN] con2WF:SSID=HueNet1,PW=****
[WN] Remaining retry_time=3
WiFi-begin: return1 = 3
WiFi-begin: return2 = 3
[WN] WOK, lastConnectedIndex=0
[WN] con2WF:OK
[WN] SSID=HueNet1,RSSI=-21
[WN] IP=192.168.2.105
[WN] b:WOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
H
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org
HHHHHHHHH HHHHHHHHHH
```

#### 7. DRD detected and Config Portal is forcefully opened

```
Start SAMD_WiFiNINA on SAMD NANO_33_IOT
WiFiManager_NINA_Lite v1.2.0
[WN] Hostname=SAMD-Master-Controller
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[WN] Double Reset Detected
[WN] ======= Start Default Config Data =======
[WN] Hdr=WIFININA,SSID=SSID1,PW=password1
[WN] SSID1=SSID2,PW1=password2
[WN] BName=SAMD-Control
[WN] i=0,id=sv1,data=account.duckdns.org
[WN] i=1,id=tk1,data=token1
[WN] i=2,id=sv2,data=account.ddns.net
[WN] i=3,id=tk2,data=token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=mqtt.duckdns.org
[WN] ChkCrR:CrCCsum=0x21ce,CrRCsum=0x21ce
[WN] CCSum=0x1246,RCSum=0x1246
[WN] CrCCsum=0x21ce,CrRCsum=0x21ce
[WN] Valid Stored Dynamic Data
[WN] ======= Start Stored Config Data =======
[WN] Hdr=WIFININA,SSID=HueNet1,PW=****
[WN] SSID1=HueNet2,PW1=****
[WN] BName=Air-Control
[WN] i=0,id=sv1,data=new_account.duckdns.org
[WN] i=1,id=tk1,data=new_token1
[WN] i=2,id=sv2,data=new_account.ddns.net
[WN] i=3,id=tk2,data=new_token2
[WN] i=4,id=pt,data=8080
[WN] i=5,id=mq,data=new_mqtt.duckdns.org
[WN] b:StayInCfgPortal:DRD
[WN] SSID=WIFININA_51F485,PW=MyWIFININA_51F485
[WN] IP=192.168.4.1,CH=10
WiFi-beginAP3: return1 = 7
WiFi-beginAP3: return2 = 7
F
Your stored Credentials :
Blynk Server1 = new_account.duckdns.org
Token1 = new_token1
Blynk Server2 = new_account.ddns.net
Token2 = new_token2
Port = 8080
MQTT Server = new_mqtt.duckdns.org

```
---
---

#### Debug

Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT       Serial
#define WIFININA_DEBUG_OUTPUT           Serial

#define _WIFININA_LOGLEVEL_             2

#define DRD_GENERIC_DEBUG               true
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `WiFiNINA module/shield` or this library version.

Sometimes, the library will only work if you update the `WiFiNINA module/shield` core to the newer or older version because some function compatibility.

---
---
 
## Releases

### Release v1.2.0

1. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
2. Enforce WiFi Password minimum length of 8 chars
3. Enhance MultiWiFi connection logic

### Release v1.1.3

1. Fix invalid "blank" or NULL Config Data treated as Valid. Check [WiFiManager connection attempt to unconfigured ("blank") SSID after restart on SAMD #8](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/8)
2. Fix compiler warnings.

### Release v1.1.2

1. Fix MultiWiFi connection bug. Check [SAMD MultiWiFi issues when first WiFi SSID configured in CP is invalid or not available #6](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/6)

### Release v1.1.1

1. Fix USE_DYNAMIC_PARAMETERS bug.

#### Major Release v1.1.0

1. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header.
2. Add support to boards using WiFi101 library such as MKR1000
3. Fix Config Portal Bug. 
4. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
5. Use more efficient [FlashStorage_SAMD v1.1.0](https://github.com/khoih-prog/FlashStorage_SAMD) and [FlashStorage_STM32 v1.0.0](https://github.com/khoih-prog/FlashStorage_STM32)
6. Optimize code
7. Add Version String

### Release v1.0.5

1. Modify LOAD_DEFAULT_CONFIG_DATA logic.
4. Enhance MultiWiFi connection logic. 
5. Add Adafruit MQTT examples.

#### Major Release v1.0.4

1. Configurable **Config Portal Title** to be either HostName, BoardName or default undistinguishable names.
2. Optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input.
3. **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
4. Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
5. Add Board Name

Thanks to [Thor Johnson](https://github.com/thorathome) to test, suggest and encourage to add those new features in [**Blynk_WM Library**](https://github.com/khoih-prog/Blynk_WM), such as Default Credentials/Dynamic Params, Configurable Config Portal Title, DRD. Now those features are speading fast into libraries having similar functionalities.

#### Major Release v1.0.3

1. **Multiple WiFi Credentials (SSID, Password)** and system will autoconnect to the available WiFi AP. It will then autoreconnect to the remaining WiFi AP if the current connection is lost.
2. Add support to **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
3. WiFi Password max length is 63, according to WPA2 standard
4. Permit to input special chars such as **%** and **#** into data fields.
5. Add option to have built-in, yet configurable RFC-952-conformed DHCP hostname.
6. Fix bug

#### Release v1.0.2

1. Fix bug
2. Add support to **SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.

#### Release v1.0.1

1. Use new [**WiFiNINA_Generic library**](https://github.com/khoih-prog/WiFiNINA_Generic) to provide support to many more boards (Teensy, AVR Mega, SAM DUE, SAMD51, STM32, etc.) running WiFiNINA. The original WiFiNINA library only supports Nano-33 IoT, Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2.
2. Use new [**FlashStorage_SAMD library**](https://github.com/khoih-prog/FlashStorage_SAMD) to provide EEPROM/FlashStorage support to SAMD51 boards (Itsy-Bitsy M4, etc).

#### Release v1.0.0

1. New **powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved **automatically in EEPROM, SAMD EEPROM-emulated FlashStorage or SAM DUE DueFlashStorage**.
3. This is a Light-Weight Credentials / WiFi Connection Manager with fallback web configuration portal. Completely new to support **Teensy, SAM DUE, SAMD, STM32, etc. boards running WiFiNINA modules/shields.** with small memory (64+K bytes)
4. Config Portal AP SSID and Password will use 4 bytes of hardware unique macAddress, only for Teensy.

---
---

### TO DO

1. Support more boards

### DONE

 1. Adding dynamic custom parameters
 2. Add MultiWiFi and Auto(Re)Connect feature
 3. Add support to SAMD21, SAMD51, nRF52, etc.
 4. Many more to list ( DHCP Hostname, WPA2 password length, special chars, etc.)
 5. Add DRD
 6. Add default Credentials
 7. Add Dynamic parameters
 8. Add Configurable Config Portal Title
 9. Split each example into several manageable files.
10. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header
11. Add functions to control Config Portal from software or Virtual Switches.
12. Use more efficient [FlashStorage_SAMD v1.1.0](https://github.com/khoih-prog/FlashStorage_SAMD) and [FlashStorage_STM32 v1.00](https://github.com/khoih-prog/FlashStorage_STM32)
13. Add Version String and Table-of-Contents
14. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
15. Enforce WiFi Password minimum length of 8 chars


---
--- 

### Issues ###

Submit issues to: [WiFiManager_NINA_Lite issues](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues)

---
---

### Contributions and thanks

1. Thanks to [Darvesh7](https://github.com/Darvesh7) to report [When Saved Network is unavailable or credential changed bug](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/1) leading to the major release v1.0.3
2. Thanks to [Thor Johnson](https://github.com/thorathome) to test, suggest and encourage to add those new features in [Blynk_WM](https://github.com/khoih-prog/Blynk_WM), such as Default Credentials/Dynamic Params, Configurable Config Portal Title, DRD. Now those features are speading fast into libraries having similar functionalities.
3. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially **u-blox B302, B112 running as nRF52840/nRF52832**, has never been started and finished. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)
4. Thanks to [Pierluigi Colangeli](https://github.com/piecol) to make enhancement request in [Custom html header #4](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/4) leading to v1.1.0.
5. Thanks to [Michael "bizprof"](https://github.com/bizprof) to report bugs in 
  - [Won't compile for SAMD when USE_DYNAMIC_PARAMETERS set to FALSE #5](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/5) leading to v1.1.1, 
  - [SAMD MultiWiFi issues when first WiFi SSID configured in CP is invalid or not available #6](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/6) leading to v1.1.2.
  - [WiFiManager connection attempt to unconfigured ("blank") SSID after restart on SAMD #8](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/8) leading to v1.1.3 and v1.2.0


<table>
  <tr>
    <td align="center"><a href="https://github.com/thorathome"><img src="https://github.com/thorathome.png" width="100px;" alt="thorathome"/><br /><sub><b>⭐️ Thor Johnson</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Darvesh7"><img src="https://github.com/Darvesh7.png" width="100px;" alt="Darvesh7"/><br /><sub><b>Darvesh7</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/piecol"><img src="https://github.com/piecol.png" width="100px;" alt="piecol"/><br /><sub><b>Pierluigi Colangeli</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/bizprof"><img src="https://github.com/bizprof.png" width="100px;" alt="bizprof"/><br /><sub><b>⭐️ Michael "bizprof"</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/WiFiManager_NINA_Lite/blob/master/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang


