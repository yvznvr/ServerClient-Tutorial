#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client.setPort(8080);
    client.createSocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.jpg)"));
    ui->path->setText(fileName);
}

void MainWindow::on_send_clicked()
{
    uint8_t buf[320];
    if(client.isSocketCreated())
    {
        image.setFileName(ui->path->text());
        if(!image.open(QIODevice::ReadOnly)) return;
        int index = 0;
        while(!image.atEnd())
        {
            // I add 6 bytes header front of data
            memcpy(buf, &index, 4);
            index++;
            uint16_t size = image.read((char*)&(buf[6]), 314);
            memcpy(&(buf[4]), &size, sizeof(uint16_t));
            client.sendData(buf);
        }
        memset(buf, 0, 6);
        client.sendData(buf);
    }
}
