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
    allPoints = data;
    // Get unique clusters IDs
    std::vector<int> clusterIDs = getClusterIDs(allPoints);


    // Image preprocessing
    cv::cvtColor(source, destination, cv::COLOR_BGR2RGB);
    imgcam = QImage((uchar*) destination.data,
                    destination.cols,
                    destination.rows,
                    destination.step,
                    QImage::Format_RGB888);

    cameraScene = new CameraScene(imgcam);
    ui->graphicsView->setScene(cameraScene);
    // https://stackoverflow.com/questions/7772080/tracking-mouse-move-in-qgraphicsscene-class
    ui->graphicsView->setMouseTracking(true);

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
            new QRadioButton(QString("Cluster %1").arg(i)));
    }

    // Check the first item
    if (ui->lswClusters->count() > 0)
    {
        auto firstItem =
            static_cast<QRadioButton*>(
                ui->lswClusters->itemWidget(ui->lswClusters->item(0)));
        firstItem->setChecked(true);

        ui->lswClusters->item(0)->setSelected(true);
    }

    // Создаем объекты для работы с 3D-графиком
    graph3D = new Q3DScatter();
    series3D = new QScatter3DSeries();

    graph3D->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    graph3D->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    graph3D->addSeries(series3D);

    container3D = QWidget::createWindowContainer(graph3D);

    // Установка темы
    Q3DTheme *currentTheme = graph3D->activeTheme();
    currentTheme->setBackgroundEnabled(false);
    currentTheme->setType(Q3DTheme::ThemeArmyBlue);

    setMode(ToolMode::Mode2D);
}

ToolWindow::~ToolWindow()
{
    delete cameraScene;

    delete series3D;
    delete graph3D;
    delete container3D;

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

void ToolWindow::on_lswClusters_itemSelectionChanged()
{
    auto selectedItem = static_cast<QRadioButton*>(
        ui->lswClusters->itemWidget(ui->lswClusters->selectedItems().first()));
    QString seletedText = selectedItem->text();
    int ID = seletedText.remove("Cluster ").toInt();

    // Remove old data
    clusterPoints.cluster.clear();
    clusterPoints.rgb.clear();
    clusterPoints.vu.clear();
    clusterPoints.xyz.clear();

    // Filter only selected cluster data
    for (size_t i = 0; i < allPoints.cluster.size(); i++)
    {
        if (allPoints.cluster.at(i) == ID)
        {
            clusterPoints.cluster.push_back(allPoints.cluster.at(i));
            clusterPoints.rgb.push_back(allPoints.rgb.at(i));
            clusterPoints.vu.push_back(allPoints.vu.at(i));
            clusterPoints.xyz.push_back(allPoints.xyz.at(i));
        }
    }

    // Debug Information
    qDebug() << "Selected Cluster ID: " << ID << "(" << clusterPoints.cluster.size() << "/" << allPoints.cluster.size() << ")";

    cameraScene->removeRule(); // Удаляем старую линейку (если была создана)
    cameraScene->set3DPoints(clusterPoints);
}

void ToolWindow::on_btn2D_clicked()
{
    if (getMode() == ToolWindow::Mode3D)
    {
        container3D->setVisible(false);
        ui->graphicsView->setVisible(true);

        ui->verticalLayout->removeWidget(container3D);
        ui->verticalLayout->addWidget(ui->graphicsView);

        setMode(ToolMode::Mode2D);
    }
}


void ToolWindow::on_btn3D_clicked()
{
    if (getMode() == ToolWindow::Mode2D)
    {
        // Удалить старые точки
        series3D->dataProxy()->removeItems(0, series3D->dataProxy()->itemCount());

        // Получить новые точки
        QScatterDataArray data;
        for (size_t i = 0; i < clusterPoints.cluster.size(); i++)
        {
            data << QVector3D(clusterPoints.xyz.at(i).at(0),
                              clusterPoints.xyz.at(i).at(1),
                              clusterPoints.xyz.at(i).at(2));
        }

        // Передать точки в объект Series
        series3D->dataProxy()->addItems(data);

        ui->graphicsView->setVisible(false);
        container3D->setVisible(true);

        ui->verticalLayout->removeWidget(ui->graphicsView);
        ui->verticalLayout->addWidget(container3D);

        setMode(ToolMode::Mode3D);
    }
}

void ToolWindow::setMode(ToolMode mode)
{
    toolMode = mode;
}
ToolWindow::ToolMode ToolWindow::getMode()
{
    return toolMode;
}
