#include "zmqipc.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "strutil.h"
#include "vardecl.h"
#include <windows.h>
#include <tlhelp32.h>

ZmqContext::ZmqContext()
{
    this->context = new zmq::context_t(1);
}

ZmqContext::~ZmqContext()
{
    this->close();
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
    if (!this->socket)
        return;
    zmq::message_t response(msg.size());
    memcpy(response.data(), msg.c_str(), msg.size());
    this->socket->send(response, zmq::send_flags::none);
}

static DWORD parent_process_id()
{
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W pe;
    memset(&pe, 0, sizeof(pe));
    pe.dwSize = sizeof(pe);
    DWORD pid = GetCurrentProcessId();
    DWORD ppid = 0;
    if (Process32FirstW(h, &pe))
    {
        do
        {
            if (pe.th32ProcessID == pid)
            {
                ppid = pe.th32ParentProcessID;
            }
        } while (Process32NextW(h, &pe));
    }
    CloseHandle(h);
    return ppid;
}

static bool is_process_running(DWORD pid)
{
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD ret = WaitForSingleObject(process, 0);
    CloseHandle(process);
    return ret == WAIT_TIMEOUT;
}

void ZmqIPC::worker()
{
    DWORD ppid = parent_process_id();
    for (;;)
    {
        //cout << "worker" << endl;
        if (!is_process_running(ppid))
        {
            //::MessageBoxW(NULL, L"exiting...", L"server.exe", MB_OK);
            exit(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

std::string ZmqContext::recv_msg()
{
    if (!this->socket)
        return "";
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

void ZmqContext::close()
{
    if (this->socket)
    {
        this->socket->close();
        delete this->socket;
        this->socket = nullptr;
    }
    if (this->context)
    {
        this->context->close();
        delete this->context;
        this->context = nullptr;
    }
}

ZmqIPC::ZmqIPC()
{
}

ZmqIPC::~ZmqIPC()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    delete this->server_process;
    delete this->http_server;
    delete this->http_client;
}

bool ZmqIPC::open_client(const std::string &server, bool debug)
{
    std::string endpoint;
    if (!this->context.open_client(endpoint))
        return false;
    std::wstring cmdline = utf8_to_wide(server);
    cmdline += L" ";
    cmdline += utf8_to_wide(endpoint);
    cmdline += L" ";
    cmdline += format(L"%i", (int)debug);
    std::cout << wide_to_utf8(cmdline) << std::endl;
    this->server_process = new ZmqProcess(cmdline, debug);
    //std::cout << "(a)" << std::endl;
    if (!this->server_process->started())
    {
        delete this->server_process;
        this->server_process = nullptr;
        return false;
    }
#if 0x1
    json j = this->recv_json();
    this->context.close();
    int port = j["port"].get<int>();
    this->http_client = new httplib::Client("127.0.0.1", port);
    formatA(std::cout, "open_client(): port=%d\n", port);
#else
    this->recv_msg(); // #begin
#endif
    return true;
}

bool ZmqIPC::open_server(const std::string &endpoint, zmq_ipc_handler handler)
{
    this->api_handler = handler;
    std::thread *th = new std::thread(worker);
    UNUSED_VARIABLE(th);
    bool b = this->context.open_server(endpoint);
    if (b)
    {
#if 0x1
        this->http_server = new httplib::Server();
        this->http_server->Post("/test", [&](const httplib::Request &req, httplib::Response &res) {
            //formatA(std::cout, U8("/test req.body=%s (%s)\n"), req.body.c_str(), req.get_header_value("Content-Type").c_str());
            json j = json::parse(req.body);
            std::string api = j["api"];
            //formatA(std::cout, "api=%s\n", api.c_str());
            std::string input = j["input"].get<std::string>();
            std::string output;
            //formatA(std::cout, "before this->api_handler=%p\n", this->api_handler);
            const char *ret = this->api_handler(api.c_str(), input.c_str());
            //formatA(std::cout, "ret=%s\n", ret);
            if(!ret) ret = "false";
            output = ret;
            //formatA(std::cout, "output=%s\n", output.c_str());
            res.set_content(output, "application/json; charset=utf-8");
        });
        int port = this->http_server->bind_to_any_port("127.0.0.1");
        formatA(std::cout, "open_server(): port=%d\n", port);
        json p;
        p["port"] = port;
        this->send_json(p);
        this->http_server->listen_after_bind();
#else
        this->send_msg("#begin");
        for(;;)
        {
            auto msg = this->recv_msg();
            json j = json::parse(msg);
            std::string api = j["api"];
            std::string input = j["input"].get<std::string>();
            std::string output;
            const char *ret = this->api_handler(api.c_str(), input.c_str());
            if(!ret) ret = "false";
            output = ret;
            this->send_msg(output);
        }
#endif
    }
    return b;
}

void ZmqIPC::send_msg(const std::string &msg)
{
    this->context.send_msg(msg);
}

std::string ZmqIPC::recv_msg()
{
    return this->context.recv_msg();
}

void ZmqIPC::send_json(const json &j)
{
    this->context.send_msg(j.dump());
}

json ZmqIPC::recv_json()
{
    std::string msg = this->context.recv_msg();
    try
    {
        json j = json::parse(msg);
        return j;
    }
    catch (nlohmann::detail::parse_error &e)
    {
        json j = msg;
        return j;
    }
}

std::string ZmqIPC::call_api(const std::string &api, const std::string &input)
{
#if 0x1
    //formatA(std::cout, "call_api(1)\n");
    json req = json::object();
    req["api"] = api;
    req["input"] = input;
    auto res = this->http_client->Post("/test", req.dump(), "application/json; charset=utf-8");
    //formatA(std::cout, "call_api(2)\n");
    if (res)
    {
        json info = {
            {"status", res->status},
            {"content-type", res->get_header_value("Content-Type")},
            {"body", res->body}
        };
        //formatA(std::cout, "returning: %s\n", info.dump(4).c_str());
        return res->body;
    }
    //formatA(std::cout, "call_api(3)\n");
    return "false";
#else
    //formatA(std::cout, "call_api(1)\n");
    json req = json::object();
    req["api"] = api;
    req["input"] = input;
    this->send_msg(req.dump());
    auto res = this->recv_msg();
    return res;
#endif
}

void ZmqIPC::register_json_api(const std::string &name, ZmqIPC::json_api func)
{
    json_api_map[name] = func;
}

ZmqIPC::json_api ZmqIPC::retrieve_json_api(const std::string &name)
{
    if (json_api_map.count(name) == 0)
        return nullptr;
    return json_api_map[name];
}

extern "C" void __wgetmainargs(int *, wchar_t ***, wchar_t ***, int, int *);
bool find_endpont_from_args(std::string &endpoint, bool *debug)
{
    endpoint = "";
    if (debug)
        *debug = false;
    int argc, si = 0;
    wchar_t **argv, **env;
    __wgetmainargs(&argc, &argv, &env, 0, &si);
    if (argc < 2)
        return false;
    std::wstring arg1 = argv[1];
    if (!starts_with(arg1, L"tcp://"))
        return false;
    endpoint = wide_to_utf8(arg1);
    if (argc >= 3)
    {
        std::wstring arg2 = argv[2];
        *debug = !!atoi(wide_to_utf8(arg2).c_str());
    }
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
    if (!this->m_started)
        return;
#if 0x0
    std::cout << "kill the server" << std::endl;
    TerminateProcess(m_pi.hProcess, 0);
    CloseHandle(m_pi.hThread);
    CloseHandle(m_pi.hProcess);
#endif
}

bool ZmqProcess::started()
{
    return this->m_started;
}
