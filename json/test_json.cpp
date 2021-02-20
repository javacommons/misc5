/*************************************************************************
    > File Name: test_json.cpp
    > Author: ce39906
    > Mail: ce39906@163.com
    > Created Time: 2018-07-31 19:26:17
 ************************************************************************/
#include <iostream>
#include <vjson/json.hpp>

using namespace json;

#if 0x0
using Value = boost::variant<String,
                             Number,
                             boost::recursive_wrapper<Object>,
                             boost::recursive_wrapper<Array>,
                             True,
                             False,
                             Null>;
#endif

namespace json {

struct Json {
    const Value *value;
    Value store;
    Json(const Value &value): value(&value)
    {
    }
    Json(const Object &obj)
    {
        store = obj;
        this->value = &store;
    }
    Json(const Array &obj)
    {
        store = obj;
        this->value = &store;
    }
    Json(const Number &obj)
    {
        store = obj;
        this->value = &store;
    }
    Json(const True &obj)
    {
        store = obj;
        this->value = &store;
    }
    Json(const False &obj)
    {
        store = obj;
        this->value = &store;
    }
    Json(const Null &obj)
    {
        store = obj;
        this->value = &store;
    }
    std::string type()
    {
        switch(value->which())
        {
        case 0: return "String";
        case 1: return "Number";
        case 2: return "Object";
        case 3: return "Array";
        case 4: return "True";
        case 5: return "False";
        case 6: return "Null";
        default: return "?";
        }
    }
};

}

int main()
{
    Object obj;
    obj.values["string"] = "v1";
    obj.values["bool"] = True();
    obj.values["null"] = Null();
    obj.values["number"] = Number(9);
    
    Array arr;
    arr.values.emplace_back(Number(1.02));
    arr.values.emplace_back(Number(2.2));
    arr.values.emplace_back(Number(3));
    arr.values.emplace_back(True());
    arr.values.emplace_back(False());
    obj.values["array"] = std::move(arr);
    
    // json access
    std::cout << "Test json access.\n";
    const auto& arr1 = access::asArray(obj["array"]);
    std::cout << "first number in arr is "
              << access::asNumber(arr1.front()).value << std::endl;
    // json serialize to ostream
    std::cout << "Test serialize to ostream.\n";
    serialize(std::cout, obj);
    std::cout << std::endl;
    // json serialize to string
    std::cout << "Test serialize to string.\n";
    std::string str;
    serialize(str, obj);
    std::cout << str << std::endl;

    Value objVal = obj;
    if (objVal.type() == typeid(Object)) {
        std::cout << "Object" << std::endl;
        const Object &vObj = access::asObject(objVal);
        Json j(access::asObject(objVal));
        auto &map = vObj.values;
        for (auto& it: map) {
            std::cout << it.first << std::endl;
            Json second(it.second);
            std::cout << it.second.which() << second.type() << std::endl;
        }
    } else {
        std::cout << "Not Object" << std::endl;
    }

    return 0;
}
