#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>


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
signals:
    void sig_getfilevector(const QString& path);

private slots:
    void on_pushButton_select_clicked();
    void on_getfilevector(const QString& path);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
