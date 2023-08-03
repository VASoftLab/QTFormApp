#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toolwindow.h"

#include <QFileDialog>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), webcam(0)
{
    setFixedSize(660, 560);
    ui->setupUi(this);
    // Центрируем окно в пределах экрана
    move(screen()->geometry().center() - frameGeometry().center());

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
        timer->start(100);
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

    // Image preprocessing
    cv::cvtColor(source, destination, cv::COLOR_BGR2RGB);
    imgcam = QImage((uchar*) destination.data,
                    destination.cols,
                    destination.rows,
                    destination.step,
                    QImage::Format_RGB888);

    // Show QImage using QLabel
    ui->lblCamera->setPixmap(QPixmap::fromImage(imgcam));
}

Data3DVector MainWindow:: getData(int rows, int cols, bool norm = true)
{
    Data3DVector data;

    // Путь к папке с данными
    auto dataPath = QDir::cleanPath(qApp->applicationDirPath() + QDir::separator() + "data");
    // qDebug() << "Data path : " << dataPath;

    // Чтение данных
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"), dataPath, tr("TXT Files (*.txt)"));
    QFile file(fileName);
    QStringList lineData;
    Data3DItem data3DItem;

    int vuX;
    int vuY;
    double xyzX;
    double xyzY;
    double xyzZ;
    int rgbR;
    int rgbG;
    int rgbB;
    int clst;

    int Xmin = INT_MAX;
    int Xmax = INT_MIN;
    int Ymin = INT_MAX;
    int Ymax = INT_MIN;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {

            // Строка данных
            lineData = in.readLine().split("\t");

            // Парсинг
            vuX = lineData[0].trimmed().toInt();
            vuY = lineData[1].trimmed().toInt();

            if (vuX > Xmax)
                Xmax = vuX;
            if (vuX < Xmin)
                Xmin = vuX;

            if (vuY > Ymax)
                Ymax = vuY;
            if (vuY < Ymin)
                Ymin = vuY;

            xyzX = lineData[2].trimmed().toDouble();
            xyzY = lineData[3].trimmed().toDouble();
            xyzZ = lineData[4].trimmed().toDouble();

            rgbR = lineData[5].trimmed().toInt();
            rgbG = lineData[6].trimmed().toInt();
            rgbB = lineData[7].trimmed().toInt();

            clst = lineData[8].trimmed().toInt();

            // Очистка структуры
            data3DItem.vu.clear();
            data3DItem.vu.clear();

            data3DItem.xyz.clear();
            data3DItem.xyz.clear();
            data3DItem.xyz.clear();

            data3DItem.rgb.clear();
            data3DItem.rgb.clear();
            data3DItem.rgb.clear();

            // Заполнение структуры
            data3DItem.vu.push_back(vuX);
            data3DItem.vu.push_back(vuY);

            data3DItem.xyz.push_back(xyzX);
            data3DItem.xyz.push_back(xyzY);
            data3DItem.xyz.push_back(xyzZ);

            data3DItem.rgb.push_back(rgbR);
            data3DItem.rgb.push_back(rgbG);
            data3DItem.rgb.push_back(rgbB);

            data3DItem.cluster = clst;

            // Накопление данных
            data.vu.push_back(data3DItem.vu);
            data.xyz.push_back(data3DItem.xyz);
            data.rgb.push_back(data3DItem.rgb);
            data.cluster.push_back(data3DItem.cluster);
        }

        if (norm)
        {
            for (size_t i = 0; i < data.vu.size(); i++)
            {
                if (Xmax != Xmin)
                    data.vu.at(i).at(0) = cols * (data.vu.at(i).at(0) - Xmin) / (Xmax - Xmin);
                if (Ymax != Ymin)
                    data.vu.at(i).at(1) = rows * (data.vu.at(i).at(1) - Ymin) / (Ymax - Ymin);
            }
        }
    }

    return data;
}

void MainWindow::on_btnScreenshot_clicked()
{
    // Get current Image from camera
    cv::Mat image_original;
    webcam.read(image_original);
    cv::Mat image;
    // VA 31-07-2023: Это временный костыль.
    // Размер изображения на панели инструментов (и сама панель)
    // должны изменять свой размер автоматически
    cv::resize(image_original, image, cv::Size(640, 480), 0, 0, cv::INTER_LINEAR);

    // Массив данных описывающий облоко 3D точек
    Data3DVector data = getData(image.rows, image.cols);

    // Show tool window
    ToolWindow *toolWindow = new ToolWindow(image, data, this);
    toolWindow->exec();
    delete toolWindow;
}

