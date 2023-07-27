#ifndef TOOLWINDOW_H
#define TOOLWINDOW_H

#include <QDialog>

#include "camerascene.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "datastructure.h"

#include <algorithm>
#include <iterator>

namespace Ui {
class ToolWindow;
}

class ToolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ToolWindow(cv::Mat image, Data3DVector data, QWidget *parent = nullptr);
    ~ToolWindow();

private slots:
    void on_lswClusters_itemSelectionChanged();

    void on_btn2D_clicked();

    void on_btn3D_clicked();

private:
    Ui::ToolWindow *ui;    
    cv::Mat source;
    cv::Mat destination;
    QImage imgcam;    
    Data3DVector allPoints;
    Data3DVector clusterPoints;


    std::vector<int> getClusterIDs(Data3DVector points);

    CameraScene *cameraScene;
};

#endif // TOOLWINDOW_H
