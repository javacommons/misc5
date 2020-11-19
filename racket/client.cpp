#include "pipe.hpp"
#include "vardecl.h"
#include "strconv.h"

#include <windows.h>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "base64.hpp"
#include "msgpack11.hpp"
using namespace msgpack11;

int main(int argc, char *argv[])
{
    const char *name = argv[1];

    char szData[] = "sample-data";

    HANDLE hPipe = create_pipe_crient(name);
    if (hPipe == INVALID_HANDLE_VALUE)
    {
        MessageBoxW(NULL, L"パイプへの接続に失敗しました。",
                    NULL, MB_ICONWARNING);
        return 0;
    }

    //write_string_to_pipe(hPipe, szData);
    std::string read = read_string_from_pipe(hPipe);
    std::string packed = base64_decode(read);
    json json1 = json::from_msgpack(packed);
    //std::cout << "[API]" << api_name << " args=" << json1.dump() << std::endl;

    MessageBoxW(NULL, utf8_to_wide(json1.dump(4)).c_str(), L"クライアント", MB_OK);

    std::string ts;
    std::vector<uint8_t> bin;

    MsgPack obj = MsgPack::object{
        {"sum", 12.34},
        {"diff", 45.67},
        {"ts", ts},
        {"bin", bin},
    };
    std::string output = obj.dump();
    std::string base64_result = base64_encode(output);
    write_string_to_pipe(hPipe, base64_result);

    CloseHandle(hPipe);

    return 0;
}
