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
    explicit ZmqProcess(const std::wstring &cmdline, bool debug);
    virtual ~ZmqProcess();
    bool started()
    {
        return this->m_started;
    }
};

bool find_endpont_from_args(std::string &endpoint);

#endif //ZMQIPC_HPP
