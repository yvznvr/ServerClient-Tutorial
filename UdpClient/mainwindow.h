#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <udpclient.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_browse_clicked();

    void on_send_clicked();

private:
    Ui::MainWindow *ui;
    UdpClient client;
    QFile image;
};

#endif // MAINWINDOW_H
