#include "libarchive.h"
#include "json-ipc.h"
#include <cstdlib>
#include "strconv.h"
#include "vardecl.h"

//using namespace std;

void on_exit()
{
    formatA(std::cout, "on_exit\n");
    ::MessageBoxW(NULL, L"on_exit()", L"server.exe", MB_OK);
}

json dummy_api(const json &input)
{
    json output = input;
    output["out"] = 123.45;
    return output;
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
    //ormatA(std::cout, "api=%s input=%s\n", api, input);
    std::string api_ = api;
    std::string input_ = input;
    json_api func = retrieve_json_api(api);
    if(!func) return nullptr;
    json output = func(json::parse(input));
    //ormatA(std::cout, "handler: api=%s output=%s\n", api, output.dump().c_str());
    TLS_VARIABLE static std::string ret;
    ret = output.dump();
    return ret.c_str();
}

int main(int argc, char *argv[])
{
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);

    //ormatA(std::cout, "server(1)\n");

    int debug;
    const char *endpoint = ipc_find_endpont_from_args(&debug);
    if(!endpoint) return 1;

    if (debug)
        std::atexit(on_exit);

    //ormatA(std::cout, "server(2)\n");

    REGISTER_JSON_API(dummy_api);
    REGISTER_JSON_API(api_open_archive);
    REGISTER_JSON_API(api_close_archive);
    REGISTER_JSON_API(api_archive_get_params);
    REGISTER_JSON_API(api_archive_next_entry);
    REGISTER_JSON_API(api_archive_entry_write);
    json_ipc *ipc = ipc_open_server(endpoint, handler);

    //ormatA(std::cout, "server(3)\n");

    return 0;
}
