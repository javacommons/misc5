#ifndef ZMQIPC_HPP
#define ZMQIPC_HPP

#include <zmq.hpp>
#include <string>
#include <windows.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

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
    static void worker();
    typedef json (*json_api)(const json &input);
    std::map<std::string, json_api> json_api_map;
public:
    explicit ZmqIPC();
    virtual ~ZmqIPC();
    bool open_client(const std::string &server, bool debug);
    bool open_server(const std::string &endpoint);
    void send_msg(const std::string &msg);
    std::string recv_msg();
    void send_json(const json &j);
    json recv_json();
    json call_json_api(const std::string &api, const json &input);
    void register_json_api(const std::string &name, json_api func);
    json_api retrieve_json_api(const std::string &name);
    bool handle_json_api();
};
#define REGISTER_JSON_API(IPC, X) ((IPC).register_json_api(#X, X))

class ZmqProcess
{
    bool m_started = false;
    STARTUPINFOW m_si;
    PROCESS_INFORMATION m_pi;
public:
    explicit ZmqProcess(const std::wstring &cmdline, bool debug);
    virtual ~ZmqProcess();
    bool started();
};

bool find_endpont_from_args(std::string &endpoint, bool *debug = nullptr);

#endif //ZMQIPC_HPP
