#include "dll01.h"

#include <QtCore>
#include "strconvQt.h"

int dummy = 0;
QCoreApplication a(dummy, nullptr);

Dll01::Dll01()
{
    QString app_dir = qApp->applicationDirPath();
}

const char *get_app_dir()
{
    static thread_local std::string app_dir;
    app_dir = qstr_to_utf8(qApp->applicationDirPath());
    return app_dir.c_str();
}
