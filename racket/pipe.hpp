#ifndef PIPE_HPP
#define PIPE_HPP

#include <windows.h>
#include <string>

inline HANDLE create_pipe_server(const std::string &name, DWORD buffer_size) {
    std::string pipe_name = std::string(R"(\\.\pipe\)") + name;
    HANDLE hPipe = CreateNamedPipeA(pipe_name.c_str(),
                                    PIPE_ACCESS_DUPLEX,
                                    PIPE_TYPE_BYTE,
                                    PIPE_UNLIMITED_INSTANCES,
                                    buffer_size,
                                    buffer_size,
                                    0,
                                    NULL);
    return hPipe;
}

inline HANDLE create_pipe_client(const std::string &name) {
    std::string pipe_name = std::string(R"(\\.\pipe\)") + name;
    HANDLE hPipe = CreateFileA(pipe_name.c_str(),
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               NULL,
                               OPEN_EXISTING,
                               0,
                               NULL);
    return hPipe;
}

inline std::string read_string_from_pipe(HANDLE hPipe) {
    char c;
    std::string read = "";
    while(true) {
        DWORD  dwResult;
        if(!ReadFile(hPipe, &c, sizeof(c), &dwResult, NULL)) break;
        if(c=='\0') break;
        read.push_back(c);
    }
    return read;
}

inline void write_string_to_pipe(HANDLE hPipe, const std::string &s) {
    DWORD  dwResult;
    WriteFile(hPipe, s.c_str(), s.size()+1, &dwResult, NULL);
}

#endif //PIPE_HPP
