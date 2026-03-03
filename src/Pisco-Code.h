// Arduino-compatible wrapper header for Pisco Code library.

#ifndef PISCO_CODE_ARDUINO_H
#define PISCO_CODE_ARDUINO_H

// ── C++17 requirement ──────────────────────────────────────────────────
// The Pisco-Code library uses C++14/C++17 features (relaxed constexpr,
// inline variables, [[nodiscard]], auto return-type deduction).
//
// Boards such as ESP32, RP2040, STM32, SAMD, and ESP8266 already
// default to C++17 and work out of the box.
//
// If your board defaults to an older standard (e.g. Arduino AVR), you
// can enable C++17 manually by creating a file called
// "platform.local.txt" next to your board's "platform.txt" containing:
//   compiler.cpp.extra_flags=-std=gnu++17
// See the README for details.
#if __cplusplus < 201703L
#error "Pisco-Code requires C++17 or later. Your current toolchain " \
       "defaults to an older standard. Boards like ESP32, RP2040, "  \
       "STM32, and SAMD work out of the box. For other boards "      \
       "(e.g. AVR) create a platform.local.txt next to your board's " \
       "platform.txt containing: "                                    \
       "compiler.cpp.extra_flags=-std=gnu++17 "                       \
       "See the library README."
#endif

// ── Arduino macro workaround ──────────────────────────────────────────
// Arduino's Print.h defines BIN, OCT, DEC, HEX as preprocessor macros
// (e.g. #define BIN 2). These clash with the pisco_code::NumberBase enum
// members of the same name.  Undefine them before pulling in the library;
// the scoped enum (NumberBase::BIN, etc.) replaces them safely.
#ifdef BIN
#undef BIN
#endif
#ifdef OCT
#undef OCT
#endif
#ifdef DEC
#undef DEC
#endif
#ifdef HEX
#undef HEX
#endif

#include "pisco_code.hpp"

#endif // PISCO_CODE_ARDUINO_H
