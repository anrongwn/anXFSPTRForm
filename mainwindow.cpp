#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>
#include <QFuture>
#include <QtConcurrent>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QObject::connect(this, &MainWindow::sig_getfilevector, this, &MainWindow::on_getfilevector);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

anFileV MainWindow::getfilevector(const QString &path)
{
    qDebug()<<"MainWindow::getfilevector(" << path <<"), tid=" << QThread::currentThreadId();
    anFileV result;

    QDir dir(path);
    if (!dir.exists()) return result;

    dir.setFilter(QDir::Files);
    QStringList filters;
    filters << "*.def";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();
    for(auto const & it : list){
        if (it.isFile()){
            //qDebug()<<"(" << it.absoluteFilePath() <<"), tid=" << QThread::currentThreadId();
            result.append(it.absoluteFilePath());
        }
    }

    return result;

}

void MainWindow::on_pushButton_select_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, QString("please ptr form path"), \
                                                     R"(c:\)", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!path.isEmpty()){
        ui->lineEdit_path->setText(path);
    }

    qDebug() << "form path = " << path;
    emit sig_getfilevector(path);
}

void MainWindow::on_getfilevector(const QString &path)
{
    if (path.isEmpty()) return;

    qDebug()<<"MainWindow::on_getfilevector(" << path <<"), tid=" << QThread::currentThreadId();
    QFuture<anFileV> result = QtConcurrent::run(QThreadPool::globalInstance(), this, &MainWindow::getfilevector, path);
    result.waitForFinished();
    anFileV filev = result.result();
    qDebug()<<"MainWindow::on_getfilevector filev = " << filev.size()<< ",tid=" << QThread::currentThreadId() ;







}
