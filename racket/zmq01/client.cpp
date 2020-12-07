#include "zmqipc.hpp"
#include <QtCore>
#include <iostream>

#include "strconv.h"

using namespace std;

class ZmqIPC
{
    ZmqContext context;
public:
    explicit ZmqIPC()
    {
    }
    virtual ~ZmqIPC()
    {
    }
    bool open_client(const std::string &server, int debug)
    {
        std::string endpoint;
        if(!this->context.open_client(endpoint)) return false;
        std::wstring cmdline = utf8_to_wide(server);
        cmdline += L" ";
        cmdline += utf8_to_wide(endpoint);
        std::cout << wide_to_utf8(cmdline) << std::endl;
        PROCESS_INFORMATION ps = {0};
        STARTUPINFOW si = {0};
        WINBOOL b = CreateProcessW(
            NULL,
            (LPWSTR)cmdline.c_str(),
            NULL,
            NULL,
            FALSE,
            debug ? 0 : CREATE_NO_WINDOW,
            NULL,
            NULL,
            &si,
            &ps);
        if (!b)
        {
          std::cout << "Could not start client." << std::endl;
          return false;
        }
    }
    void send_msg(const std::string &msg)
    {
        this->context.send_msg(msg);
    }
    std::string recv_msg()
    {
        return this->context.recv_msg();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if 0x0
    ZmqContext ipc;
#else
    ZmqIPC ipc;
#endif
    std::string endpoint;
#if 0x0
    bool b = ipc.open_client(endpoint);
#else
    bool b = ipc.open_client(u8R"(C:\Users\javac\misc5\racket\build-server-Desktop_Qt_MinGW_w64_32bit_MSYS2-Debug\debug\server.exe)", 1);
#endif
    if(!b) return 1;
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
