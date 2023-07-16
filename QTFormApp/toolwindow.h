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

namespace Ui {
class ToolWindow;
}

class ToolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ToolWindow(cv::Mat image, Data3DVector data, QWidget *parent = nullptr);
    ~ToolWindow();

private:
    Ui::ToolWindow *ui;    
    cv::Mat source;
    cv::Mat destination;
    QImage imgcam;

    CameraScene *cameraScene;
};

#endif // TOOLWINDOW_H
