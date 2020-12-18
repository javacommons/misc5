#include "zmqipc.hpp"
//#include <QtCore>
#include <iostream>

#include "strconv.h"
#include "strutil.h"

using namespace std;

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    ZmqIPC ipc;
#if 0x0
    bool debug = false;
#else
    bool debug = true;
#endif
    bool b = ipc.open_client(U8(R"("./server.exe")"),
                             debug);
    if(!b) return 1;

    json j = {
        {"abc", format(U8("testテスト%d"), 123)}
    };
    j["xyz"] = 123;
    json j2 = ipc.call_json_api("dummy_api", j);
    //cout << "return=" << utf8_to_ansi(j2.dump()) << endl;
    formatA(cout, U8("return=%s\n"), j2.dump().c_str());

    json j3 = true;
    json j4 = ipc.call_json_api("no_api", j3);
    //cout << "return2=" << utf8_to_ansi(j4.dump()) << endl;
    formatA(cout, U8("return2=%s\n"), j4.dump().c_str());

    return 0;
}
