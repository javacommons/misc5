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
    if(!ipc.open_server(endpoint)) return 1;
    ipc.send_json("#begin");
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
