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

    static const int CIRCLE_D = 10;
    enum Mode {Undefined, LeftButton, RightButton};

    void setMode(Mode mode);
    Mode getMode();

    void set3DPoints(Data3DVector points);
    void removeRule();

private:
    QPointF startPoint;
    QPointF endPoint;
    QImage screenshot;

    QGraphicsLineItem* lineItem;
    std::vector<QGraphicsEllipseItem*> circleItems;
    QGraphicsEllipseItem* circleCurrent;
    QGraphicsEllipseItem* circleStart;
    QGraphicsEllipseItem* circleEnd;

    // TODO: Использование данного флага - костыль.
    // Подумать как оптимизировать
    bool lineItemAdded = false;
    bool circleCurrentAdded = false;
    bool circleStartAdded = false;
    bool circleEndAdded = false;

    Mode sceneMode;
    Data3DVector clusterPoints;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void createCircleStart(QRectF rect);
    void createCircleEnd(QRectF rect);
};

#endif // CAMERASCENE_H
