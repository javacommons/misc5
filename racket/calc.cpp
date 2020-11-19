#include "calc.hpp"

//#include <nlohmann/json.hpp>
//using json = nlohmann::json;

#include <string>
#include <iostream>

#include "pipe.hpp"
#include "strconv.h"
#include "vardecl.h"

const char *open_pipe_server(const char *prefix,
                             const char *client,
                             int show_client)
{
  FILETIME file_time;
  GetSystemTimeAsFileTime(&file_time);
  ULONGLONG ull = (ULONGLONG)file_time.dwHighDateTime << 32 | file_time.dwLowDateTime;
  std::string name = prefix;
  name += ":";
  name += std::to_string(ull);
  HANDLE hPipe = create_pipe_server(name, 4096);
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
      show_client ? 0 : CREATE_NO_WINDOW,
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
  std::string addr = address_to_string(hPipe);
  return strdup(addr.c_str());
}

const char *open_pipe_client(const char *name)
{
  HANDLE hPipe = create_pipe_client(name);
  std::string addr = address_to_string(hPipe);
  return strdup(addr.c_str());
}

const char *read_from_pipe(const char *hPipe)
{
  static TLS_VARIABLE_DECL std::string read;
  read = read_string_from_pipe(string_to_address(hPipe));
  return read.c_str();
}

void write_to_pipe(const char *hPipe, const char *s)
{
  write_string_to_pipe(string_to_address(hPipe), s);
}
