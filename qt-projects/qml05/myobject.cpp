#include "myobject.h"

MyObject::MyObject(QObject *parent) : QObject(parent)
{
}

void MyObject::func1() {
    qDebug() << "func1() called!";
    printf("func1() called!(2)\n"); fflush(stdout);
}
