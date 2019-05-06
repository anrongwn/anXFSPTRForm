#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>
#include <QFuture>

#include <QtConcurrent>
#include "anfile_mapreduce.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(this, &MainWindow::sig_getfilevector, this, &MainWindow::on_getfilevector);

    watcher_ = new QFutureWatcher<anFileV>(this);
    QObject::connect(watcher_, &QFutureWatcher<anFileV>::finished, this, &MainWindow::on_filev_finished);

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

anFileData MainWindow::filedata_mapped(const QString &filename)
{
    anFileData fd;
    fd.setFileName(filename);

    QFile f(filename);
    if (f.open(QIODevice::ReadOnly)){
        fd.push_data(f.readAll());
    }
    f.close();

    //qDebug()<<"MainWindow::filedata_mapped(" << filename <<"), tid=" << QThread::currentThreadId();
    return fd;
}

void MainWindow::filedata_reduced(anFileData_v &form, const anFileData &data)
{
    form.push_back(data);

    //qDebug()<<"MainWindow::filedata_reduced(), tid=" << QThread::currentThreadId();
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
    watcher_->setFuture(result);

}

void MainWindow::on_filev_finished()
{
    anFileV filev = watcher_->result();
    qDebug()<<"MainWindow::on_filev_finished filev = " << filev.size()<< ",tid=" << QThread::currentThreadId() ;

    /*//
    QFuture<anFileData_v> result = QtConcurrent::mappedReduced(filev, mapped(), reduced(), \
                                                               QtConcurrent::OrderedReduce|QtConcurrent::SequentialReduce);
                                                               */
/*//
    auto fn1 = [](const QString& filename)->anFileData{
        anFileData fd;
        fd.setFileName(filename);

        QFile f(filename);
        if (f.open(QIODevice::ReadOnly)){
            fd.push_data(f.readAll());
        }
        f.close();

        //qDebug()<<"MainWindow::filedata_mapped(" << filename <<"), tid=" << QThread::currentThreadId();
        return fd;
    };

    auto fn2 = [&](anFileData_v &form, const anFileData &data){
        form.push_back(data);
    };


    QFuture<anFileData_v> result = QtConcurrent::mappedReduced(filev, fn1, fn2, \
                                                               QtConcurrent::OrderedReduce|QtConcurrent::SequentialReduce);
                                                               */



    QFuture<anFileData_v> result = QtConcurrent::mappedReduced(filev, MainWindow::filedata_mapped, MainWindow::filedata_reduced, \
                                                               QtConcurrent::OrderedReduce|QtConcurrent::SequentialReduce);

    result.waitForFinished();

    anFileData_v form = result.result();
    qDebug()<<"MainWindow::on_filev_finished form = " << form.size()<< ",tid=" << QThread::currentThreadId() ;

}
