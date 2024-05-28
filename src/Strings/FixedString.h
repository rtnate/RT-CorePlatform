#pragma once

#include "./StringDeps.h"
#include "./StringRef.h"
#include "./StringBuffer.h"

class FixedString: public Print {
  public:
    FixedString(char* buffer, uint16_t bufferSize): 
      buffer_(buffer, bufferSize), index_(0){}

    FixedString(StringBuffer& buffer): buffer_(buffer), index_(0){};

    template<int LENGTH>
    FixedString(StaticStringBuffer<LENGTH>& buffer): buffer_(buffer.data(), buffer.kSize),
      index_(0){};

    FixedString() :
      buffer_(nullptr, 0), index_(0){}
    //Information About This String

    int currentIndex() const {
      return index_;
    }

    int remainingCapacity() {
      return buffer_.capacity() - currentIndex();
    }

    int totalCapacity() {
      return buffer_.capacity();
    }

    int length() {
      return buffer_.length();
    }

    int putC(char c) {
      if (remainingCapacity() > 0) {
        auto str = buffer_.data();
        str[index_++] = c;
        terminateString();
        return 1;
      }
      else {
        return 0;
      }
    }

    int append(char c) {
      return putC(c);
    }

    int append(StringRef other);

    int append(StringRef other, size_t lengthToAppend);

    int append(int number, int radix = 10);

    void truncate(size_t newLength);

    void softTruncate(size_t newLength, size_t ellipsesLength);

    void reset() {
      setIndex(0);
    }

    FixedString start() {
      return FixedString(buffer_);
    }

    FixedString end() {
      auto len = length();
      auto size = buffer_.size();
      return FixedString(buffer_.data() + len, size - len);
    }

    char charAt(size_t loc) const {
      if (loc >= buffer_.size()) return '\0';
      else return buffer_[loc];
    }

    int compareWith(const StringRef other) const {
      return StringRef::compare((StringRef)*this, other);
    }

    int compareWith(const StringRef other, size_t noChars) const {
      return StringRef::compare(*this, other, noChars);
    }

    bool equalsIgnoreCase(StringRef s) const {
      return StringRef(*this).equalsIgnoreCase(s);
    }

    bool startsWith(StringRef prefix) const {
      return StringRef(*this).startsWith(prefix);
    }

    bool startsWith(StringRef prefix, size_t offset) const {
      return StringRef(*this).startsWith(prefix, offset);
    }

    bool endsWith(StringRef suffix) const {
      return StringRef(*this).endsWith(suffix);
    }

    int indexOf(char ch) const {
      return indexOf(ch, 0);
    }

    int indexOf(char ch, size_t fromIndex) const {
      return StringRef(*this).indexOf(ch, fromIndex);
    }

    int indexOf(StringRef str) const {
      return indexOf(str, 0);
    }

    int indexOf(StringRef str, size_t fromIndex) const {
      return StringRef(*this).indexOf(str, fromIndex);
    }

    char operator[](size_t index) const {
      return charAt(index);
    }

    char& operator[](size_t index) {
      static char dummyChar = '\0';
      if (index < buffer_.size()) {
        return buffer_[index];
      }
      else {
        return dummyChar;
      }
    }

    bool seekStart(int offset = 0) {
      int next = offset;
      int len = length();
      if (next >= len || offset < 0) {
        return false;
      } else {
        setIndex(next);
        return true;
      }
    }

    bool seek(int offset) {
      int next = index_ + offset;
      int len = length();
      if (next >= len || next < 0) {
        return false;
      }
      else {
        setIndex(next);
        return true;
      }
    }

    bool seekEnd() {
      int len = length();
      setIndex(len);
      return true;
    }

    bool seekEnd(int offset) {
      int len = length();
      int next = len + offset;
      if (next >= len || next < 0) {
        return false;
      }
      else {
        setIndex(next);
        return true;
      }
    }

    FixedString operator+=(StringRef str) {
      append(str);
      return *this;
    }

    FixedString operator+=(char c) {
      append(c);
      return *this;
    }

    FixedString operator+=(int num) {
      append(num);
      return *this;
    }


    bool operator==(StringRef other) {
      return StringRef::compare(*this, other) == 0;
    }

    bool operator!=(StringRef other) {
      return StringRef::compare(*this, other) != 0;
    }

    bool operator<=(StringRef other) {
      return StringRef::compare(*this, other) <= 0;
    }

    bool operator>=(StringRef other) {
      return StringRef::compare(*this, other) >= 0;
    }

    bool operator<(StringRef other) {
      return StringRef::compare(*this, other) < 0;
    }

    bool operator>(StringRef other) {
      return StringRef::compare(*this, other) > 0;
    }

    size_t write(uint8_t c) override{
      return putC(c);
    }

    size_t write(const uint8_t* buffer, size_t size) override;

    size_t printf(const char* format, ...);

    size_t printf(size_t noChars, const char* format, ...);

    const char* c_str() const {
      return buffer_.data();
    }

    operator StringRef() const {
      return (StringRef)buffer_;
    }
  protected:
    StringBuffer buffer_;
    int index_;

    void setIndex(int newIndex) {
      newIndex = newIndex < 0 ? 0 : newIndex;
      newIndex = newIndex > totalCapacity() ? totalCapacity() : newIndex;
      index_ = newIndex;
      terminateString();
    }
    void terminateString() {
      buffer_[index_] = '\0';
    }

    char* getCurrentPtr() {
      return buffer_.data() + index_;
    }
};