#include "myobject.hpp"

MyObject::MyObject(QObject *parent) : QObject(parent)
{
}

void MyObject::func1() {
    qDebug() << "func1() called!";
    m_io.printf("func1() called!(2)\n");
    emit func1Called();
}
