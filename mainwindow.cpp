#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>
#include <QString>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QObject::connect(this, &MainWindow::getfilevector, this, &MainWindow::on_getfilevector);

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
    emit getfilevector(path);
}

void MainWindow::on_getfilevector(const QString &path)
{
    if (path.isEmpty()) return;

    QDir dir(path);
    if (!dir.exists()) return;

    dir.setFilter(QDir::Files);
    QStringList filters;
    filters << "*.def";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();
}
