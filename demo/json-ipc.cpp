#include "json-ipc.h"
#include "zmqipc.hpp"
#include "strconv.h"
#include "vardecl.h"

extern "C" __declspec(dllexport)
const char *ipc_find_endpont_from_args(int *debug)
{
    *debug = 0;
    TLS_VARIABLE std::string endpoint;
    bool d;
    bool b = find_endpont_from_args(endpoint, &d);
    if(!b) return nullptr;
    *debug = d;
    return endpoint.c_str();
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
}

extern "C" __declspec(dllexport)
const char *ipc_call_api(json_ipc *ipc, const char *api, const char *input)
{
    ZmqIPC *zipc = (ZmqIPC *)ipc;
    TLS_VARIABLE std::string result;
    result = zipc->call_api(api, input);
    return result.c_str();
}

extern "C" __declspec(dllexport)
json_ipc *ipc_open_server(const char *endpoint, ipc_handler handler)
{
    ZmqIPC *zipc = new ZmqIPC();
    if(!zipc->open_server(endpoint, handler))
    {
        delete zipc;
        return nullptr;
    }
    return (json_ipc *)zipc;
}
