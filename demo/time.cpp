#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

int main()
{
    time_t t = std::time(nullptr);
    struct tm *ptm = std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(ptm, "%Y-%m-%d %H:%M:%S");
    std::string str = oss.str();

    std::cout << str << std::endl;
}
