#pragma once

#include "./FixedString.h"

template<unsigned int LENGTH>
class StaticString : public FixedString {
  static constexpr uint16_t MAX_LEN = UINT16_MAX;
  static_assert((LENGTH < MAX_LEN), "Maximum Length Static String is 65535 chars");
  public:
    StaticString(): FixedString(sbuffer_.data(), LENGTH), sbuffer_(){};
  protected:
    StaticStringBuffer<LENGTH> sbuffer_;
};
