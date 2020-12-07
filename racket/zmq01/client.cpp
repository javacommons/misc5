#include "zmqipc.hpp"
#include <QtCore>
#include <iostream>

#include "strconv.h"
#include "strutil.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ZmqIPC ipc;
    bool b = ipc.open_client(u8R"(C:\Users\javac\misc5\racket\build-server-Desktop_Qt_MinGW_w64_32bit_MSYS2-Debug\debug\server.exe)",
                             true);
    if(!b) return 1;
    std::string bgn = ipc.recv_msg();
    if(bgn != "#begin")
    {
        cerr << "#begin not found" << endl;
        return 1;
    }
    for(int i=0; i<3; i++) {
        ipc.send_msg(format("testテスト%d", i+1));
        std::string res = ipc.recv_msg();
        cout << utf8_to_ansi(res) << endl;
    }
    ipc.send_msg("#end");
    return 0;
}
