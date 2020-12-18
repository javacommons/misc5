#ifndef STRCONVFMT_H
#define STRCONVFMT_H

#include "strconv.h"

// https://github.com/fmtlib/fmt (A modern formatting library)
#define FMT_HEADER_ONLY
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
static inline void output(std::ostream& ostrm, const std::wstring &format_str, Args &&... args)
{
  ostrm << fmt::format(format_str, args...) << std::flush;
}
template <typename... Args>
static inline void output(std::ostream& ostrm, const std::string &format_str, Args &&... args)
{
  ostrm << fmt::format(format_str, args...) << std::flush;
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

template <typename... Args>
static inline void outputA(std::ostream& ostrm, const std::wstring &format_str, Args &&... args)
{
  ostrm << wide_to_ansi(fmt::format(format_str, args...)) << std::flush;
}
template <typename... Args>
static inline void outputA(std::ostream& ostrm, const std::string &format_str, Args &&... args)
{
  ostrm << utf8_to_ansi(fmt::format(format_str, args...)) << std::flush;
}

#endif /* STRCONVFMT_H */
