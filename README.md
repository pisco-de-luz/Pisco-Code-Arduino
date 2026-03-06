# Pisco Code — Arduino Library

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

**Pisco Code** encodes decimal, hexadecimal, or binary values as LED blink patterns using a single status LED. No serial port or display needed.

This is the **Arduino-compatible distribution** of the [Pisco Code](https://github.com/pisco-de-luz/Pisco-Code) library. It is automatically generated from the main repository on each release.

> **⚠️ Requires C++17** — Works out of the box with **ESP32, RP2040 (Pico), STM32, SAMD, ESP8266** and other boards whose toolchain defaults to C++17.  
> Other boards (e.g. Arduino AVR) can be used by enabling C++17 manually — see [Enabling C++17 on older boards](#enabling-c17-on-older-boards) below.

## Installation

### Arduino IDE Library Manager

1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for **Pisco-Code**
4. Click **Install**

### Manual Installation

1. Download the latest release `.zip` from [Releases](https://github.com/pisco-de-luz/Pisco-Code-Arduino/releases)
2. In Arduino IDE: **Sketch → Include Library → Add .ZIP Library…**

## Quick Start

```cpp
#include <Pisco-Code.h>

bool ledOnboard(pisco_code::LedControlCode code)
{
    switch (code)
    {
        case pisco_code::LedControlCode::ON:
            digitalWrite(LED_BUILTIN, HIGH);
            return true;
        case pisco_code::LedControlCode::OFF:
            digitalWrite(LED_BUILTIN, LOW);
            return true;
        default:
            return false;
    }
}

pisco_code::LedControllerSoftwarePwm controller(ledOnboard);
pisco_code::SignalEmitter             emitter(controller);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    emitter.showCode(
        pisco_code::SignalCode{103},
        pisco_code::Radix::DEC,
        pisco_code::NumDigits{0});
}

void loop()
{
    emitter.loop();
    delay(1);
}
```

## How It Works

Most embedded projects lack a convenient way to observe internal variables — serial ports, debuggers, or displays aren't always available. Pisco Code solves this by encoding values as **LED blink patterns** that anyone can read by eye.

### The Problem with Simple Blink Counting

A common approach is to blink an LED *n* times to represent the value *n*. For multi-digit numbers like `312`, you blink 3 times, pause, 1 time, pause, 2 times:

![code312.png](https://github.com/pisco-de-luz/Pisco-Code/blob/6c91251ed2d3033bc74d414339b4a64d40685235/graphics/code312.png)

This works — but **breaks down for zeros** (how do you blink 0 times?) and can be hard to follow.

### The Pisco Code Solution

Pisco Code adds a **framing signal** — a dim glow before each digit sequence begins. This makes every digit unambiguous, including zero:

**Code `121`:**

![Video-Code-121-132x132.gif](https://github.com/pisco-de-luz/Pisco-Code/blob/d0bb059eef8c726219ba4b1a40f07471f648127f/graphics/Video-Code-121-132x132.gif)
<img src="https://github.com/pisco-de-luz/Pisco-Code/blob/2d7ab53852a28b9fdf24be6b03f43a6450f9fef0/graphics/pisco-code-121.png" height="132">

**Code `120` (with a zero digit):**

![Pisco-Code-120-144x144.gif](https://github.com/pisco-de-luz/Pisco-Code/blob/ba3e80ebc5cc06cf77d8f8e30f36b71e3b5d880f/graphics/Pisco-Code-120-144x144.gif)
<img src="https://github.com/pisco-de-luz/Pisco-Code/blob/9d276453b1f99df96e158106dcbb28b7e36d6daf/graphics/pisco-code-120.png" height="144">

**Minimum digits (e.g. `002` for 0.02 V sensor reading):**

![Pisco-Code-002-144x144.gif](https://github.com/pisco-de-luz/Pisco-Code/blob/b1c607510b4095d7174fb170666a0196a63d295a/graphics/Pisco-Code-002-144x144.gif)
<img src="https://github.com/pisco-de-luz/Pisco-Code/blob/9d276453b1f99df96e158106dcbb28b7e36d6daf/graphics/pisco-code-002.png" height="144">

**Negative values (`-12` — long blink prefix):**

![Pisco-Code-Negative12-144x144.gif](https://github.com/pisco-de-luz/Pisco-Code/blob/347a2f6999becbef7c22bfab5b0d4cb3d843b71c/graphics/Pisco-Code-Negative12-144x144.gif)
<img src="https://github.com/pisco-de-luz/Pisco-Code/blob/d46fea2847a2d3f49e9fccbcebee1c75f28df785/graphics/pisco-code-12-negative.png" height="144">

### Features

| Feature | Description |
|---|---|
| Bases | Decimal, binary, hexadecimal |
| Negative values | Long-blink prefix |
| Zero digits | Explicit gap representation |
| Min digits | Configurable (e.g., always show 3 digits for 0–5 V readings) |
| Controllers | Software PWM (GPIO toggle) and Hardware PWM (smooth dimming) |
| Memory | No dynamic allocation, no exceptions — ideal for constrained MCUs |

### Real-World Use

Pisco Code has been used in the [Pisco de Luz](https://www.piscodeluz.org/?lang=en) project since 2020, reading battery voltage, solar panel output, temperature, and usage hours in off-grid solar lighting systems — all through a single LED.

For full documentation, architecture details, and cross-platform support (AVR, STM32, native), see the **[main repository](https://github.com/pisco-de-luz/Pisco-Code)**.

## Enabling C++17 on older boards

Some boards (e.g. Arduino AVR — Uno, Mega, Nano) ship with a toolchain that defaults to C++11. You can switch to C++17 by creating a **`platform.local.txt`** file:

1. Find your board's **`platform.txt`**. Common locations:
   | OS | Path |
   |---|---|
   | Windows | `%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\avr\<version>\` |
   | macOS | `~/Library/Arduino15/packages/arduino/hardware/avr/<version>/` |
   | Linux | `~/.arduino15/packages/arduino/hardware/avr/<version>/` |

2. In that **same folder**, create a new file called **`platform.local.txt`** with the following line:
   ```
   compiler.cpp.extra_flags=-std=gnu++17
   ```

3. Restart the Arduino IDE and recompile.

> **Note:** `platform.local.txt` overrides settings without modifying the original `platform.txt`, so board-manager updates won't undo your change.

## Changelog

See the [Changelog](https://github.com/pisco-de-luz/Pisco-Code/blob/main/CHANGELOG.md) in the main repository.

## License

MIT — see [LICENSE](LICENSE).
