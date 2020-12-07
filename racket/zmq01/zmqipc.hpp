#ifndef ZMQIPC_HPP
#define ZMQIPC_HPP

#include <zmq.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "strconv.h"

class ZmqContext {
    zmq::context_t *context = nullptr;
    zmq::socket_t *socket = nullptr;
public:
    explicit ZmqContext()
    {
        this->context = new zmq::context_t(1);
    }
    virtual ~ZmqContext()
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
    bool open_client(std::string &endpoint)
    {
        endpoint = "";
        this->socket = new zmq::socket_t(*this->context, ZMQ_REP);
        std::vector<char> port(128);
        size_t size = port.size();
        try
        {
    #if 0x1
            this->socket->bind("tcp://127.0.0.1:*");
    #else
            this->socket->bind("tcp://127.0.0.1:50862");
    #endif
        }
        catch (zmq::error_t &e)
        {
            return false;
        }
        this->socket->getsockopt(ZMQ_LAST_ENDPOINT, &port[0], &size);
        endpoint = &port[0];
        return true;
    }
    bool open_server(const std::string &endpoint)
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
    void send_msg(const std::string &msg)
    {
        if(!this->socket) return;
        zmq::message_t response(msg.size());
        memcpy(response.data(), msg.c_str(), msg.size());
        this->socket->send(response, zmq::send_flags::none);
    }
    std::string recv_msg()
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
};

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
    bool open_server(const std::string &endpoint)
    {
        return this->context.open_server(endpoint);
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

#endif //ZMQIPC_HPP
