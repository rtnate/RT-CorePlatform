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

#include 

#endif


#endif