#include "../pipe.hpp"
#include "../vardecl.h"

#include <windows.h>

int main(int argc, char *argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    DWORD buffer_size = 4096;
    HANDLE hPipe = create_pipe_server("2020-11-16T05:13:01.444776611", buffer_size);
    if (hPipe == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"パイプの作成に失敗しました。", NULL, MB_ICONWARNING);
        return 0;
    }
    ConnectNamedPipe(hPipe, NULL);

    std::string read = read_string_from_pipe(hPipe);
    write_string_to_pipe(hPipe, read);

    MessageBoxW(NULL, L"終了します。", L"サーバー", MB_OK);

    CloseHandle(hPipe);

    return 0;
}
