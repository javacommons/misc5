#! bash -uvx
#g++ -o server.exe server.cpp -lws2_32
#g++ -o client.exe client.cpp -lws2_32
g++ -o both.exe both.cpp -lws2_32 && ./both.exe
