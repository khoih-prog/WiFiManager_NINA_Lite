## WiFiManager_NINA_Lite (Light Weight Credentials / WiFi Manager for WiFiNINA modules/shields)

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_NINA_Lite.svg?)](https://www.ardu-badge.com/WiFiManager_NINA_Lite)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiManager_NINA_Lite.svg)](https://github.com/khoih-prog/WiFiManager_NINA_Lite/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiManager_NINA_Lite/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiManager_NINA_Lite.svg)](http://github.com/khoih-prog/WiFiManager_NINA_Lite/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Release v1.5.0](#release-v150)
  * [Release v1.4.1](#release-v141)
  * [Major Release v1.4.0](#major-release-v140)
  * [Release v1.3.1](#release-v131)
  * [Major Release v1.3.0](#major-release-v130)
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


---
---

## Changelog

### Release v1.5.0

1. Fix the blocking issue in loop(). Check [retries block the main loop #18](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/18)
2. Drop support to `AVR Mega`
3. Update `Packages' Patches`


### Release v1.4.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Major Release v1.4.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
2. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
3. Update `Packages' Patches`
4. Add `LibraryPatches` for [**Adafruit_MQTT_Library**](https://github.com/adafruit/Adafruit_MQTT_Library) to fix compiler error for RP2040-based and many other boards.

### Release v1.3.1

1. Fix createHTML bug.

### Major Release v1.3.0

1. Enable scan of WiFi networks for selection in Configuration Portal. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_NINA_Lite/pull/10). Now you can select optional **SCAN_WIFI_NETWORKS**, **MANUAL_SSID_INPUT_ALLOWED** to be able to manually input SSID, not only from a scanned SSID lists and **MAX_SSID_IN_LIST** (from 2-15)
2. Minor enhancement to not display garbage when data is invalid

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



