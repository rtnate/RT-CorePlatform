#pragma once

#include "./StringDeps.h"
#include <cstring>


#if JUCE_MODULE_AVAILABLE_juce_core
  #define USE_JUCE_STRING 1
  #define USE_STD_STRING 1
#endif


#if USE_JUCE_STRING
  #include <JuceHeader.h>
#endif 

#if USE_STD_STRING 
  #include <string>
#endif

class StringRef {
  public:
    constexpr StringRef(): stringbuf_(EmptyString){};

    constexpr StringRef(const char* string): stringbuf_(string != nullptr ? string : EmptyString){};

    constexpr StringRef(const StringRef& other): stringbuf_(other.stringbuf_){};

#if USE_JUCE_STRING 
    StringRef(const juce::String& str): stringbuf_(str.toRawUTF8()){};
#endif

#if USE_STD_STRING 
    StringRef(const std::string& str) : stringbuf_(str.c_str()) {};
#endif

    size_t length() const {
      return strlen(stringbuf_);
    }

    char charAt(size_t loc) const {
      if (loc >= length()) return '\0';
      else return stringbuf_[loc];
    }

    int compareWith(const StringRef other) const {
      return compare(*this, other);
    }

    int compareWith(const StringRef other, size_t noChars) const {
      return compare(*this, other, noChars);
    }

    bool equalsIgnoreCase(StringRef s) const;

    bool startsWith(StringRef prefix) const {
      if (length() < prefix.length()) return 0;
      return startsWith(prefix, 0);
    }

    bool startsWith(StringRef prefix, size_t offset) const;

    bool endsWith(StringRef suffix) const;

    int indexOf(char ch) const {
      return indexOf(ch, 0);
    }

    int indexOf(char ch, size_t fromIndex) const;

    int indexOf(StringRef str) const {
      return indexOf(str, 0);
    }

    int indexOf(StringRef str, size_t fromIndex) const;

    StringRef end() const {
      return StringRef((stringbuf_ +  length()));
    }

    StringRef begin() const {
      return *this;
    }

    static int compare(StringRef lhs, StringRef rhs) {
      return strcmp(lhs.stringbuf_, rhs.stringbuf_);
    }

    static int compare(StringRef lhs, StringRef rhs, size_t noChars) {
      return strncmp(lhs.stringbuf_, rhs.stringbuf_, noChars);
    }

    char operator[](size_t index) const {
      return charAt(index);
    }

    StringRef& operator=(StringRef other) {
      stringbuf_ = other.stringbuf_;
      return *this;
    }

    StringRef& operator=(const char* str) {
      stringbuf_ = str != nullptr ? str : EmptyString;
      return *this;
    }

    operator const char* () const {
      return stringbuf_;
    }

    friend bool operator==(StringRef lhs, StringRef rhs) {
      return compare(lhs, rhs) == 0;
    }

    friend bool operator!=(StringRef lhs, StringRef rhs) {
      return compare(lhs, rhs) != 0;
    }

    friend bool operator>(StringRef lhs, StringRef rhs) {
      return compare(lhs, rhs) > 0;
    }

    friend bool operator<(StringRef lhs, StringRef rhs) {
      return compare(lhs, rhs) < 0;
    }

    friend bool operator>=(StringRef lhs, StringRef rhs) {
      return compare(lhs, rhs) >= 0;
    }

    friend bool operator<=(StringRef lhs, StringRef rhs) {
      return compare(lhs, rhs) <= 0;
    }
  protected:
    static constexpr const char* EmptyString = "";
    const char* stringbuf_;


};
