#include <iostream>
#include <string>
using namespace std;

#include "vardecl.h"

extern"C" void foo(){
    cout << "hello c++!" << endl;
}

// fn my_printer(s: *const c_char);
extern"C" void my_printer(const char *msg){
    cout << "msg=" << msg << endl;
}

// fn my_string() -> *const c_char;
extern"C" const char *my_string(){
    TLS_VARIABLE_DECL std::string msg;
    msg = "<hello>";
    return msg.c_str();
}
