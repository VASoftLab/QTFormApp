#ifndef CAMERASCENE_H
#define CAMERASCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CameraScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CameraScene(QImage img, QObject *parent = nullptr);
    ~CameraScene();

    enum Mode {NoMode, DrawLine};
    void setMode(Mode mode);

private:
    QPointF startPoint;
    QPointF endPoint;

    QImage screenshot;
    QGraphicsLineItem* lineItem;

    Mode sceneMode;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CAMERASCENE_H
