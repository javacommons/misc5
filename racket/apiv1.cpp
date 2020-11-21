#include "apiv1.hpp"

#include <windows.h>
#include <string>
#include <iostream>
#include "strconv.h"
#include "vardecl.h"

static inline HANDLE win32_make_client_pipe(const std::string &name, DWORD buffer_size) {
    std::string pipe_name = std::string(R"(\\.\pipe\)") + name;
    HANDLE hPipe = CreateNamedPipeA(pipe_name.c_str(),
                                    PIPE_ACCESS_DUPLEX,
                                    PIPE_TYPE_BYTE,
                                    PIPE_UNLIMITED_INSTANCES,
                                    buffer_size,
                                    buffer_size,
                                    0,
                                    NULL);
    return hPipe;
}

static inline HANDLE win32_make_server_pipe(const std::string &name) {
    std::string pipe_name = std::string(R"(\\.\pipe\)") + name;
    HANDLE hPipe = CreateFileA(pipe_name.c_str(),
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               NULL,
                               OPEN_EXISTING,
                               0,
                               NULL);
    return hPipe;
}

static inline std::string win32_read_from_pipe(HANDLE hPipe) {
    char c;
    std::string read = "";
    while(true) {
        DWORD  dwResult;
        if(!ReadFile(hPipe, &c, sizeof(c), &dwResult, NULL)) break;
        if(c=='\0') break;
        read.push_back(c);
    }
    return read;
}

static inline void win32_wite_to_pipe(HANDLE hPipe, const std::string &s) {
    DWORD  dwResult;
    WriteFile(hPipe, s.c_str(), s.size()+1, &dwResult, NULL);
}

const void *make_client_pipe(const char *prefix,
                             const char *client,
                             int debug)
{
  FILETIME file_time;
  GetSystemTimeAsFileTime(&file_time);
  ULONGLONG ull = (ULONGLONG)file_time.dwHighDateTime << 32 | file_time.dwLowDateTime;
  std::string name = prefix;
  name += ":";
  name += std::to_string(ull);
  HANDLE hPipe = win32_make_client_pipe(name, 4096);
  if (hPipe == INVALID_HANDLE_VALUE)
  {
    MessageBoxW(NULL, L"サーバーパイプの作成に失敗しました。", NULL, MB_ICONWARNING);
    return "";
  }
  std::wstring cmdline = utf8_to_wide(client);
  cmdline += L" ";
  cmdline += utf8_to_wide(name);
  std::cout << wide_to_utf8(cmdline) << std::endl;
  PROCESS_INFORMATION ps = {0};
  STARTUPINFOW si = {0};
  WINBOOL b = CreateProcessW(
      NULL,
      (LPWSTR)cmdline.c_str(),
      NULL,
      NULL,
      FALSE,
      debug ? 0 : CREATE_NO_WINDOW,
      NULL,
      NULL,
      &si,
      &ps);
  if (!b)
  {
    std::cout << "Could not start client." << std::endl;
    exit(1);
  }
  ConnectNamedPipe(hPipe, NULL);
  return hPipe;
}

const void *make_server_pipe(const char *name)
{
  HANDLE hPipe = win32_make_server_pipe(name);
  return hPipe;
}

const char *read_from_pipe(const void *hPipe)
{
  static TLS_VARIABLE_DECL std::string read;
  read = win32_read_from_pipe((HANDLE)hPipe);
  return read.c_str();
}

void write_to_pipe(const void *hPipe, const char *s)
{
  win32_wite_to_pipe((HANDLE)hPipe, s);
}
