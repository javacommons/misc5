#include "zmqipc.hpp"
#include <thread>
#include <chrono>
#include "strutil.h"

ZmqContext::ZmqContext()
{
    this->context = new zmq::context_t(1);
}

ZmqContext::~ZmqContext()
{
    if(this->socket)
    {
        this->socket->close();
        delete this->socket;
    }
    if(this->context)
    {
        this->context->close();
        delete this->context;
    }
}

bool ZmqContext::open_client(std::string &endpoint)
{
    endpoint = "";
    this->socket = new zmq::socket_t(*this->context, ZMQ_REP);
    std::vector<char> port(128);
    size_t size = port.size();
    try
    {
        this->socket->bind("tcp://127.0.0.1:*");
    }
    catch (zmq::error_t &e)
    {
        return false;
    }
    this->socket->getsockopt(ZMQ_LAST_ENDPOINT, &port[0], &size);
    endpoint = &port[0];
    return true;
}

bool ZmqContext::open_server(const std::string &endpoint)
{
    this->socket = new zmq::socket_t(*this->context, ZMQ_REQ);
    try
    {
        this->socket->connect(endpoint.c_str());
        return true;
    }
    catch (zmq::error_t &e)
    {
        return false;
    }
}

void ZmqContext::send_msg(const std::string &msg)
{
    if(!this->socket) return;
    zmq::message_t response(msg.size());
    memcpy(response.data(), msg.c_str(), msg.size());
    this->socket->send(response, zmq::send_flags::none);
}

std::string ZmqContext::recv_msg()
{
    if(!this->socket) return "";
    zmq::message_t request;
    zmq::detail::recv_result_t result;
    try
    {
        result = this->socket->recv(request);
    }
    catch (zmq::error_t &e)
    {
        return "";
    }
    if (!result)
    {
        return "";
    }
    size_t size = result.value();
    std::string msg((char *)request.data(), size);
    return msg;
}

ZmqIPC::ZmqIPC()
{
}

ZmqIPC::~ZmqIPC()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if(!this->server_process) return;
    delete this->server_process;
}

bool ZmqIPC::open_client(const std::string &server, bool debug)
{
    std::string endpoint;
    if(!this->context.open_client(endpoint)) return false;
    std::wstring cmdline = utf8_to_wide(server);
    cmdline += L" ";
    cmdline += utf8_to_wide(endpoint);
    std::cout << wide_to_utf8(cmdline) << std::endl;
    this->server_process = new ZmqProcess(cmdline, debug);
    //std::cout << "(a)" << std::endl;
    if(!this->server_process->started())
    {
        delete this->server_process;
        this->server_process = nullptr;
        return false;
    }
    return true;
}

bool ZmqIPC::open_server(const std::string &endpoint)
{
    return this->context.open_server(endpoint);
}

void ZmqIPC::send_msg(const std::string &msg)
{
    this->context.send_msg(msg);
}

std::string ZmqIPC::recv_msg()
{
    return this->context.recv_msg();
}

extern "C" void __wgetmainargs(int*, wchar_t***, wchar_t***, int, int*);
bool find_endpont_from_args(std::string &endpoint)
{
    endpoint = "";
    int argc, si = 0;
    wchar_t **argv, **env;
    __wgetmainargs(&argc, &argv, &env, 0, &si);
    if(argc < 2) return false;
    std::wstring arg1 = argv[1];
    if(!starts_with(arg1, L"tcp://")) return false;
    endpoint = wide_to_utf8(arg1);
    return true;
}

ZmqProcess::ZmqProcess(const std::wstring &cmdline, bool debug)
{
    //std::cout << "(b)" << std::endl;
    memset(&m_si, 0, sizeof(m_si));
    m_si.cb = sizeof(m_si);
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
    //std::cout << "(c)" << std::endl;
    if (!b)
    {
        std::cout << "Could not start client." << std::endl;
        this->m_started = false;
    }
    //std::cout << "(d)" << std::endl;
    this->m_started = true;
    //std::cout << "(e)" << std::endl;
}

ZmqProcess::~ZmqProcess()
{
    if(!this->m_started) return;
    std::cout << "kill the server" << std::endl;
    TerminateProcess(m_pi.hProcess, 0);
#if 0x0
    const DWORD result = WaitForSingleObject(m_pi.hProcess, 500);
    if (result == WAIT_OBJECT_0) {
        // Success
    }
    else {
        // Timed out or an error occurred
    }
#endif
    CloseHandle(m_pi.hThread);
    CloseHandle(m_pi.hProcess);
}

bool ZmqProcess::started()
{
    return this->m_started;
}
