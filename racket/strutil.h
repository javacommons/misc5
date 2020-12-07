#ifndef STRUTIL_H
#define STRUTIL_H

#include <string>
#include <vector>
#include <stdarg.h>
#include <stdio.h>

static inline bool starts_with(const std::string& s, const std::string& prefix) // https://marycore.jp/prog/cpp/starts-with-prefix-search/
{
   auto size = prefix.size();
   if (s.size() < size) return false;
   return std::equal(std::begin(prefix), std::end(prefix), std::begin(s));
}
static inline bool starts_with(const std::wstring& s, const std::wstring& prefix) // https://marycore.jp/prog/cpp/starts-with-prefix-search/
{
   auto size = prefix.size();
   if (s.size() < size) return false;
   return std::equal(std::begin(prefix), std::end(prefix), std::begin(s));
}

static inline bool ends_with(std::string const & value, std::string const & ending) // https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
static inline bool ends_with(std::wstring const & value, std::wstring const & ending) // https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

static inline std::string replace_all(std::string &replacedStr, std::string from, std::string to) // https://www.sejuku.net/blog/54493
{
    unsigned int pos = replacedStr.find(from);
    int toLen = to.length();
    if (from.empty()) {
        return replacedStr;
    }
    while ((pos = replacedStr.find(from, pos)) != std::string::npos) {
        replacedStr.replace(pos, from.length(), to);
        pos += toLen;
    }
    return replacedStr;
}
static inline std::wstring replace_all(std::wstring &replacedStr, std::wstring from, std::wstring to) // https://www.sejuku.net/blog/54493
{
    unsigned int pos = replacedStr.find(from);
    int toLen = to.length();
    if (from.empty()) {
        return replacedStr;
    }
    while ((pos = replacedStr.find(from, pos)) != std::string::npos) {
        replacedStr.replace(pos, from.length(), to);
        pos += toLen;
    }
    return replacedStr;
}

static inline std::wstring format(const wchar_t *format, ...) // JavaCommons
{
    va_list args;
    va_start(args, format);
    int len = _vsnwprintf(nullptr, 0, format, args);
    std::vector<wchar_t> buffer(len + 1);
    _vsnwprintf(&buffer[0], len + 1, format, args);
    va_end(args);
    return &buffer[0];
}
static inline std::string format(const char *format, ...) // JavaCommons
{
    va_list args;
    va_start(args, format);
    int len = _vsnprintf(nullptr, 0, format, args);
    std::vector<char> buffer(len + 1);
    _vsnprintf(&buffer[0], len + 1, format, args);
    va_end(args);
    return &buffer[0];
}

#endif //STRUTIL_H