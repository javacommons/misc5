#include "zmqipc.hpp"
#include <QtCore>
#include <iostream>

//#include "strconv.h"
#include "strutil.h"

#include <windows.h>
#include <tlhelp32.h>

using namespace std;

std::wstring parent_programW()
{
    DWORD myPID = ::GetCurrentProcessId();
    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE) return L"";
    PROCESSENTRY32W pe32;
    pe32.dwSize = sizeof(pe32);
    DWORD parentPID = 0;
    std::map<DWORD, std::wstring> ProcessIdVsName;
    if(!::Process32FirstW(hProcessSnap, &pe32)) {
        ::CloseHandle(hProcessSnap);
        return L"";
    }
    do {
        std::pair<DWORD, std::wstring> p(pe32.th32ProcessID, pe32.szExeFile);
        /*std::pair<std::map<DWORD, std::wstring>::iterator, bool> result = */ProcessIdVsName.insert(p);
        if(pe32.th32ProcessID == myPID) {
            parentPID = pe32.th32ParentProcessID;
        }
    } while(::Process32NextW(hProcessSnap, &pe32));
    ::CloseHandle(hProcessSnap);
    std::map<DWORD, std::wstring>::iterator parent = ProcessIdVsName.find(parentPID);
    if(parent == ProcessIdVsName.end()) return L"";
    return parent->second;
}

DWORD parent_process_id()
{
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W pe;
    memset(&pe, 0, sizeof(pe));
    pe.dwSize = sizeof(pe);
    DWORD pid = GetCurrentProcessId();
    DWORD ppid = 0;
    if( Process32First(h, &pe)) {
        do {
            if (pe.th32ProcessID == pid) {
                ppid = pe.th32ParentProcessID;
            }
        } while( Process32Next(h, &pe));
    }
    CloseHandle(h);
    return ppid;
}

bool is_process_running(DWORD pid)
{
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD ret = WaitForSingleObject(process, 0);
    CloseHandle(process);
    return ret == WAIT_TIMEOUT;
}

void worker()
{
    DWORD ppid = parent_process_id();
    for(;;)
    {
        cout << "worker" << endl;
        if(!is_process_running(ppid))
        {
            ::MessageBoxW(NULL, L"exiting...", L"server.exe", MB_OK);
            exit(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::thread th(worker);

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
