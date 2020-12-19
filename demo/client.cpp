#include "zmqipc.hpp"
#include "strconv.h"
#include "vardecl.h"

#include "json-ipc.h"

int main(int argc, char *argv[])
{
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);

#if 0x1
    bool debug = false;
#else
    bool debug = true;
#endif

    json_ipc *ipc = ipc_open_client(U8(R"("./server.exe")"), debug);

    json j = {
        {"abc", format(U8("testテスト%d"), 123)}
    };
    j["xyz"] = 123;
    json j2 = ipc_call_json_api(ipc, "dummy_api", j);
    formatA(std::cout, U8("return=%s\n"), j2.dump().c_str());

    json j3 = true;
    json j4 = ipc_call_json_api(ipc, "no_api", j3);
    formatA(std::cout, U8("return2=%s\n"), j4.dump().c_str());

    return 0;
}
