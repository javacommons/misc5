/* strconv.h v1.3.0                */
/* Last Modified: 2020/12/18 11:21 */
#ifndef STRCONV_H
#define STRCONV_H

#include <windows.h>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
static inline std::wstring cp_to_wide(const std::string &s, UINT codepage)
{
  int in_length = (int)s.length();
  int out_length = MultiByteToWideChar(codepage, 0, s.c_str(), in_length, 0, 0);
  std::wstring result(out_length, L'\0');
  if (out_length)
    MultiByteToWideChar(codepage, 0, s.c_str(), in_length, &result[0], out_length);
  return result;
}
static inline std::string wide_to_cp(const std::wstring &s, UINT codepage)
{
  int in_length = (int)s.length();
  int out_length = WideCharToMultiByte(codepage, 0, s.c_str(), in_length, 0, 0, 0, 0);
  std::string result(out_length, '\0');
  if (out_length)
    WideCharToMultiByte(codepage, 0, s.c_str(), in_length, &result[0], out_length, 0, 0);
  return result;
}
#else /* __cplusplus < 201103L */
static inline std::wstring cp_to_wide(const std::string &s, UINT codepage)
{
  int in_length = (int)s.length();
  int out_length = MultiByteToWideChar(codepage, 0, s.c_str(), in_length, 0, 0);
  std::vector<wchar_t> buffer(out_length);
  if (out_length)
    MultiByteToWideChar(codepage, 0, s.c_str(), in_length, &buffer[0], out_length);
  std::wstring result(buffer.begin(), buffer.end());
  return result;
}
static inline std::string wide_to_cp(const std::wstring &s, UINT codepage)
{
  int in_length = (int)s.length();
  int out_length = WideCharToMultiByte(codepage, 0, s.c_str(), in_length, 0, 0, 0, 0);
  std::vector<char> buffer(out_length);
  if (out_length)
    WideCharToMultiByte(codepage, 0, s.c_str(), in_length, &buffer[0], out_length, 0, 0);
  std::string result(buffer.begin(), buffer.end());
  return result;
}
#endif

static inline std::string cp_to_utf8(const std::string &s, UINT codepage)
{
  if (codepage == CP_UTF8)
    return s;
  std::wstring wide = cp_to_wide(s, codepage);
  return wide_to_cp(wide, CP_UTF8);
}
static inline std::string utf8_to_cp(const std::string &s, UINT codepage)
{
  if (codepage == CP_UTF8)
    return s;
  std::wstring wide = cp_to_wide(s, CP_UTF8);
  return wide_to_cp(wide, codepage);
}

static inline std::wstring ansi_to_wide(const std::string &s)
{
  return cp_to_wide(s, CP_ACP);
}
static inline std::string wide_to_ansi(const std::wstring &s)
{
  return wide_to_cp(s, CP_ACP);
}

static inline std::wstring sjis_to_wide(const std::string &s)
{
  return cp_to_wide(s, 932);
}
static inline std::string wide_to_sjis(const std::wstring &s)
{
  return wide_to_cp(s, 932);
}

static inline std::wstring utf8_to_wide(const std::string &s)
{
  return cp_to_wide(s, CP_UTF8);
}
static inline std::string wide_to_utf8(const std::wstring &s)
{
  return wide_to_cp(s, CP_UTF8);
}

static inline std::string ansi_to_utf8(const std::string &s)
{
  return cp_to_utf8(s, CP_ACP);
}
static inline std::string utf8_to_ansi(const std::string &s)
{
  return utf8_to_cp(s, CP_ACP);
}

static inline std::string sjis_to_utf8(const std::string &s)
{
  return cp_to_utf8(s, 932);
}
static inline std::string utf8_to_sjis(const std::string &s)
{
  return utf8_to_cp(s, 932);
}

#pragma warning(push)
#pragma warning(disable : 4996)
static inline std::wstring format(const wchar_t *format, ...)
{
  va_list args;
  va_start(args, format);
  int len = _vsnwprintf(nullptr, 0, format, args);
  std::vector<wchar_t> buffer(len + 1);
  _vsnwprintf(&buffer[0], len + 1, format, args);
  va_end(args);
  return &buffer[0];
}
static inline std::string format(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  int len = _vsnprintf(nullptr, 0, format, args);
  std::vector<char> buffer(len + 1);
  _vsnprintf(&buffer[0], len + 1, format, args);
  va_end(args);
  return &buffer[0];
}

static inline std::string formatA(const wchar_t *format, ...)
{
  va_list args;
  va_start(args, format);
  int len = _vsnwprintf(nullptr, 0, format, args);
  std::vector<wchar_t> buffer(len + 1);
  _vsnwprintf(&buffer[0], len + 1, format, args);
  va_end(args);
  return wide_to_ansi(&buffer[0]);
}
static inline std::string formatA(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  int len = _vsnprintf(nullptr, 0, format, args);
  std::vector<char> buffer(len + 1);
  _vsnprintf(&buffer[0], len + 1, format, args);
  va_end(args);
  return utf8_to_ansi(&buffer[0]);
}
#pragma warning(pop)

#define U8(X) ((const char *)u8##X)
#define WIDE(X) L##X

#ifdef STRCONV_FMTLIB
#include <fmt/args.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/format-inl.h>
#include <fmt/locale.h>
#include <fmt/os.h>
#include <fmt/ostream.h>
#include <fmt/printf.h>
#include <fmt/ranges.h>
template <typename... Args>
static inline std::wstring output(const std::wstring &format_str, Args &&... args)
{
  return fmt::format(format_str, args...);
}
template <typename... Args>
static inline std::string output(const std::string &format_str, Args &&... args)
{
  return fmt::format(format_str, args...);
}

template <typename... Args>
static inline std::string outputA(const std::wstring &format_str, Args &&... args)
{
  return wide_to_ansi(fmt::format(format_str, args...));
}
template <typename... Args>
static inline std::string outputA(const std::string &format_str, Args &&... args)
{
  return utf8_to_ansi(fmt::format(format_str, args...));
}
#endif /* STRCONV_FMTLIB */

#endif /* STRCONV_H */
