#include "zmqipc.hpp"
#include <QtCore>
#include <iostream>

#include "strconv.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ZmqIPC ipc;
    bool b = ipc.open_server("tcp://127.0.0.1:50862");
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
