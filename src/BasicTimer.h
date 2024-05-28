#ifndef _RT_CORE_PLATFORM_BASIC_TIMER_H_
#define _RT_CORE_PLATFORM_BASIC_TIMER_H_

#include "./RTCorePlatformDeps.h"

/**
  * @brief Class that wraps millis() based timers for easier use.
  *
  *  A BasicTimer makes it easy to perform an action after a certain amount of milliseconds has passed.
  */
class BasicTimer
{
public:
  /**
    * @brief Construct a new TBasicTimer
    *
    * @param timeout The timers timeout in milliseconds
    */
  BasicTimer(unsigned long timeout = 500) : lastReset(0), storedTimeout(timeout) {};

  /**
    * @brief Copy Constructor
    */
  BasicTimer(const BasicTimer& other) : lastReset(other.lastReset),
    storedTimeout(other.storedTimeout) {};


  /**
    *  @brief Prepares the timer for use, equivalent to reset()
    *  @see reset()
    */
  void begin() { reset(); };

  /**
    *  @brief Prepares the timer for use and sets the timeout to the
    *         supplied value
    *
    *  @see reset()
    *  @see setTimeout()
    */
  void begin(unsigned long timeout) {
    setTimeout(timeout);
    reset();
  };

  /**
    * @brief Resets the timer (so that it is no longer expired)
    */
  void reset() { lastReset = now(); };

  /**
    * @brief Check if the timer has expired
    *
    * @return true If the timer has expired
    * @return false If it has yet to expire
    */
  bool hasExpired() const
  {
    auto current = now();
    if (current - lastReset > storedTimeout) return true;
    else return false;
  }

  /**
    * @brief Returns the timer's stored timeout time in milliseconds
    *
    * @return unsigned long
    */
  unsigned long timeout() const { return storedTimeout; };

  /**
    * @brief Get the current time in milliseconds
    *
    * @return unsigned long The current time in milliseconds
    */
  static unsigned long now()
  {
    return millis();
  }

  /**
    * @brief The amount of time that has elapsed since the timer
    *        was last reset in milliseconds.
    *
    * @return unsigned long The elapsed time in milliseconds
    */
  unsigned long elapsedTime() const {
    return (now() - lastReset);
  }

  /**
    * @brief Set the timer's timeout to the supplied value
    *
    * @param timeout The new timer period in milliseconds
    */
  void setTimeout(unsigned long timeout) { storedTimeout = timeout; };

  template<typename Functor>
  void onExpire(Functor cb) {
    if (hasExpired())
    {
      reset();
      cb();
    }
  }

  template<typename ArgType, typename Functor>
  void onExpire(Functor cb, ArgType arg)
  {
    if (hasExpired())
    {
      reset();
      cb(arg);
    }
  }

  template<typename ArgType1, typename ArgType2, typename Functor>
  void onExpire(Functor cb, ArgType1 arg1, ArgType2 arg2)
  {
    if (hasExpired())
    {
      reset();
      cb(arg1, arg2);
    }
  }

  template<typename ArgType1, typename ArgType2, typename Functor, typename... ArgTypesMore>
  void onExpire(Functor cb, ArgType1 arg1, ArgType2 arg2, ArgTypesMore... argsMore)
  {
    if (hasExpired())
    {
      reset();
      cb(arg1, arg2, argsMore...);
    }
  }

protected:
  unsigned long  lastReset; //!< The last timestamp at which the timer was reset
  unsigned long storedTimeout;//!< The timeout value in milliseconds
};

/**
  * @brief Template class for a timer with a static, constant Timeout value.
  *        This reduces the memory footprint of the class if you never want the
  *        timers time to change.
  *
  * @tparam TIMEOUT The timeout in milliseconds
  */
template <unsigned long TIMEOUT>
class StaticTimer
{
public:
  /**
    * @brief Construct a new TStaticTimer object
    *
    */
  StaticTimer() : lastReset(0) {};

  /**
    * @brief Reset the timer, setting its value to the current time
    *
    */
  void reset() { lastReset = now(); };

  /**
    * @brief Checks it the timer has expired
    *
    * @return true If the timeout has passed
    * @return false If not.
    */
  bool hasExpired() const
  {
    if (elapsedTime() > TIMEOUT) return true;
    else return false;
  }

  /**
    * @brief Gets the currenet timestamp in milliseconds
    *
    * @return unsigned long The current timestamp in milliseconds
    */
  unsigned long now() const
  {
    return millis();
  }

  /**
    * @brief The amount of time that has elapsed since the timer
    *        was last reset in milliseconds.
    *
    * @return unsigned long The elapsed time in milliseconds
    */
  unsigned long elapsedTime() const {
    return (now() - lastReset);
  }


  /**
    * @brief Runs the timer, executing the supplied function if the timer has expired.
    *
    * @param callback The function to execute
    * 
    */

  template<typename Functor>
  void onExpire(Functor cb) {
    if (hasExpired())
    {
      reset();
      cb();
    }
  }

  template<typename ArgType, typename Functor>
  void onExpire(Functor cb, ArgType arg)
  {
    if (hasExpired())
    {
      reset();
      cb(arg);
    }
  }

  template<typename ArgType1, typename ArgType2, typename Functor>
  void onExpire(Functor cb, ArgType1 arg1, ArgType2 arg2)
  {
    if (hasExpired())
    {
      reset();
      cb(arg1, arg2);
    }
  }

  template<typename ArgType1, typename ArgType2, typename Functor, typename... ArgTypesMore>
  void onExpire(Functor cb, ArgType1 arg1, ArgType2 arg2, ArgTypesMore... argsMore)
  {
    if (hasExpired())
    {
      reset();
      cb(arg1, arg2, argsMore...);
    }
  }

protected:
  unsigned long  lastReset;
};

#endif // ! _RT_PEDAL_LIB_BASIC_TIMER_H
