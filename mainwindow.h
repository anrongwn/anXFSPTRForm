#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QFutureWatcher>
#include "anfiledata.h"

namespace Ui {
class MainWindow;
}

using anFileV = QVector<QString>;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    anFileV getfilevector(const QString &path);
    static anFileData filedata_mapped(const QString &filename);
    static void filedata_reduced(anFileData_v& form, const anFileData& data);
signals:
    void sig_getfilevector(const QString& path);

private slots:
    void on_pushButton_select_clicked();
    void on_getfilevector(const QString& path);
    void on_filev_finished();

private:
    Ui::MainWindow *ui;
    QFutureWatcher<anFileV> * watcher_;
};

#endif // MAINWINDOW_H
