// Arduino-compatible wrapper header for Pisco Code library.

#ifndef PISCO_CODE_ARDUINO_H
#define PISCO_CODE_ARDUINO_H

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
