#include <QtCore>
#include <iostream>
#include <zmq.hpp>
//#include <zmq_addon.hpp>

#include "strconv.h"

using namespace std;

void send_msg(zmq::socket_t &socket, const std::string &msg)
{
    zmq::message_t response(msg.size());
    memcpy(response.data(), msg.c_str(), msg.size());
    socket.send(response, zmq::send_flags::none);
}

std::string recv_msg(zmq::socket_t &socket)
{
    zmq::message_t request;
    zmq::detail::recv_result_t result;
    try
    {
        result = socket.recv(request);
    }
    catch (zmq::error_t &e)
    {
        return "";
    }
    if (!result) {
        return "";
    }
    size_t size = result.value();
    std::string msg((char *)request.data(), size);
    return msg;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    try
    {
        socket.connect("tcp://127.0.0.1:50862");
    }
    catch (zmq::error_t &e)
    {
        cerr << "couldn't connect to socket: " << e.what() << endl;
        return e.num();
    }

    send_msg(socket, "#begin");
    while (true)
    {
        std::string msg = recv_msg(socket);
#if 0x0
        if(msg == "")
        {
            cout << "empty found" << endl;
            socket.close();
            return 0;
        }
#endif
        if(msg == "#end")
        {
            cout << "#end found" << endl;
            socket.close();
            return 0;
        }
        send_msg(socket, "[" + msg + "]");
    }

    return 0;
}
