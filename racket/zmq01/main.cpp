#include <QtCore>
#include <iostream>
#include <zmq.hpp>
#include <zmq_addon.hpp>

#include "strconv.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    char port[1024]; //make this sufficiently large.
                     //otherwise an error will be thrown because of invalid argument.
    size_t size = sizeof(port);
    try{
#if 0x0
        socket.bind("tcp://127.0.0.1:*");
#else
        socket.bind("tcp://127.0.0.1:50862");
#endif
    } catch (zmq::error_t &e){
        cerr << "couldn't bind to socket: " << e.what() << endl;
        return e.num();
    }
    socket.getsockopt( ZMQ_LAST_ENDPOINT, &port, &size );
    cout << "socket is bound at port " << port << endl;

    while (true) {
        zmq::message_t request;
        zmq::detail::recv_result_t result;
        // クライアントからのリクエストを待機
        try{
            result = socket.recv(request);
        } catch (zmq::error_t &e){
            cerr << "couldn't receive from socket: " << e.what() << endl;
            return e.num();
        }
        if (!result) {
            return 1;
        }
        size_t size = result.value(); // 有効値を取り出す
        std::cout << size << std::endl;
        std::string msg((char *)request.data(), size);
        std::cout << "Received Hello: " << utf8_to_ansi(msg) << std::endl;
        std::string reply = "[" + msg + "]";
        zmq::message_t response(reply.size());
        memcpy(response.data(), reply.c_str(), reply.size());
        socket.send(response);
    }

    return 0;
}
