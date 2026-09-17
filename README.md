# esp32-charizard-display

An animated Charizard sprite running on an ESP32, displayed on a 1.8" ST7735 TFT screen — built with Arduino and the TFT_eSPI library.

The sprite plays through an 11-frame idle animation loop, similar to the classic battle-screen "breathing" animation from the mainline Pokémon games.

## Demo

*(Add a photo or short video of your screen here once you have one — this is the best part of the README!)*

## Hardware used

| Part | Notes |
|---|---|
| ESP32-WROOM-32 Dev Board | Any standard 38-pin ESP32 dev board |
| 1.8" TFT Display (ST7735, 128x160, SPI) | 4-wire SPI interface |
| Breadboard | Used for power distribution (3.3V / GND) |
| Jumper wires | Male-to-male |

## Wiring

| TFT Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| CS | GPIO 2 |
| RESET | GPIO 16 |
| DC (A0) | GPIO 4 |
| SDA (MOSI) | GPIO 23 |
| SCK | GPIO 18 |
| LED | 3.3V |

> Note: pin choice is somewhat flexible on the ESP32 — these were chosen to keep all wiring on one side of this particular dev board layout. If you rewire differently, make sure to update `User_Setup.h` (see below) to match.

## Software setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support via **File → Preferences → Additional Boards Manager URLs**:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
   Then install **esp32 by Espressif Systems** via Boards Manager.
3. Install the **TFT_eSPI** library (by Bodmer) via Library Manager.
4. Edit `TFT_eSPI/User_Setup.h` (inside your Arduino libraries folder) with the following:
   ```cpp
   #define ST7735_DRIVER
   #define TFT_WIDTH  128
   #define TFT_HEIGHT 160
   #define ST7735_REDTAB

   #define TFT_MOSI 23
   #define TFT_SCLK 18
   #define TFT_CS   2
   #define TFT_DC   4
   #define TFT_RST  16

   #define TFT_RGB_ORDER TFT_BGR
   ```
   > The exact `TAB` option (`REDTAB`/`GREENTAB`/etc.) and `TFT_RGB_ORDER` value can vary between individual display units from the same batch — if colors look wrong or there's edge noise/static, try cycling through the other TAB options and RGB/BGR settings.

5. Select **Tools → Board → ESP32 Dev Module**, and the correct COM port.
6. Open `charizard_animation.ino` (with `sprites.h` in the same folder) and upload.

## How the sprite data was made

1. Sourced an animated GIF sprite (11 frames)
2. Split the GIF into individual PNG frames using [ezgif.com/split](https://ezgif.com/split)
3. Resized each frame to 96x64px, preserving aspect ratio
4. Filled transparent backgrounds with solid black (to match the display's black background, avoiding the need for alpha blending)
5. Converted each frame to a C byte array using the [LVGL Image Converter](https://lvgl.io/tools/imageconverter), output format **RGB565**, **C array**
6. Cleaned up each generated file (stripped the LVGL wrapper struct, kept just the raw `uint8_t` array) and combined all 11 into `sprites.h`

## Customization

- **Animation speed**: change `frameDelay` in the `.ino` file (higher = slower)
- **Sprite size**: change the `SCALE` constant (e.g., `1.3`, `1.5`, `2.0`)
- **Swap in a different Pokémon**: repeat the sprite conversion steps above with a new GIF, and update the array names/count in the `.ino` file accordingly

## Credits

Sprite artwork sourced from [Project Pokémon](https://projectpokemon.org/) sprite resources. Pokémon and Charizard are trademarks of Nintendo/Game Freak/Creatures Inc. This is a personal, non-commercial hobby project.
