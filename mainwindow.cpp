#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_select_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, QString("please ptr form path"), \
                                                     R"(c:\)", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!path.isEmpty()){
        ui->lineEdit_path->setText(path);
    }

    qDebug() << "form path = " << path;
}
