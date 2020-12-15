#define FMT_HEADER_ONLY
#include <fmt/chrono.h>
#include <iostream>
#include "strconv.h"

template <typename... Args>
static inline std::string formatA2(const std::string &format_str, Args &&... args)
{
  return utf8_to_ansi(fmt::format(format_str, args...));
}

template <typename... Args>
static inline std::string formatA2(const std::wstring &format_str, Args &&... args)
{
  return wide_to_ansi(fmt::format(format_str, args...));
}

int main()
{
  using namespace std::literals::chrono_literals;
  std::cout << formatA2(u8"Default format: {} {}", 42s, 100ms) << std::endl;
  std::cout << formatA2(u8"strftime-like format: {:%H:%M:%S}", 3h + 15min + 30s) << std::endl;
  std::wstring hello = L"ハロー";
  std::cout << formatA2(L"this is(これは) {}", hello) << std::endl;
  std::string goodby = u8"グッバイ";
  std::cout << formatA2(u8"that is(あれは) {}", goodby) << std::endl;
  return 0;
}