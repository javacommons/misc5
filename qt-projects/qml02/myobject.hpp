#ifndef MYOBJECT_HPP
#define MYOBJECT_HPP

#include <QtCore>
#include "strconv2.hpp"

class MyObject : public QObject
{
    Q_OBJECT
    strconv::io m_io;
public:
    explicit MyObject(QObject *parent = nullptr);
    Q_INVOKABLE void func1();
    Q_INVOKABLE void log(const QString &msg);
signals:
    void func1Called();
};

#endif // MYOBJECT_HPP
