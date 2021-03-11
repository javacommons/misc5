#include <QtCore>
#include <QtNetwork>
#include <string>
#include "strconvQt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "hello";
    QDirIterator it(".", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        qDebug() << it.next();

        // /etc/.
        // /etc/..
        // /etc/X11
        // /etc/X11/fs
        // ...
    }
    return 0;
}
