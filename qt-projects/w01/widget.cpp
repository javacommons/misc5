#include "widget.h"
#include "ui_widget.h"
#include <QtCore>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
    //Qt::ItemDataRole role;
    item->setData(Qt::UserRole, "my-data");
}

void Widget::on_pushButton1_clicked()
{
    qDebug() << u8"clicked!漢字";
    ui->listWidget->addItem("item");
    qDebug() << u8"count:" << ui->listWidget->count();
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    qDebug() << u8"row:" << ui->listWidget->currentRow();
}
