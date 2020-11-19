#ifndef MYOBJECT_HPP
#define MYOBJECT_HPP

#include <QtCore>
#include <QtQml>
#include "strconv2.hpp"

class MyObject : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    strconv::io m_io;
public:
    explicit MyObject(QObject *parent = nullptr);
    Q_INVOKABLE void func1();
signals:
    void func1Called();
};

#endif // MYOBJECT_HPP
