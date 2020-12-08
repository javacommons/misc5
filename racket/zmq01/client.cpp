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
    bool b = ipc.open_client(u8R"("C:\Users\javac\misc5\racket\build-server-Desktop_Qt_MinGW_w64_32bit_MSYS2-Debug\debug\server.exe")",
                             debug);
    if(!b) return 1;
    for(int i=0; i<3; i++) {
        std::vector<std::string> vec;
        json j = {
            {"abc", format("testテスト%d", i+1)}
        };
        j["xyz"] = 123;
        json j2 = ipc.call_json_api("dummy_api", j);
        cout << "return=" << utf8_to_ansi(j2.dump()) << endl;
    }
    return 0;
}
