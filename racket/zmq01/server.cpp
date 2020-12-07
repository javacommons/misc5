#include "zmqipc.hpp"
#include <QtCore>
#include <iostream>

//#include "strconv.h"
#include "strutil.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string endpoint;
    if(!find_endpont_from_args(endpoint)) return 1;

    ZmqIPC ipc;
    //bool b = ipc.open_server("tcp://127.0.0.1:50862");
    bool b = ipc.open_server(endpoint);
    if(!b) return 1;
    //ipc.send_msg("#begin");
    ipc.send_json("#begin");
    while (true)
    {
        json msg = ipc.recv_json();
        cout << "msg=" << utf8_to_ansi(msg.dump()) << endl;
        if(msg == "#end")
        {
            cout << "#end found" << endl;
            return 0;
        }
        //ipc.send_msg("[" + msg + "]");
        msg["return"] = 567.89;
        ipc.send_json(msg);
    }
    return 0;
}
