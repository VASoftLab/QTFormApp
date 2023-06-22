#include "toolwindow.h"
#include "ui_toolwindow.h"
#include <QListWidgetItem>
#include <QRadioButton>

ToolWindow::ToolWindow(cv::Mat image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolWindow)
{
    ui->setupUi(this);

    // Set images for buttons
    QPixmap btn2Dimg(":/icons/img/icon-ruler.png");
    QPixmap btn3Dimg(":/icons/img/icon-cube.png");

    QIcon btn2Dico(btn2Dimg);
    QIcon btn3Dico(btn3Dimg);

    ui->btn2D->setIcon(btn2Dico);
    ui->btn2D->setIconSize(btn2Dimg.rect().size());

    ui->btn3D->setIcon(btn3Dico);
    ui->btn3D->setIconSize(btn3Dimg.rect().size());
    // Border around the label
    ui->lblScreenshot->setStyleSheet("QLabel {"
                                     "border-style: solid;"
                                     "border-width: 1px;"
                                     "border-color: black; "
                                     "}");

    // Check the source image
    if (image.empty())
        return;

    // Image copy
    source = image.clone();

    // Image preprocessing
    cv::cvtColor(source, destination, cv::COLOR_BGR2RGB);
    imgcam = QImage((uchar*) destination.data,
                    destination.cols,
                    destination.rows,
                    destination.step,
                    QImage::Format_RGB888);

    // Show QImage using QLabel
    ui->lblScreenshot->setPixmap(QPixmap::fromImage(imgcam));

    // Checkbox list generationi
    for (int i = 0; i < 10; i++)
    {
        // Checkbox List
        // QListWidgetItem *item = new QListWidgetItem;
        // item->setText("Claster " + QString::number(i + 1));
        // item->setCheckState(Qt::Unchecked);
        // ui->lswClusters->addItem(item);

        // Radiobutton list
        QListWidgetItem *item = new QListWidgetItem(ui->lswClusters);
        ui->lswClusters->setItemWidget(
            item,
            new QRadioButton("Claster " + QString::number(i + 1)));
    }

    // Check the first item
    if (ui->lswClusters->count() > 0)
    {
        auto firstItem =
            static_cast<QRadioButton*>(
                ui->lswClusters->itemWidget(ui->lswClusters->item(0)));
        firstItem->setChecked(true);
    }
}

ToolWindow::~ToolWindow()
{
    delete ui;
}
