#ifndef _RT_CORE_PLATFORM_DEPS_H_
#define _RT_CORE_PLATFORM_DEPS_H_

#include <stdint.h>

#if defined(ARDUINO) || defined(RT_PEDAL_LIB_USE_ARDUINO)
#include <Arduino.h>
#define RT_HAS_ARDUINO 1
#else 
#ifdef __cplusplus
extern "C" {
#endif
  uint32_t millis();
  uint32_t micros();
  void delay(uint32_t ms);
  void delayMicroseconds(uint32_t us);
#ifdef __cplusplus
}
#endif

#include "./Deps/Print.h"
#include "./Deps/Printable.h"
#endif

#endif