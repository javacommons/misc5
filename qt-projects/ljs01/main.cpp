#include <QtCore>
#include <iostream>
#include <sol/sol.hpp>

// クラスAをC++とLua間でやりとりしたい
class A
{
public:
    A(const int val = 0, const std::string dummy = "") : val_(val) {
        qDebug() << "dummy=" << dummy.c_str();
    }
    ~A() { qDebug() << "~A() called"; }

    int f1() {
        return val_ * 100;
    }

    int f2(int rate) {
        return val_ * rate;
    }

    int g() {
        return val_ * 100;
    }

    int g(int rate) {
        return val_ * rate;
    }

    int getVal() {
        return val_;
    }

    void setVal(const int val) {
        val_ = val;
    }

    int x = 0;

    static int st_func2(int a) { return a + 200; }

private:
    int val_;
};

std::string overfunc(const std::string &a) {
    return a + "!!!";
}

int overfunc(int a) {
    return a + 100;
}

#if 0x0
QByteArray getResource(const QString &path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    file.close();
    return bytes;
}
#endif

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "hello!";

    //qDebug() << getResource(":/scripts/hello.lua");

    sol::state lua;
    lua.open_libraries(
                sol::lib::base,
                sol::lib::package,
                sol::lib::math,
                sol::lib::string,
                sol::lib::table,
                sol::lib::io
                );
    lua.script("print('Hello World')");
    system("pwd");

    lua.script(R"***(
               var json = {"name": "bob"};
               var A = {t: {f: 7}, n: 3}
               var ary = [1,2,3,4]; //Array style declaration, syntax sugar for {}
               var num = 5;

               if(json.name == "bob") print("Hello Bob !"); // if/ese like in C/C++/Java/Javascript
               else if(json.name == "mary") print("A pretty woman !");
               else print("Nice to meet you !");

               for(i=1, 10) print(i);
               for(k,v in pairs(json)) print(k,v);

               for(k,v in pairs(A)) { // blocks are curly braces delimited
                   if(k == "one") continue;
                   print(k, type(k), v);
               }

               while(num > 0) --num; //pre inc/dec operators
               num += 5; // compound operators
               while(num > 0) {
                   print(num--);
               }
               num += 5;
               do { //conventional do/while
                   if(num == 3) goto update;
                   //inline boolean expression
                   print(num == 2 ? "it's a two" : "it's a " .. num);
               update:
                   --num;
               } while(num > 0);

               function doIt(p : string) : string { // functions and variables can have an anotation
                   return "Done " .. p;
               }

               print(doIt("car"));

               function doAgain(p) {
                   if(p == null) return "I don't know what to do !"; // uses "null" instead of "nil"
                   return "Done " .. p;
               }

               print(doAgain("car"));

               var Engine = {
                   speed : 0
               };

               function Engine::speedTo(v : integer) { //synatx sugar for function member with "this"
                   this.speed = v; // use "this" instead of "self"
               }

               print(Engine.speed);
               Engine->speedTo(12); //syntax sugar for method call with implicity "this"
               print(Engine.speed);
               )***");

    //lua["json"] = lua.script_file("json.lua");

    lua["intval"] = 100;
    lua["pi"] = 3.14;
    lua["some_text"] = "abcdef";

    // ユーザー定義型の登録
    lua.new_usertype<A>(
        // 型名
        "A",
        //コンストラクタ
        sol::constructors<A(const int, const std::string)>(),
        // メンバ関数
        "f", sol::overload( &A::f1, &A::f2, [](A& self, int a, int b) ->int { return a + b; } ),
        "g", sol::overload( (int(A::*)())&A::g, (int(A::*)(int))&A::g ),
        // メンバ変数
        "x", &A::x,
        // プロパティ
        "val", sol::property(&A::getVal, &A::setVal),
        // ラムダ関数も使用可
        "y", [](A& a, const int n) ->int { return a.x * n; }
        );

    lua["A"]["st_fun"] = [](int a) { return a+100; };
    lua["A"]["st_fun2"] = &A::st_func2;

#if 0x0
    lua.set_function("overfunc", sol::overload(
      [](int x) { return overfunc(x); },
      [](const std::string &x) { return overfunc(x); }
    ));
#else
    lua.set_function("overfunc", sol::overload(
      (int(*)(int x))overfunc,
      (std::string(*)(const std::string &))overfunc
    ));
#endif

    lua["of2"] = sol::overload(
                (int(*)(int x))overfunc,
                (std::string(*)(const std::string &))overfunc
              );

    //lua.script_file("hello.lua");
    //lua.script(getResource(":/scripts/hello.lua").constData());

    qDebug() << lua["a"].get<int>(); // => '100'
    qDebug() << lua["b"].get<int>(); // => '200'
    qDebug() << lua["not_exist"].get_or(999);  // => '999'

    lua["func2"] = [](const int x) { return x * 2; };  // ラムダでもいい
    lua.script("print(func2(10))");  // => '20'

#if 0x1
    auto x_type = lua.script("return type(x)").get<std::string>();
    qDebug() << x_type.c_str();
    auto x = lua["x"].get<A*>();
    if(x) qDebug() << x->g();
    if(x) qDebug() << x->g(10);
    auto z = lua.script("return nil").get<A*>();
    if(z) qDebug() << z->g();
    if(z) qDebug() << z->g(10);
#endif

    lua.script(R"***(
               function real_print_recursive (e, level) {
                   var et = type(e);
                   if( et == 'table' ) {
                       io.write("{ ");
                       var iters = 0;
                       for( k, v in pairs(e) ) {
                           if( iters != 0  ) {
                               io.write(", ");
                           }
                           real_print_recursive(k, level + 1);
                           io.write(": ");
                           real_print_recursive(v, level + 1);
                           ++iters    ;
                       }
                       io.write(" }");
                   } else if( et == 'string' ) {
                       io.write('"');
                       io.write(e);
                       io.write('"');
                   } else {
                       io.write(tostring(e));
                   }
                   if( level == 0 ) {
                       io.write("\n");
                   }
               }

               function print_recursive (e) {
                   real_print_recursive(e, 0);
               }
               )***");

    lua.script(R"***(
               print_recursive({a:123, b: "abc", c: [11,22,33]});
               )***");
    //lua.collect_garbage();

    lua.safe_script_file("../ljs01/fib.ljs");

    auto st = lua.script(R"***(
               print("(1)");
               print(fib(39));
               print("(2)");
               )***");

    qDebug() << st.valid();

    try {
    st = lua.safe_script(R"***(
               print("(3)");
               print(fib2(39));
               print("(4)");
               )***", "chunkname-1");

    qDebug() << st.valid();
    } catch(const std::exception &ex) {
        std::cout << "<WHAT>" << ex.what() << std::endl;
    }

    qDebug() << "[END]";
    //return a.exec();
    return 0;
}
