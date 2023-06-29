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
