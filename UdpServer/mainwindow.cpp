#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    server.setPort(8080);
    if(server.createSocket())
    {
        server.start();
    }
    connect(&server, SIGNAL(recvData(uint8_t*)), this, SLOT(recvData(uint8_t*)));
    imageList = new QList<QFile*>();
}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i=0; imageList->size(); i++)
    {
        delete imageList->at(i);
    }
    delete imageList;
}

void MainWindow::recvData(uint8_t *data)
{
    QFile *file;
    if(!imageList->isEmpty() && imageList->last()->isOpen())
    {
        file = imageList->last();
    }
    uint8_t success[6] = {0,0,0,0,0,0};
    int tempIndex;
    memcpy(&tempIndex, data, 4);
    uint16_t dataSize;
    memcpy(&dataSize,&(data[4]), 2);
    if(data[0] == 0 && data[1] == 0 && data[2] == 0 &&
            data[3] == 0 && data[4] == 0 && data[5] == 0)
    {
        // all image recieved
        index = 0;
        server.sendData(success);
        file->close();
        showImage();
    }
    else if(tempIndex == index)
    {
        if(tempIndex == 0)
        {
            QString a = QDir::tempPath();
            file = new QFile(QDir::tempPath() + QDir::separator() +
                             QString::number(imageList->size())  + ".jpeg");
            file->open(QIODevice::WriteOnly);
            imageList->append(file);
        }
        // packet recieved
        file->write((const char *)&(data[6]), dataSize);
        qDebug() << tempIndex;
        server.sendData(success);
        index++;
    }
}

void MainWindow::showImage()
{
    QLabel *label = new QLabel(ui->tabWidget);
    QPixmap pixmap(imageList->last()->fileName());
    label->setPixmap(pixmap);
    label->setScaledContents(true);
    label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->tabWidget->insertTab(imageList->size(), label, QString::number(imageList->size()));
    label->show();
    ui->tabWidget->setCurrentIndex(imageList->size()-1);
}
