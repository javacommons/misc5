#ifndef MYOBJECT_HPP
#define MYOBJECT_HPP

#include <QtCore>
#include <QtQml>

class MyObject : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MyObject(QObject *parent = nullptr);
    Q_INVOKABLE void func1();

signals:

};

#endif // MYOBJECT_HPP
