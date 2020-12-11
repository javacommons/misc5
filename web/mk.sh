#! bash -uvx
#g++ -o server.exe server.cpp -lws2_32
#g++ -o client.exe client.cpp -lws2_32
g++ -o both.exe both.cpp httplib.cc -lws2_32 -lz && ./both.exe
