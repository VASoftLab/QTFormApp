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

    circleCurrent = nullptr;
    setMode(Mode::NoMode);
}

CameraScene::~CameraScene()
{
    this->removeItem(lineItem);
    delete lineItem;

    if (circleCurrent != nullptr)
    {
        this->removeItem(circleCurrent);
        delete circleCurrent;
    }
}

void CameraScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CameraScene::Mode currentMode = getMode();

    if (event->buttons() & Qt::LeftButton)
    {
        // Начало отрисовки
        if ((currentMode == Mode::NoMode) || (currentMode == Mode::RBM))
        {
            startPoint = event->scenePos();
            endPoint = event->scenePos();

            lineItem->setLine(0, 0,
                              endPoint.x() - startPoint.x(),
                              endPoint.y() - startPoint.y());

            lineItem->setPos(startPoint);

            setMode(Mode::LBM);
        }

        // Окончание отрисовки (второе подряд нажатие ЛКМ)
        if (currentMode == Mode::LBM)
        {
            setMode(Mode::NoMode); // Сброс режима
        }

    }
    else if (event->buttons() & Qt::RightButton)
    {
        setMode(Mode::RBM);
    }

    QGraphicsScene::mousePressEvent(event);
}

void CameraScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    CameraScene::Mode currentMode = getMode();

    // Получаем конечную текущую точку
    endPoint = event->scenePos();

    // Рисуем линию (если отрисовка линейки начата)
    if ((lineItem != nullptr) && (currentMode == Mode::LBM))
    {
        lineItem->setLine(0, 0,
                          endPoint.x() - startPoint.x(),
                          endPoint.y() - startPoint.y());
    }

    // Проверяем, попали ли в точку 3D облака
    for (size_t i = 0; i < clusterPoints.cluster.size(); i++)
    {
        if ((endPoint.x() > clusterPoints.vu.at(i).at(0) - CIRCLE_D / 2) &&
            (endPoint.x() < clusterPoints.vu.at(i).at(0) + CIRCLE_D / 2) &&
            (endPoint.y() > clusterPoints.vu.at(i).at(1) - CIRCLE_D / 2) &&
            (endPoint.y() < clusterPoints.vu.at(i).at(1) + CIRCLE_D / 2))
        {
            if (circleCurrent != nullptr)
                this->removeItem(circleCurrent);

            if (circleCurrent == nullptr)
            {
                circleCurrent = new QGraphicsEllipseItem();
                circleCurrent->setPen(QPen(Qt::red, 1, Qt::SolidLine));
            }

            // Add real XY from 3D cloud data structure
            circleCurrent->setRect(clusterPoints.vu.at(i).at(0) - CIRCLE_D / 2, clusterPoints.vu.at(i).at(1) - CIRCLE_D / 2, CIRCLE_D, CIRCLE_D);
            this->addItem(circleCurrent);

            break;
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void CameraScene::setMode(Mode mode)
{
    sceneMode = mode;
}

CameraScene::Mode CameraScene::getMode()
{
    return sceneMode;
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
        elipse->setPen(QPen(Qt::lightGray, 1, Qt::SolidLine));
        // Add real XY from 3D cloud data structure
        elipse->setRect(points.vu.at(i).at(0) - CIRCLE_D / 2, points.vu.at(i).at(1) - CIRCLE_D / 2, CIRCLE_D, CIRCLE_D);
        circleItems.push_back(elipse);
        this->addItem(elipse);

        clusterPoints.cluster.push_back(points.cluster.at(i));
        clusterPoints.rgb.push_back(points.rgb.at(i));
        clusterPoints.vu.push_back(points.vu.at(i));
        clusterPoints.xyz.push_back(points.xyz.at(i));
    }
}
