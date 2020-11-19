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

QByteArray getResource(const QString &path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    file.close();
    return bytes;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "hello!";

    qDebug() << getResource(":/scripts/hello.lua");

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

    lua["json"] = lua.script_file("json.lua");

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
    lua.script(getResource(":/scripts/hello.lua").constData());

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

    const auto& code = R"(
        function real_print_recursive (e, level)
            local et = type(e)
            if et == 'table' then
                io.write("{ ")
                local iters = 0
                for k, v in pairs(e) do
                    if iters ~= 0  then
                        io.write(", ")
                    end
                    real_print_recursive(k, level + 1)
                    io.write(": ")
                    real_print_recursive(v, level + 1)
                    iters = iters + 1
                end
                io.write(" }")
            elseif et == 'string' then
                io.write('"')
                io.write(e)
                io.write('"')
            else
                io.write(tostring(e))
            end
            if level == 0 then
                io.write("\n")
            end
        end

        function print_recursive (e)
            real_print_recursive(e, 0)
        end
    )";

    sol::optional<sol::error> maybe_error = lua.safe_script(code, sol::script_pass_on_error);
    if (maybe_error) {
        std::cerr << maybe_error->what() << std::endl;
        return 1;
    }
    sol::function print_recursive = lua["print_recursive"];

    print_recursive(lua["ary"]);
    print_recursive(lua["x"]);
    //lua.collect_garbage();

    qDebug() << "[END]";
    //return a.exec();
    return 0;
}
