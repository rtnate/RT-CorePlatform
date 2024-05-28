#include "FixedString.h"
#include <stdarg.h>
#include <cstring>
#include <ctype.h>

size_t FixedString::write(const uint8_t* buffer, size_t size) {
  size_t cap = remainingCapacity();
  size_t toCopy = cap > size ? size : cap;
  size_t didCopy = toCopy;
  int index = index_;
  while (toCopy--) {
    char c = (char)(*buffer++);
    buffer_[index++] = c;
  }
  setIndex(index);
  return didCopy;
}


size_t FixedString::printf(size_t noChars, const char* format, ...) {
  va_list args;
  va_start(args, format);
  size_t room = remainingCapacity();
  if (room == 0) return 0;
  size_t toCopy = room > noChars ? noChars : room;
  char* buffer = getCurrentPtr();
  vsnprintf(buffer, toCopy + 1, format, args);
  va_end(args);
  return strlen(buffer);
}

size_t FixedString::printf(const char* format, ...) {
  va_list args;
  va_start(args, format);
  size_t room = remainingCapacity();
  if (room == 0) return 0;
  char* buffer = getCurrentPtr();
  vsnprintf(buffer, room + 1, format, args);
  va_end(args);
  return strlen(buffer);
}

int FixedString::append(StringRef other) {
  int room = remainingCapacity();
  int size = other.length();
  int toCopy = room > size ? size : room;
  int didCopy = toCopy;
  int index = index_;
  while (toCopy--) {
    buffer_[index++] = other[index];
  }
  setIndex(index);
  return didCopy;
}

int FixedString::append(int num, int radix) {
  return print(num, radix);
}

int FixedString::append(StringRef other, size_t sizeToAppend) {
  int room = remainingCapacity();
  int size = other.length() > sizeToAppend ? other.length() : sizeToAppend;
  int toCopy = room > size ? size : room;
  int didCopy = toCopy;
  int index = index_;
  while (toCopy--) {
    buffer_[index++] = other[index];
  }
  setIndex(index);
  return didCopy;
}

void FixedString::truncate(size_t newLength) {
  if (newLength < length()) {
    setIndex(newLength);
  }
}

void FixedString::softTruncate(size_t newLength, size_t ellipsesLength) {
  if (newLength < length()) {
    int ellip = ellipsesLength > newLength ? newLength : ellipsesLength;
    int i = newLength - ellip;
    setIndex(i);
    while (ellip--) {
      putC('.');
    }
  }
}