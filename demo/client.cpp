#include "json-ipc.h"
//#include "zmqipc.hpp"
#include "strconv.h"
#include "vardecl.h"

#include <regex>

int main(int argc, char *argv[])
{
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);

#if 0x0
    bool debug = false;
#else
    bool debug = true;
#endif

    json_ipc *ipc = ipc_open_client(U8(R"("./server.exe")"), debug);

#if 0x0
    json j = {
        {"abc", format(U8("testテスト%d"), 123)}
    };
    j["xyz"] = 123;
    json j2 = ipc_call_json_api(ipc, "dummy_api", j);
    formatA(std::cout, U8("return=%s\n"), j2.dump().c_str());

    json j3 = true;
    json j4 = ipc_call_json_api(ipc, "no_api", j3);
    formatA(std::cout, U8("return2=%s\n"), j4.dump().c_str());
#endif

    std::string msys2TarXz = U8(R"(C:\Users\Public\root\Dropbox\_data_\msys2-base-x86_64-20200903.tar.xz)");
    json archive = ipc_call_json_api(ipc, "api_open_archive",
                                     json{
                                         {"path", msys2TarXz},
                                         {"target", "D:/temp/"}});
    formatA(std::cout, "archive=%s\n", archive.dump().c_str());
    if(archive==false) return 1;
    for(;;) {
        json entry = ipc_call_json_api(ipc, "api_archive_next_entry", archive);
        //formatA(std::cout, "entry=%s\n", entry.dump().c_str());
        if(false==entry) {
            break;
        }
        auto pathname = entry["pathname"].get<std::string>();
        //formatA(std::cout, "pathname=%s\n", pathname.c_str());
        auto realname = std::regex_replace(pathname, std::regex("^[^/]+/(.*)$"), "$1");
        //ormatA(std::cout, "(A)\n");
        entry["pathname"] = realname;
        //ormatA(std::cout, "(B)\n");
#if 0x0
        auto written = ipc_call_json_api(ipc, "api_archive_entry_write", entry);
        if(written==false) break;
        bool isDir = entry["isDir"];
        std::string indicator = isDir?"[D] ":"[F] ";
        std::cout << indicator << written["writePath"] << std::endl;
#endif
    }
    //json params = api_archive_get_params(archive);
    json params = ipc_call_json_api(ipc, "api_archive_get_params", archive);
    //cout << params << endl;
    ipc_call_json_api(ipc, "api_close_archive", archive);

    return 0;
}
