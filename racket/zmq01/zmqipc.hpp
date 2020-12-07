#ifndef ZMQIPC_HPP
#define ZMQIPC_HPP

#include <zmq.hpp>
#include <vector>

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
    #if 0x0
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

#endif //ZMQIPC_HPP
