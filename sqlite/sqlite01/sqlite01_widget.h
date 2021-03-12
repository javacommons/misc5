#ifndef SQLITE01_WIDGET_H
#define SQLITE01_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Sqlite01_Widget; }
QT_END_NAMESPACE

class Sqlite01_Widget : public QWidget
{
    Q_OBJECT

public:
    Sqlite01_Widget(QWidget *parent = nullptr);
    ~Sqlite01_Widget();

private slots:
    void on_open_dialog_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Sqlite01_Widget *ui;
};
#endif // SQLITE01_WIDGET_H
