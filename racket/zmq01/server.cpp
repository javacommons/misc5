#include "zmqipc.hpp"
#include <QtCore>
#include <iostream>

#include "strconv.h"
#include "strutil.h"

using namespace std;

extern "C" void __wgetmainargs(int*, wchar_t***, wchar_t***, int, int*);
bool find_endpont_from_args(std::string &endpoint)
{
    endpoint = "";
    int argc, si = 0;
    wchar_t **argv, **env;
    __wgetmainargs(&argc, &argv, &env, 0, &si);
    if(argc < 2) return false;
    std::wstring arg1 = argv[1];
    if(!starts_with(arg1, L"tcp://")) return false;
    endpoint = wide_to_utf8(arg1);
    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string endpoint;
    if(!find_endpont_from_args(endpoint)) return 1;

    ZmqContext ipc;
    //bool b = ipc.open_server("tcp://127.0.0.1:50862");
    bool b = ipc.open_server(endpoint);
    if(!b) return 1;
    ipc.send_msg("#begin");
    while (true)
    {
        std::string msg = ipc.recv_msg();
        cout << "msg=" << utf8_to_ansi(msg) << endl;
        if(msg == "#end")
        {
            cout << "#end found" << endl;
            return 0;
        }
        ipc.send_msg("[" + msg + "]");
    }
    return 0;
}
