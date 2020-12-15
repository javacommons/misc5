#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <map>

using atom = std::variant<int, char, std::string, void *>;
using list = std::vector<atom>;
using dict = std::map<std::string, atom>;
using variable = std::variant<int, char, std::string, void *, list, dict>;

struct xyz
{
    int a;
    int b;
};

int main()
{
    // int, char, std::stringのいずれかの型の値を保持できる型
    //std::variant<int, char, std::string> v = 3; // int型の値を代入
    variable v = 3;

    // 候補型の0番目の型 (int) を保持しているか
    if (v.index() == 0)
    {
        int &x = std::get<0>(v); // 型のインデックスを指定して、保持している値を取得
        std::cout << x << std::endl;
    }

    //v = std::string("Hello"); // std::string型オブジェクトを代入
    v = "Hello";

    // std::string型を保持しているか
    if (std::holds_alternative<std::string>(v))
    {
        std::string &x = std::get<std::string>(v); // 型を指定して、保持している値を取得
        std::cout << x << std::endl;
    }

    xyz x;
    //v = (void *)"Goodbye";
    v = &x;
    if (std::holds_alternative<void *>(v))
    {
        void *&x = std::get<void *>(v); // 型を指定して、保持している値を取得
        std::cout << x << std::endl;
    }
}