#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ::FreeConsole();
    Widget w;
    w.show();
    return a.exec();
}
