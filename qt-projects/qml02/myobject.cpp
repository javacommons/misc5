#include "myobject.hpp"

MyObject::MyObject(QObject *parent) : QObject(parent)
{
}

void MyObject::func1() {
    qDebug() << u8"func1() called!漢字";
    m_io.printf(u8"func1() called!(2)漢字\n");
    emit func1Called();
}

void MyObject::log(const QString &msg)
{
    m_io.writeln(msg.toStdString().c_str());
}
