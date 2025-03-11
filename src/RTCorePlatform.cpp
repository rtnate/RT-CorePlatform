#if !defined(ARDUINO) || !defined(USE_ARDUINO)

#include "RTCorePlatform.h"

#if JUCE_MODULE_AVAILABLE_juce_core

#include <JuceHeader.h>

extern "C" {
  uint32_t millis() {
    int64_t hrTicks = juce::Time::getHighResolutionTicks();
    double secs = juce::Time::highResolutionTicksToSeconds(hrTicks);
    double ms = secs * 1000.f;
    return (uint32_t)ms;
  }

  uint32_t micros() {
    int64_t hrTicks = juce::Time::getHighResolutionTicks();
    double secs = juce::Time::highResolutionTicksToSeconds(hrTicks);
    double us = secs * 1000000.;
    return (uint32_t)us;
  }

  void delay(uint32_t ms) {
    juce::Thread::sleep(ms);
  }

  void delayMicroseconds(uint32_t us) {
    if (us <= 1000.f) {
      delay(1);
    } else {
      delay(us / 1000.f);
    }
  }
}

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <Windows.h>

extern "C" {
  void get_micros_uli(ULARGE_INTEGER& uli)
  {
    SYSTEMTIME st;
    GetSystemTime(&st);
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    uli.HighPart = ft.dwHighDateTime;
    uli.LowPart = ft.dwLowDateTime;
  }

  uint64_t get_micros_ull()
  {
    ULARGE_INTEGER uli;
    get_micros_uli(uli);
    return (uint64_t)(uli.QuadPart / 10ull);
  }
  uint32_t millis() {
    auto us_ull = get_micros_ull();
    auto ms_ull = us_ull / 1000ull;
    return (uint32_t)ms_ull;
  }

  uint32_t micros() {
    return (uint32_t)(get_micros_ull);
  }

  void delay(uint32_t ms) {
    Sleep(ms);
  }

  void delayMicroseconds(uint32_t us) {
    if (us <= 1000.f) {
      delay(1);
    }
    else {
      delay(us / 1000.f);
    }
  }
}

#endif


#endif