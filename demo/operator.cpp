#include <iostream>

struct Adder
{
    int x, y;
    int operator()()
    {
        return x + y;
    }
    int operator()(int bonus)
    {
        return x + y + bonus;
    }
};

class Adder2
{
    int x, y, z;

public:
    Adder2(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int operator()()
    {
        return x + y;
    }
    int operator()(int bonus)
    {
        return x + y + bonus;
    }
};

int main()
{
    auto result = Adder{11, 22}();
    std::cout << result << std::endl;
    std::cout << Adder{11, 22}(100) << std::endl;
    std::cout << Adder2(11, 22)() << std::endl;
    std::cout << Adder2(11, 22)(100) << std::endl;
    return 0;
}