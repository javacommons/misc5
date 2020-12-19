#include "json-ipc.h"
//#include "zmqipc.hpp"
#include <cstdlib>
//#include <iostream>
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

typedef json (*json_api)(const json &input);
std::map<std::string, json_api> json_api_map;
void register_json_api(const std::string &name, json_api func)
{
    json_api_map[name] = func;
}
json_api retrieve_json_api(const std::string &name)
{
    if (json_api_map.count(name) == 0)
        return nullptr;
    return json_api_map[name];
}
#define REGISTER_JSON_API(X) (register_json_api(#X, X))

static const char *handler(const char *api, const char *input)
{
    std::string api_ = api;
    std::string input_ = input;
    json_api func = retrieve_json_api(api);
    if(!func) return nullptr;
    json output = func(json::parse(input));
    formatA(std::cout, "handler: output=%s\n", output.dump().c_str());
    return output.dump().c_str();
}


int main(int argc, char *argv[])
{
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);

    formatA(std::cout, "server(1)\n");

#if 0x0
    std::string endpoint;
    bool debug;
    if (!find_endpont_from_args(endpoint, &debug))
        return 1;
#else
    int debug;
    const char *endpoint = ipc_find_endpont_from_args(&debug);
    if(!endpoint) return 1;
#endif
    if (debug)
        std::atexit(on_exit);

    formatA(std::cout, "server(2)\n");

#if 0x0
    ZmqIPC ipc;
    REGISTER_JSON_API(ipc, dummy_api);
    if (!ipc.open_server(endpoint))
        return 1;
#else
    REGISTER_JSON_API(dummy_api);
    json_ipc *ipc = ipc_open_server(endpoint, handler);
#endif

    formatA(std::cout, "server(3)\n");

    return 0;
}
