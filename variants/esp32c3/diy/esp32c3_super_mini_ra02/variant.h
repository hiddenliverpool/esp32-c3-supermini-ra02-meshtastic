#ifndef _VARIANT_ESP32C3_SUPER_MINI_RA02_
#define _VARIANT_ESP32C3_SUPER_MINI_RA02_

#ifdef __cplusplus
extern "C" {
#endif

// ESP32-C3 SuperMini has no onboard Meshtastic display in this wiring.
#define HAS_SCREEN 0

// BOOT button.
#define BUTTON_PIN 9

// Disable GPS defaults for this minimal node.
#define HAS_GPS 0
#undef GPS_RX_PIN
#undef GPS_TX_PIN

// AI-Thinker Ra-02 / SX1278 on 433 MHz.
#define USE_RF95
#define USERPREFS_CONFIG_LORA_REGION meshtastic_Config_LoRaConfig_RegionCode_EU_433
#define REGULATORY_LORA_REGIONCODE meshtastic_Config_LoRaConfig_RegionCode_EU_433

#define LORA_SCK 4
#define LORA_MISO 5
#define LORA_MOSI 6
#define LORA_CS 7

#define LORA_DIO0 3
#define LORA_RESET 8
#define LORA_DIO1 RADIOLIB_NC
#define LORA_DIO2 RADIOLIB_NC

// Ra-02 has no external TX/RX enable pins or TCXO control pins.
#define RF95_MAX_POWER 17

#ifdef __cplusplus
}
#endif

#endif
