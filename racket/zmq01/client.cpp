#include "zmqipc.hpp"
#include <QtCore>
#include <iostream>

#include "strconv.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ZmqIPC ipc;
    std::string endpoint = ipc.open_client();
    cout << "endpoint=" << endpoint << endl;
    std::string bgn = ipc.recv_msg();
    if(bgn != "#begin")
    {
        cerr << "#begin not found" << endl;
        return 1;
    }
    for(int i=0; i<3; i++) {
        ipc.send_msg("testテスト");
        std::string res = ipc.recv_msg();
        cout << utf8_to_ansi(res) << endl;
    }
    ipc.send_msg("#end");
    return 0;
}
