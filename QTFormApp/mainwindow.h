#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "datastructure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    cv::VideoCapture webcam;
    cv::Mat source;
    cv::Mat destination;
    QImage imgcam;

    t_vuxyzrgb getData(int rows, int cols, bool norm);

public slots:
    void updatePicture();

private slots:
    void on_btnScreenshot_clicked();
};
#endif // MAINWINDOW_H
