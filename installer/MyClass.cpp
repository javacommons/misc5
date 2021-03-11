#include "MyClass.hpp"
#include "strconv.h"

int globalNumber = 101;

int run_cmd(const char *cmd)
{
    std::wstring cmdline = utf8_to_wide(cmd);
    std::cout << wide_to_utf8(cmdline) << std::endl;
    PROCESS_INFORMATION pi = {0};
    STARTUPINFOW si = {0};
    WINBOOL b = CreateProcessW(
        NULL,
        (LPWSTR)cmdline.c_str(),
        NULL,
        NULL,
        FALSE,
        0, //debug ? 0 : CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi);
    if (!b)
    {
        std::cerr << "Could not start command: " << cmd << std::endl;
        exit(1);
    }

    HANDLE childProcess = pi.hProcess;

    // 不要なスレッドハンドルをクローズする
    if (!CloseHandle(pi.hThread))
    {
        std::cerr << "CloseHandle(hThread)" << cmd << std::endl;
        return -1;
    }

    // 子プロセスの終了待ち
    DWORD r = WaitForSingleObject(childProcess, INFINITE);
    // 子プロセスの終了コードを取得
    DWORD exitCode;
    if (!GetExitCodeProcess(childProcess, &exitCode))
    {
        return -1;
    }

    return exitCode;
}