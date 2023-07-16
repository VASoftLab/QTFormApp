#include "camerascene.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>

CameraScene::CameraScene(QImage img, QObject *parent)
    : QGraphicsScene{parent}
{
    if (!img.isNull())
    {
        screenshot = img.copy();

        // Add Image
        QPixmap img = QPixmap::fromImage(screenshot);
        QGraphicsPixmapItem* item =
            new QGraphicsPixmapItem(img);

        this->addItem(item);

        // Add Line
        lineItem = new QGraphicsLineItem();
        lineItem->setPen(QPen(Qt::white, 2, Qt::SolidLine));
        this->addItem(lineItem);
    }
}

CameraScene::~CameraScene()
{
    this->removeItem(lineItem);
    delete lineItem;
}

void CameraScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // TODO: Line drawing should be optimized

    if (event->buttons() & Qt::LeftButton)
    {
        startPoint = event->scenePos();
        endPoint = event->scenePos();

        lineItem->setLine(0, 0,
                          endPoint.x() - startPoint.x(),
                          endPoint.y() - startPoint.y());

        lineItem->setPos(startPoint);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        startPoint = event->scenePos();
        endPoint = event->scenePos();

        lineItem->setLine(0, 0,
                          endPoint.x() - startPoint.x(),
                          endPoint.y() - startPoint.y());
    }

    QGraphicsScene::mousePressEvent(event);
}

void CameraScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    endPoint = event->scenePos();

    // TODO: Line drawing should be optimized
    if (lineItem != nullptr)
    {
        lineItem->setLine(0, 0,
                          endPoint.x() - startPoint.x(),
                          endPoint.y() - startPoint.y());
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void CameraScene::setMode(Mode mode)
{
    sceneMode = mode;
}

void CameraScene::set3DPoints(Data3DVector points)
{
    clusterPoints.cluster.clear();
    clusterPoints.rgb.clear();
    clusterPoints.vu.clear();
    clusterPoints.xyz.clear();

    // Clear old circles data
    for (size_t i = 0; i < circleItems.size(); i++)
    {
        // Remove the circle form scene
        this->removeItem(circleItems.at(i));

        // Free memory (circle object in vector)
        delete circleItems.at(i);
    }

    // Clear vector of items
    circleItems.clear();

    // Create new circle items
    for (size_t i = 0; i < points.cluster.size(); i++)
    {
        auto elipse = new QGraphicsEllipseItem();
        elipse->setPen(QPen(Qt::red, 1, Qt::SolidLine));
        elipse->setRect(0 + i*5, 0 + i*5, CIRCLE_D, CIRCLE_D);
        circleItems.push_back(elipse);
        this->addItem(elipse);
    }
}
