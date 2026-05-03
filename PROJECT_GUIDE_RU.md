# ESP32-C3 SuperMini + Ra-02 Meshtastic

Это рабочая папка VS Code для кастомной сборки Meshtastic под:

- ESP32-C3 SuperMini
- AI-Thinker Ra-02 / SX1278 433 MHz
- Radio branch Meshtastic: RF95 / SX127x
- Environment PlatformIO: `c3ra02`

## Главное

Кастомный вариант платы лежит здесь:

```text
variants/esp32c3/diy/esp32c3_super_mini_ra02/variant.h
```

В нем заданы пины:

```text
SCK  = GPIO4
MISO = GPIO5
MOSI = GPIO6
CS   = GPIO7
RST  = GPIO8
DIO0 = GPIO3
DIO1 = not connected
```

И принудительный регион:

```cpp
#define USERPREFS_CONFIG_LORA_REGION meshtastic_Config_LoRaConfig_RegionCode_EU_433
#define REGULATORY_LORA_REGIONCODE meshtastic_Config_LoRaConfig_RegionCode_EU_433
```

Это важно: без этого Meshtastic может стартовать в `UNSET` и уйти на 906 MHz. С этим вариантом старт подтвержден на `433.875 MHz`.

## Проверенный лог

На обеих платах мы получили:

```text
Wanted region 2, regulatory override to EU_433
Radio freq=433.875
Set radio: region=EU_433, name=LongFast
frequency: 433.875000
RF95 init success
```

## VS Code задачи

В VS Code нажми `Ctrl+Shift+P` -> `Tasks: Run Task`.

Доступные задачи:

```text
Meshtastic c3ra02: Build
Meshtastic c3ra02: Upload
Meshtastic c3ra02: Monitor
Meshtastic: List Ports
```

## Команды в терминале

Сборка:

```powershell
pio run -e c3ra02
```

Прошивка платы:

```powershell
pio run -e c3ra02 -t upload --upload-port COMx
```

Прошивка платы:

```powershell
pio run -e c3ra02 -t upload --upload-port COMx
```

Монитор:

```powershell
pio device monitor -b 115200 --port COMx
pio device monitor -b 115200 --port COMx
```

## Если порт занят

Закрой Serial Monitor в VS Code/Arduino IDE. Если не помогло, проверь зависший монитор:

```powershell
Get-Process | Where-Object { $_.ProcessName -match 'platformio|python' }
```

Ранее порт держал зависший `platformio device monitor`.

## Если плата пишет waiting for download

Это bootloader mode. Отпусти `BOOT`, отключи USB, подключи обратно без `BOOT` или нажми `RESET` без `BOOT`.

