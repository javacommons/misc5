#include "json-ipc.h"
#include "zmqipc.hpp"
#include "strconv.h"
#include "vardecl.h"

extern "C" __declspec(dllexport) int add2(int x, int y)
{
    return x + y;
}

extern "C" __declspec(dllexport)
json_ipc *ipc_open_client(const char *server, int debug)
{
    ZmqIPC *zipc = new ZmqIPC();
    if(!zipc->open_client(server, !!debug))
    {
        delete zipc;
        return nullptr;
    }
    return (json_ipc *)zipc;
    return 0;
}

extern "C" __declspec(dllexport)
const char *ipc_call_api(json_ipc *ipc, const char *api, const char *input)
{
    ZmqIPC *zipc = (ZmqIPC *)ipc;
    TLS_VARIABLE std::string result;
    result = zipc->call_api(api, input);
    return result.c_str();
}
