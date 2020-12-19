#include "zmqipc.hpp"
#include <cstdlib>
#include <iostream>
#include "strconv.h"
#include "vardecl.h"

using namespace std;

json dummy_api(const json &input)
{
    json output = input;
    output["out"] = 123.45;
    return output;
}

void on_exit()
{
    formatA(std::cout, "on_exit\n");
    ::MessageBoxW(NULL, L"on_exit()", L"server.exe", MB_OK);
}

int main(int argc, char *argv[])
{
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);

    formatA(std::cout, "server(1)\n");

    std::string endpoint;
    bool debug;
    if (!find_endpont_from_args(endpoint, &debug))
        return 1;
    if (debug)
        std::atexit(on_exit);

    formatA(std::cout, "server(2)\n");

    ZmqIPC ipc;
    REGISTER_JSON_API(ipc, dummy_api);
    if (!ipc.open_server(endpoint))
        return 1;

    formatA(std::cout, "server(3)\n");

    return 0;
}
