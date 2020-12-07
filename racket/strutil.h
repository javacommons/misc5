#ifndef STRUTIL_H
#define STRUTIL_H

#include <string>

inline bool starts_with(const std::string& s, const std::string& prefix) // https://marycore.jp/prog/cpp/starts-with-prefix-search/
{
   auto size = prefix.size();
   if (s.size() < size) return false;
   return std::equal(std::begin(prefix), std::end(prefix), std::begin(s));
}

inline bool starts_with(const std::wstring& s, const std::wstring& prefix)
{
   auto size = prefix.size();
   if (s.size() < size) return false;
   return std::equal(std::begin(prefix), std::end(prefix), std::begin(s));
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

inline bool ends_with(std::wstring const & value, std::wstring const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::string replace_all(std::string &replacedStr, std::string from, std::string to) // https://www.sejuku.net/blog/54493
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
std::wstring replace_all(std::wstring &replacedStr, std::wstring from, std::wstring to) // https://www.sejuku.net/blog/54493
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

#endif //STRUTIL_H
