#include "zmqipc.hpp"
#include <QtCore>
#include <cstdlib>
#include <iostream>

using namespace std;

void on_exit()
{
    std::cout << "on exit" << std::endl;
    ::MessageBoxW(NULL, L"on_exit()", L"server.exe", MB_OK);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "server(1)" << endl;

    cout << "server(2)" << endl;

    std::string endpoint;
    bool debug;
    if(!find_endpont_from_args(endpoint, &debug)) return 1;
    if(debug) std::atexit(on_exit);

    cout << "server(3)" << debug << endl;

    ZmqIPC ipc;
    if(!ipc.open_server(endpoint)) return 1;

    cout << "server(4)" << endl;

    while(true)
    {
        json req = ipc.recv_json();
        cout << "request=" << utf8_to_ansi(req.dump()) << endl;
        if(req == "#end")
        {
            cout << "#end found" << endl;
            return 0;
        }
        req["return"] = 567.89;
        ipc.send_json(req);
    }
    return 0;
}
