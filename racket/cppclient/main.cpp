#include "../pipe.hpp"
#include "../vardecl.h"
#include "../strconv.h"

#include <windows.h>
#include <string>

int main(int argc, char *argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    char   szData[] = "sample-data";

    HANDLE hPipe = create_pipe_crient("2020-11-16T05:13:01.444776611");
    if (hPipe == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"パイプへの接続に失敗しました。",
                    NULL, MB_ICONWARNING);
        return 0;
    }

    write_string_to_pipe(hPipe, szData);
    std::string read = read_string_from_pipe(hPipe);

    MessageBoxW(NULL, utf8_to_wide(read).c_str(), L"クライアント", MB_OK);

    CloseHandle(hPipe);

    return 0;
}
