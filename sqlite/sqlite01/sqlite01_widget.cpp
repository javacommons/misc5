#include "sqlite01_widget.h"
#include "ui_sqlite01_widget.h"

#include "sqlite01_common.h"

Sqlite01_Widget::Sqlite01_Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sqlite01_Widget)
{
    ui->setupUi(this);
    //this->setFixedSize(400, 200);
    this->resize(400, 200);
}

Sqlite01_Widget::~Sqlite01_Widget()
{
    delete ui;
}

void Sqlite01_Widget::on_open_dialog_button_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "hoge", ".",
                                                    "Text files(*.txt);;All Files(*.*)");
    qDebug() << filename;
    if(filename.isEmpty()) return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) return;
    auto content = file.readAll();
    ui->textBrowser->setText(QString::fromUtf8(content));
}

void Sqlite01_Widget::on_pushButton_clicked()
{
    QFile file("users.yaml");
    if(!file.open(QIODevice::ReadOnly)) return;
    auto content = file.readAll();
    ui->textBrowser->setText(QString::fromUtf8(content));
}
