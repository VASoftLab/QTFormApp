#include "toolwindow.h"
#include "ui_toolwindow.h"
#include <QListWidgetItem>
#include <QRadioButton>
#include <QGraphicsPixmapItem>

ToolWindow::ToolWindow(cv::Mat image, Data3DVector data, QWidget *parent) :
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

    // Check the source image
    if (image.empty())
        return;

    // Image copy
    source = image.clone();

    // Data copy
    points = data;
    std::vector<int> clusterIDs = getClusterIDs(points);

    // Image preprocessing
    cv::cvtColor(source, destination, cv::COLOR_BGR2RGB);
    imgcam = QImage((uchar*) destination.data,
                    destination.cols,
                    destination.rows,
                    destination.step,
                    QImage::Format_RGB888);

    // Checkbox list generationi
    for (int i : clusterIDs)
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
            new QRadioButton("Claster " + QString::number(i)));
    }

    // Check the first item
    if (ui->lswClusters->count() > 0)
    {
        auto firstItem =
            static_cast<QRadioButton*>(
                ui->lswClusters->itemWidget(ui->lswClusters->item(0)));
        firstItem->setChecked(true);
    }

    cameraScene = new CameraScene(imgcam);
    ui->graphicsView->setScene(cameraScene);
}

ToolWindow::~ToolWindow()
{
    delete cameraScene;
    delete ui;
}

std::vector<int> ToolWindow::getClusterIDs(Data3DVector points)
{
    std::vector<int> clusterIDs = points.cluster;
    std::vector<int>::iterator it;
    std::sort(clusterIDs.begin(), clusterIDs.end());

    it = std::unique(clusterIDs.begin(), clusterIDs.end());
    clusterIDs.resize(std::distance(clusterIDs.begin(), it));

    return clusterIDs;
}