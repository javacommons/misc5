//#include <QCoreApplication>
#include <QtCore>
#include <QtNetwork>
#include <stdio.h>
#include <gauche.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ScmObj value;

    GC_INIT();
    Scm_Init(GAUCHE_SIGNATURE);

    value = SCM_MAKE_INT(123);
    printf("INTP: %s\n", SCM_INTP(value) ? "true" : "false");
    printf("INT_VALUE: %ld\n", SCM_INT_VALUE(value));

    return 0;
}
