#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void getfilevector(const QString& path);

private slots:
    void on_pushButton_select_clicked();
    void on_getfilevector(const QString& path);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
