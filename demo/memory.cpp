#include <windows.h>
#include <stdexcept>

MEMORYSTATUSEX memory_status() // https://www.youtube.com/watch?v=LSkAs15aJbU
{
    MEMORYSTATUSEX m = {sizeof m};
    if(GlobalMemoryStatusEx(&m))
    {
        return m;
    }
    else
    {
        throw std::runtime_error("GlobalMemoryStatusEx");
    }
}
