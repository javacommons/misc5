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
#if 0x0
    bool debug = false;
#else
    bool debug = true;
#endif
    bool b = ipc.open_client(u8R"(C:\Users\javac\misc5\racket\build-server-Desktop_Qt_MinGW_w64_32bit_MSYS2-Debug\debug\server.exe)",
                             debug);
    if(!b) return 1;
    json bgn = ipc.recv_json();
    if(bgn != "#begin")
    {
        cerr << "#begin not found" << endl;
        return 1;
    }
    for(int i=0; i<3; i++) {
        std::vector<std::string> vec;
        json j = {
            {"abc", format("testテスト%d", i+1)}
        };
        j["xyz"] = 123;
        ipc.send_json(j);
        json j2 = ipc.recv_json();
        cout << "return=" << utf8_to_ansi(j2.dump()) << endl;
    }
    //ipc.send_json("#end");
    return 0;
}
