# ESP32-C3 SuperMini + Ra-02 SX1278 Meshtastic

Custom Meshtastic firmware build for a minimal DIY node:

- Board: ESP32-C3 SuperMini
- LoRa module: AI-Thinker Ra-02 / SX1278, 433 MHz
- Firmware base: Meshtastic firmware `2.7.23.b2bda3b`
- Radio path inside Meshtastic: `RF95` / SX127x
- PlatformIO environment: `c3ra02`

This repository is a Meshtastic firmware tree with one custom board variant added for the ESP32-C3 SuperMini + Ra-02 wiring.

## Hardware

Use 3.3 V only. Do not power the Ra-02 from 5 V.

Attach an antenna before powering the LoRa module.

| Ra-02 / SX1278 | ESP32-C3 SuperMini |
| --- | --- |
| SCK | GPIO4 |
| MISO | GPIO5 |
| MOSI | GPIO6 |
| NSS / CS | GPIO7 |
| RST | GPIO8 |
| DIO0 / IRQ | GPIO3 |
| DIO1 | not connected |
| 3.3V | 3.3V |
| GND | GND |

## Custom Variant

The custom variant lives here:

```text
variants/esp32c3/diy/esp32c3_super_mini_ra02/
```

Important files:

```text
variants/esp32c3/diy/esp32c3_super_mini_ra02/platformio.ini
variants/esp32c3/diy/esp32c3_super_mini_ra02/variant.h
```

The PlatformIO environment name is intentionally short:

```text
c3ra02
```

Short paths matter on Windows because Meshtastic pulls many libraries with long names. Building from a short folder such as `C:\src\mt-fw` avoids PlatformIO copy/path errors.

## Region and Frequency

The Ra-02 module used here is a 433 MHz SX1278 module.

Meshtastic's default `UNSET` region may start around 906 MHz, which is wrong for this module. The custom variant therefore forces `EU_433` at compile time:

```cpp
#define USERPREFS_CONFIG_LORA_REGION meshtastic_Config_LoRaConfig_RegionCode_EU_433
#define REGULATORY_LORA_REGIONCODE meshtastic_Config_LoRaConfig_RegionCode_EU_433
```

Verified boot log:

```text
Wanted region 2, regulatory override to EU_433
RF95Interface(cs=7, irq=3, rst=8, busy=-1)
Radio freq=433.875
Set radio: region=EU_433, name=LongFast, config=0, ch=3, power=10
frequency: 433.875000
Final Tx power: 10 dBm
RF95 init result 0
RF95 init success
```

Do not select `RU` in the Meshtastic app for this hardware. In Meshtastic, `RU` is an 868 MHz region. Use `EU_433`.

## Build

Open this folder in VS Code with PlatformIO installed, or use a terminal:

```powershell
cd C:\src\mt-fw
pio run -e c3ra02
```

## Flash

List ports:

```powershell
pio device list
```

Flash a module, replacing `COMx` with your actual port:

```powershell
pio run -e c3ra02 -t upload --upload-port COMx
```

Serial monitor:

```powershell
pio device monitor -b 115200 --port COMx
```

## VS Code Tasks

This repo includes VS Code tasks:

```text
Meshtastic c3ra02: Build
Meshtastic c3ra02: Upload
Meshtastic c3ra02: Monitor
Meshtastic: List Ports
```

Run them from:

```text
Ctrl+Shift+P -> Tasks: Run Task
```

The upload and monitor tasks ask for a serial port.

## Meshtastic App Setup

Recommended app settings:

```text
Region: EU_433
Modem Preset: Long Fast
Frequency Slot: default / 3
Hop Limit: 3
TX Enabled: On
Primary Channel: LongFast
PSK: default
```

The safest way to make two nodes match is to share the Primary Channel from the first node and import it on the second node.

See also:

```text
APP_SETUP_RU.md
PROJECT_GUIDE_RU.md
```

## Known Issues and Notes

Meshtastic support for SX127x/SX1278 is less straightforward than modern SX126x/LR11xx boards. This build uses the existing `RF95Interface` path and has been verified to initialize the radio successfully on ESP32-C3 SuperMini boards.

If upload fails with:

```text
Could not open COMx, the port is busy or doesn't exist
```

close PlatformIO Serial Monitor, Arduino Serial Monitor, or any other terminal using that COM port. A stuck `platformio device monitor` process can hold the port.

If the board prints:

```text
boot:0x5 (DOWNLOAD)
waiting for download
```

it is in bootloader mode. Release `BOOT`, unplug/replug USB, or press `RESET` without holding `BOOT`.

If Windows path errors occur while installing dependencies, build from a short path. Example:

```text
C:\src\mt-fw
```

## Upstream

This project is based on the official Meshtastic firmware:

```text
https://github.com/meshtastic/firmware
```

Meshtastic firmware is GPL-3.0 licensed. The original license file is preserved in this repository.
.
