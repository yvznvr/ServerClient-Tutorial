#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QList>
#include <QDir>
#include <QLabel>
#include <QPixmap>
#include "udpserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void recvData(uint8_t *data);

private:
    Ui::MainWindow *ui;
    UdpServer server;
    QList<QFile*> *imageList;
    int index = 0;
    void showImage();

};

#endif // MAINWINDOW_H
