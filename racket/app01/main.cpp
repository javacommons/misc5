#include <QtCore>
#include <iostream>
#include <filesystem>
#include <map>
#include "../strconv.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "hello!";
    QFile File(QCoreApplication::applicationDirPath() + "/config.cfg");
    qDebug() << File.fileName();
    QFile File2(QCoreApplication::applicationFilePath());
    qDebug() << File2.fileName();

    namespace fs = std::filesystem;
    // 現在の作業ディレクトリを取得
    fs::path p = fs::current_path();
    std::cout << p << std::endl;

    const std::wstring s = p.wstring();
    qDebug() << wide_to_qstr(s);

    // 現在の作業ディレクトリを設定
    fs::current_path(L"/");
    std::cout << fs::current_path() << std::endl;

    std::map<std::string, double> map = {{"a", 123.0}, {"b", 567.8}};
    json j =  map;
    std::cout << j.dump(4) << std::endl;

    return 0;
}
