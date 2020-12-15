#define FMT_HEADER_ONLY
#include <fmt/chrono.h>
#include <iostream>
#include "strconv.h"

template <typename... Args>
static inline std::wstring formatX(const std::wstring& format_str, Args&&... args) {
  return fmt::format(format_str, args...);
}


int main() {
  using namespace std::literals::chrono_literals;
  fmt::print("Default format: {} {}\n", 42s, 100ms);
  fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
  std::wstring ws = formatX(L"this is(これは) abc {}", 123);
  std::cout << wide_to_ansi(ws) << std::endl;
}