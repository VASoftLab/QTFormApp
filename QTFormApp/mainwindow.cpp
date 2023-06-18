#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), webcam(0)
{
    setFixedSize(660, 560);
    ui->setupUi(this);

    // Border around the label
    ui->lblCamera->setStyleSheet("QLabel {"
                                 "border-style: solid;"
                                 "border-width: 1px;"
                                 "border-color: black; "
                                 "}");

    // Check the webcam connection
    if (!webcam.isOpened())
        ui->lblCamera->setText("ERROR: Can't create webcam connection");
    else
    {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
        timer->start(50);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePicture()
{
    webcam.read(source);

    if (source.empty())
        return;

    // Img preprocessing
    cv::cvtColor(source, destination, cv::COLOR_BGR2RGB);
    imgcam = QImage((uchar*) destination.data, destination.cols, destination.rows, destination.step, QImage::Format_RGB888);

    // Show QImage using QLabel
    ui->lblCamera->setPixmap(QPixmap::fromImage(imgcam));
}

