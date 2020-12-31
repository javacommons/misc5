#include <iostream>
#include <fstream>
#include "strconv.h"

int main()
{
    const char *fileName = "euc.tmp";

    std::ofstream ofs(fileName);
    if (!ofs)
    {
        std::cout << "ファイルが開けませんでした。" << std::endl;
        std::cin.get();
        return 0;
    }

    //ofs << "あいうえお　かきくけこ" << std::endl;
    ofs << utf8_to_cp("あいうえお漢字hello", 20932) << std::endl;
    std::cout << fileName << "に書き込みました。" << std::endl;

    std::cin.get();
}