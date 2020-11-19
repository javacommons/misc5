#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>

#include "base64.hpp"

int main()
{
    // create an empty structure (null)
    json j;

    // add a number that is stored as double (note the implicit conversion of j to an object)
    j["pi"] = 3.141;

    // add a Boolean that is stored as bool
    j["happy"] = true;

    // add a string that is stored as std::string
    j["name"] = "Niels";

    // add another null object by passing nullptr
    j["nothing"] = nullptr;

    // add an object inside the object
    j["answer"]["everything"] = 42;

    // add an array that is stored as std::vector (using an initializer list)
    j["list"] = {1, 0, 2};

    // add another object (using an initializer list of pairs)
    j["object"] = {{"currency", "USD"}, {"value", 42.99}};

    // instead, you could also write (which looks very similar to the JSON above)
    json j2 = {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {"answer", {{"everything", 42}}},
        {"list", {1, 0, 2}},
        {"object", {{"currency", "USD"}, {"value", 42.99}}}};

    auto j3 = R"(
    {
        "happy": true,
        "pi": 3.141
    }
    )"_json;

    auto j4 = json::parse(R"(
    {
        "happy": true,
        "pi": 3.141
    }
    )");

    std::cout << j << std::endl;
    std::cout << j2 << std::endl;
    std::cout << j3 << std::endl;
    std::cout << j4.dump(4) << std::endl;
    std::cout << j["pi"].get<double>() << std::endl;

    msgpack::type::tuple<int, bool, std::string> src(1, true, "example");

    // serialize the object into the buffer.
    // any classes that implements write(const char*,size_t) can be a buffer.
    std::stringstream buffer;
    msgpack::pack(buffer, src);

    // send the buffer ...
    buffer.seekg(0);

    // deserialize the buffer into msgpack::object instance.
    std::string str(buffer.str());

    msgpack::object_handle oh =
        msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    // msgpack::object supports ostream.
    std::cout << deserialized << std::endl;

    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<int, bool, std::string> dst;
    deserialized.convert(dst);

    // or create the new instance
    msgpack::type::tuple<int, bool, std::string> dst2 =
        deserialized.as<msgpack::type::tuple<int, bool, std::string>>();

#if 0x1
    std::string b64 = base64_encode("base64ベイス64");
    std::cout << b64 << std::endl;
    std::string dec = base64_decode(b64);
    std::cout << dec << std::endl;
#endif

    std::string enc1 = "g6Fiy0B8jHrhR64UoWOTAQIDoWHLQF7czMzMzM0=";
    std::cout << enc1.size() << std::endl;
    std::string dec1 = base64_decode(enc1);
    std::cout << dec1.size() << std::endl;

    json json1 = json::from_msgpack(dec1);
    std::cout << json1.dump(4) << std::endl;

    msgpack::object_handle oh1 =
        msgpack::unpack(dec1.data(), dec1.size());
    msgpack::object obj1 = oh1.get();
    std::cout << obj1 << std::endl;

    typedef std::map<std::string, msgpack::object> MapStrMsgpackObj;
    MapStrMsgpackObj mmap = obj1.as<MapStrMsgpackObj>();
    std::cout << mmap.find("a")->second.as<double>() << std::endl;
    std::cout << mmap.find("b")->second.as<double>() << std::endl;
    decltype(mmap)::iterator it = mmap.find("c");
    if(it == mmap.end()) {
        std::cout << "<not found>" << std::endl;
    } else {
        std::cout << it->second << std::endl;
        std::vector<int> vec;
        it->second.convert(vec);
        for(int i=0; i<vec.size(); i++) {
            std::cout << vec[i] << std::endl;
        }
    }

    std::cout << "[end]" << std::endl;

    return 0;
}