#include "StringRef.h"
#include <ctype.h>

bool StringRef::equalsIgnoreCase(StringRef s) const {
	if (stringbuf_ == s.stringbuf_) return true;
	if (length() != s.length()) return 0;
	if (length() == 0) return true;
	const char* p1 = stringbuf_;
	const char* p2 = s.stringbuf_;
	while (*p1) {
		if (tolower(*p1++) != tolower(*p2++)) return false;
	}
	return true;
}

bool StringRef::startsWith(StringRef prefix, size_t offset) const {
	auto len = length(); auto prefix_len = prefix.length();
	if (offset > len) return 0;
	if (offset > (len - prefix_len)) return 0;
	return strncmp(&stringbuf_[offset], prefix.stringbuf_, prefix_len) == 0;
}

bool StringRef::endsWith(StringRef suffix) const {
	auto len = length(); auto suffix_len = suffix.length();
	if (len < suffix_len) return 0;
	return strcmp(&stringbuf_[len - suffix_len], suffix.stringbuf_) == 0;
}

int StringRef::indexOf(char ch, size_t fromIndex) const {
	if (fromIndex >= length()) return -1;
	const char* found = strchr(stringbuf_ + fromIndex, ch);
	if (found) {
		int index = found - stringbuf_;
		return index;
	}
	return -1;
}

int StringRef::indexOf(StringRef str, size_t fromIndex) const {
	if (fromIndex >= length()) return -1;
	const char* found = strstr(stringbuf_ + fromIndex, str);
	if (found) {
		int index = found - stringbuf_;
		return index;
	}
	return -1;
}
