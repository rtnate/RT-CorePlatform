#pragma once

#include "./StringDeps.h"
#include "./StringRef.h"

#ifdef __GNUC__
#ifndef PACKED
#define PACKED( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif
#endif

#ifdef _MSC_VER
#ifndef PACKED
#define PACKED( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif
#endif


class StringBuffer {
  public:
    StringBuffer(char* pData, int bufSize):
      data_(pData), size_(pData != nullptr ? bufSize : 0){};

    StringBuffer() :
      data_(nullptr), size_(0) {};

    int size() const {
      return size_;
    }

    int capacity() const {
      return size_ - 1;
    }

    int length() const {
      return strlen(data_);
    }

    void clear() {
      if (data_) memset(data_, 0, size_);
    }

    void reset() {
      if (data_) data_[0] = '\0';
    }

    char* data() {
      return data_;
    }

    const char* data() const {
      return data_;
    }

    char operator[](int index) const {
      return data_[index];
    }

    char& operator[](int index) {
      return data_[index];
    }

    operator StringRef() const {
      return StringRef(data_);
    }
  protected:
      char *const data_;
      const unsigned int size_;
};

template <int LENGTH>
class StaticStringBuffer {
  public:
    static_assert(LENGTH > 0, "LENGTH Template parameter must be greater than zero");
    static constexpr int kSize = LENGTH;

    StaticStringBuffer(): data_{}{};

    int size() const {
      return kSize;
    }

    int capacity() const {
      return kSize - 1;
    }

    int length() const {
      return strlen(data_);
    }

    void clear() {
      memset(data_, 0, kSize);
    }

    void reset() {
      data_[0] = '\0';
    }

    char* data() {
      return data_;
    }

    operator StringBuffer() {
      return StringBuffer(data_, kSize);
    }

    operator StringRef() const {
      return StringRef(data_);
    }
  protected:
    char data_[kSize];
};
