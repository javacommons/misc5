#include "dialog.h"
#include "ui_dialog.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_destinationButton_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory("C:/root");
#if 0x0
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.setOption(QFileDialog::ShowDirsOnly, false);
#endif
    if(dialog.exec()==QDialog::Accepted) {
        qDebug() << dialog.directory().path();
        ui->destinationEdit->setText(dialog.directory().path());
        QSettings settings;
        settings.setValue("destinationDir", dialog.directory().path());
        qDebug() << "destinationDir" << settings.value("destinationDir");
        qDebug() << settings.fileName();
        qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    }
}
