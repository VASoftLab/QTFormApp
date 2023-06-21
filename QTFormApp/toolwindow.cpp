#include "toolwindow.h"
#include "ui_toolwindow.h"

ToolWindow::ToolWindow(cv::Mat image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolWindow)
{
    ui->setupUi(this);

    // Border around the label
    ui->lblScreenshot->setStyleSheet("QLabel {"
                                     "border-style: solid;"
                                     "border-width: 1px;"
                                     "border-color: black; "
                                     "}");

    if (image.empty())
        return;

    // Image copy
    source = image.clone();

    auto rowscount = image.rows;
    auto colscount = image.cols;

    // Image preprocessing
    cv::cvtColor(source, destination, cv::COLOR_BGR2RGB);
    imgcam = QImage((uchar*) destination.data,
                    destination.cols,
                    destination.rows,
                    destination.step,
                    QImage::Format_RGB888);

    // Show QImage using QLabel
    ui->lblScreenshot->setPixmap(QPixmap::fromImage(imgcam));
}

ToolWindow::~ToolWindow()
{
    delete ui;
}
