#ifndef ZMQIPC_HPP
#define ZMQIPC_HPP

#include <zmq.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "strconv.h"

class ZmqProcess;

class ZmqContext {
    zmq::context_t *context = nullptr;
    zmq::socket_t *socket = nullptr;
public:
    explicit ZmqContext();
    virtual ~ZmqContext();
    bool open_client(std::string &endpoint);
    bool open_server(const std::string &endpoint);
    void send_msg(const std::string &msg);
    std::string recv_msg();
};

class ZmqIPC
{
    ZmqContext context;
    class ZmqProcess *server_process = nullptr;
public:
    explicit ZmqIPC();
    virtual ~ZmqIPC();
    bool open_client(const std::string &server, bool debug);
    bool open_server(const std::string &endpoint);
    void send_msg(const std::string &msg);
    std::string recv_msg();
};

class ZmqProcess
{
    bool m_started = false;
    STARTUPINFOW m_si;
    PROCESS_INFORMATION m_pi;
public:
    explicit ZmqProcess(const std::wstring &cmdline, bool debug)
    {
        std::cout << "(b)" << std::endl;
        memset(&m_si, 0, sizeof(m_si));
        memset(&m_pi, 0, sizeof(m_pi));
        WINBOOL b = CreateProcessW(
                    NULL,
                    (LPWSTR)cmdline.c_str(),
                    NULL,
                    NULL,
                    FALSE,
                    debug ? 0 : CREATE_NO_WINDOW,
                    NULL,
                    NULL,
                    &m_si,
                    &m_pi);
        std::cout << "(c)" << std::endl;
        if (!b)
        {
            std::cout << "Could not start client." << std::endl;
            this->m_started = false;
        }
        std::cout << "(d)" << std::endl;
        this->m_started = true;
        std::cout << "(e)" << std::endl;
    }
    virtual ~ZmqProcess()
    {
        if(!this->m_started) return;
        std::cout << "kill the server" << std::endl;
        TerminateProcess(m_pi.hProcess, 0);
        // 500 ms timeout; use INFINITE for no timeout
        const DWORD result = WaitForSingleObject(m_pi.hProcess, 500);
        if (result == WAIT_OBJECT_0) {
            // Success
        }
        else {
            // Timed out or an error occurred
        }
        CloseHandle(m_pi.hProcess);
        CloseHandle(m_pi.hThread);
    }
    bool started()
    {
        return this->m_started;
    }
};

bool find_endpont_from_args(std::string &endpoint);

#endif //ZMQIPC_HPP
