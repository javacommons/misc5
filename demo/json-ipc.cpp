#include "json-ipc.h"
#include "zmqipc.hpp"

extern "C" __declspec(dllexport) int add2(int x, int y)
{
    return x + y;
}

extern "C" __declspec(dllexport)
    json_ipc *ipc_open_client(const char *server, int debug)
{
    ZmqIPC *ipc = new ZmqIPC();
    if(!ipc->open_client(server, !!debug))
    {
        delete ipc;
        return nullptr;
    }
    return (json_ipc *)ipc;
    return 0;
}
