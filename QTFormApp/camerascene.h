#ifndef CAMERASCENE_H
#define CAMERASCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "datastructure.h"

class CameraScene : public QGraphicsScene
{
    Q_OBJECT
public:    
    explicit CameraScene(QImage img, QObject *parent = nullptr);
    ~CameraScene();

    enum Mode {NoMode, LBM, RBM};

    void setMode(Mode mode);
    Mode getMode();

    void set3DPoints(Data3DVector points);

    static const int CIRCLE_D = 10;
private:
    QPointF startPoint;
    QPointF endPoint;

    QImage screenshot;
    QGraphicsLineItem* lineItem;
    std::vector<QGraphicsEllipseItem*> circleItems;
    QGraphicsEllipseItem* circleCurrent;

    // QGraphicsEllipseItem* circleStart;
    // QGraphicsEllipseItem* circleEnd;

    Mode sceneMode;

private:
    Data3DVector clusterPoints;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CAMERASCENE_H
