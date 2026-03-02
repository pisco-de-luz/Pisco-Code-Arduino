# Pisco Code — Arduino Library

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

**Pisco Code** encodes decimal, hexadecimal, or binary values as LED blink patterns using a single status LED. No serial port or display needed.

This is the **Arduino-compatible distribution** of the [Pisco Code](https://github.com/pisco-de-luz/Pisco-Code) library. It is automatically generated from the main repository on each release.

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
        pisco_code::SignalCode{42},
        pisco_code::NumberBase::DEC,
        pisco_code::NumDigits{0});
}

void loop()
{
    emitter.loop();
    delay(1);
}
```

## How It Works

Pisco Code extends the classic blink-count method with a **framing signal** — a low-brightness phase before the digit sequence begins. This makes every digit (including zero) unambiguous and clearly separated.

| Feature | Description |
|---|---|
| Bases | Decimal, binary, hexadecimal |
| Negative values | Long-blink prefix |
| Zero digits | Explicit gap representation |
| Min digits | Configurable (e.g., always show 3 digits) |
| Controllers | Software PWM (GPIO) and Hardware PWM |

For full documentation, architecture details, and cross-platform support (AVR, STM32, native), see the **[main repository](https://github.com/pisco-de-luz/Pisco-Code)**.

## Changelog

See the [Changelog](https://github.com/pisco-de-luz/Pisco-Code/blob/main/CHANGELOG.md) in the main repository.

## License

MIT — see [LICENSE](LICENSE).
