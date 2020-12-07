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
    try{
        result = socket.recv(request);
    } catch (zmq::error_t &e){
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
    zmq::socket_t socket(context, ZMQ_REP);
    char port[1024]; //make this sufficiently large.
                     //otherwise an error will be thrown because of invalid argument.
    size_t size = sizeof(port);
    try
    {
#if 0x0
        socket.bind("tcp://127.0.0.1:*");
#else
        socket.bind("tcp://127.0.0.1:50862");
#endif
    }
    catch (zmq::error_t &e)
    {
        cerr << "couldn't bind to socket: " << e.what() << endl;
        return e.num();
    }
    socket.getsockopt( ZMQ_LAST_ENDPOINT, &port, &size );
    cout << "socket is bound at port " << port << endl;

    std::string bgn = recv_msg(socket);
    if(bgn != "#begin")
    {
        cerr << "#begin not found" << endl;
        return 1;
    }
    for(int i=0; i<3; i++) {
        send_msg(socket, "testテスト");
        std::string res = recv_msg(socket);
        cout << utf8_to_ansi(res) << endl;
    }
    send_msg(socket, "#end");
    socket.close();

    return 0;
}
