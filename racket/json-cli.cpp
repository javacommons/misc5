#include "calc.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "strconv.h"

#include <time.h>

typedef json (*json_function)(const json &input);

json func1(const json &input)
{
    return 1234;
}

namespace ns
{
    struct person
    {
        std::string name;
        std::string address;
        int age;
    };
} // namespace ns

namespace ns
{
    void to_json(json &j, const person &p)
    {
        j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
    }
    void from_json(const json &j, person &p)
    {
        j.at("name").get_to(p.name); // get_to(T& arg) は arg = get<T>() と同じ
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
    }
} // namespace ns

json api_persons(/*const json &input*/)
{
    //std::cout << "[api_persons] input=" << input << std::endl;
    typedef std::vector<ns::person> person_vec;
    person_vec vec;
    vec.push_back(ns::person{"Ned Flanders", "744 Evergreen Terrace", 60});
    vec.push_back(ns::person{"Ned2 Flanders", "7442 Evergreen Terrace", 602});
    json j = vec;
    return j;
}

int handle_pipe_events(const std::string &pipe_name)
{
    std::map<std::string, json_function> func_map;
    func_map["func1"] = func1;
    std::string hPipe = open_pipe_client(pipe_name.c_str());
    while (true)
    {
        std::string input_json = read_from_pipe(hPipe.c_str());
        std::cout << "input_json=" << input_json << std::endl;
        if (input_json.empty())
            break;
        json packet = json::parse(input_json);
        std::string api_name = packet["name"];
        json value = packet["value"];
        std::cout << api_name << " " << value << std::endl;
        json result = api_persons();
        result = 18446744073709551615ULL;
        json output;
        output["name"] = api_name;
        output["value"] = result;
        std::cout << output << std::endl;
        write_to_pipe(hPipe.c_str(), output.dump().c_str());
    }
    return 0;
}

static inline ULONGLONG get_time_stamp()
{
    FILETIME file_time;
    GetSystemTimeAsFileTime(&file_time);
	ULONGLONG ull = (ULONGLONG)file_time.dwHighDateTime << 32 | file_time.dwLowDateTime;
    return ull;
}

extern "C" void __wgetmainargs(int *, wchar_t ***, wchar_t ***, int, int *);
int main(int, char **)
{
    int argc, si = 0;
    wchar_t **argv, **env;
    __wgetmainargs(&argc, &argv, &env, 0, &si);
    printf("argc=%d\n", argc);
    if (argc >= 2)
    {
        std::string pipe_name = wide_to_utf8(argv[1]).c_str();
        printf("pipe_name=%s\n", pipe_name.c_str());
        return handle_pipe_events(pipe_name);
    }
    std::cout << "(1)" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};
    std::cout << "(2)" << std::endl;
    json j = p; // jsonへの暗黙的変換
    std::cout << "(3)" << std::endl;
    std::cout << j << std::endl;
    std::cout << "(4)" << std::endl;
    // {"address":"744 Evergreen Terrace","age":60,"name":"Ned Flanders"}
    ns::person p2 = j.get<ns::person>(); // json->personへの変換
    std::cout << "(5)" << std::endl;

    json output = api_persons();
    std::cout << output << std::endl;

    auto n = 18446744073709551615ULL;
    std::string s = unsigned_to_string(n);
    std::cout << s << std::endl;
    unsigned long long ull = string_to_unsigned(s);
    std::cout << ull << std::endl;

    json big = n;
    std::cout << "big=" << big.dump() << std::endl;

    //SYSTEMTIME systime;
    //GetSystemTime(&systime);

    FILETIME file_time;
    GetSystemTimeAsFileTime(&file_time);

	ULONGLONG ll;
	ll = (ULONGLONG)file_time.dwHighDateTime << 32 | file_time.dwLowDateTime;

#if 0x0
    time_t t = time(NULL);
    struct tm tm;
    char str[81];
    localtime_s(&tm, &t);
    strftime(str, sizeof(str), "%Y-%m-%d %H:%I:%S", &tm);
    printf("%s\n", str);
#endif
    std::cout << get_time_stamp() << std::endl;


    return 0;
}
