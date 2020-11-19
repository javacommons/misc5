#include "mychaiscript.hpp"

#include <string>
#include "strconv2.hpp"

class Person {
public:
    std::string name;
    int age;
    explicit Person(std::string a_name, int a_age) {
        name = a_name;
        age = a_age;
    }
    virtual ~Person() {
        printf("~Person()\n"); fflush(stdout);
    }
    std::string to_string() const {
        return strconv::format("Person(人) { name=%s, age=%d }", name.c_str(), age);
    }
};

std::string to_console(const std::string &s) {
    static strconv::io io;
    return io.to_console(s);
}

int main() {
    MyChaiscript chai;
    chai.add(chaiscript::fun(&to_console), "to_console");
    chai.eval(R"***( puts(helloWorld("Bob")+"\n"); //helloWorld is defined in mychaiscript.cpp )***");
    chai.eval(R"***( puts(helloWorld("John")+"\n"); //helloWorld is defined in mychaiscript.cpp )***");
    chai.add(chaiscript::fun<std::function<std::string (bool)>>([](bool type) {
        if (type) { return "x"; }
        else { return "y"; }
    }), "function_name");
    chai.eval(R"***( puts(function_name(true)+"\n"); )***");

    //chai.add(chaiscript::user_type<Person>(), "Person");
    chai.add(chaiscript::constructor<Person(std::string a_name, int a_age)>(), "Person");
    chai.add(chaiscript::fun(&Person::name), "name");
    chai.add(chaiscript::fun(&Person::age), "age");
    chai.add(chaiscript::fun(&Person::to_string), "to_string");
    chai.eval(R"***( var p = Person("Bob", 32); )***");
    chai.eval(R"***( print(p.name); )***");
    chai.eval(R"***( print(p.age); )***");
    //chai.eval(R"***( print(p.height); )***");
    //chai.eval(R"***( p = 0; )***");
    //chai.eval(R"***( var p = 0; )***");
    chai.eval(R"***( for(var i=0; i<5; ++i) { print(i); var p2 = Person("repeated", i); print(to_string(p2).to_console()); } )***");
    printf("[END]\n"); fflush(stdout);
}
