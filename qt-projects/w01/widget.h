#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton1_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
