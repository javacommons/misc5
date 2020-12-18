#include "zmqipc.hpp"
//#include <QtCore>
#include <cstdlib>
#include <iostream>

using namespace std;

json dummy_api(const json &input)
{
    json output = input;
    output["out"] = 123.45;
    return output;
}

void on_exit()
{
    std::cout << "on exit" << std::endl;
    ::MessageBoxW(NULL, L"on_exit()", L"server.exe", MB_OK);
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    cout << "server(1)" << endl;

    cout << "server(2)" << endl;

    std::string endpoint;
    bool debug;
    if (!find_endpont_from_args(endpoint, &debug))
        return 1;
    if (debug)
        std::atexit(on_exit);

    cout << "server(3)" << debug << endl;

    ZmqIPC ipc;
    REGISTER_JSON_API(ipc, dummy_api);
    if (!ipc.open_server(endpoint))
        return 1;

    cout << "server(4)" << endl;

#if 0x0
    while (true)
    {
        ipc.handle_json_api();
    }
#endif
    return 0;
}
