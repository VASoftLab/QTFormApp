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
    }

    lineItem = nullptr;
    circleCurrent = nullptr;
    circleStart = nullptr;
    circleEnd = nullptr;

    setMode(Mode::Undefined);
}

CameraScene::~CameraScene()
{
    if (lineItem != nullptr)
    {
        this->removeItem(lineItem);
        delete lineItem;
    }

    if (circleCurrent != nullptr)
    {
        this->removeItem(circleCurrent);
        delete circleCurrent;
    }

    if (circleStart != nullptr)
    {
        this->removeItem(circleStart);
        delete circleStart;
    }

    if (circleEnd != nullptr)
    {
        this->removeItem(circleEnd);
        delete circleEnd;
    }
}

void CameraScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CameraScene::Mode currentMode = getMode();

    if (event->buttons() & Qt::LeftButton)
    {
        // Начало отрисовки (первое нажатие ЛКМ)
        if ((currentMode == Mode::Undefined) || (currentMode == Mode::RightButton))
        {
            if (circleStart != nullptr)
                this->removeItem(circleStart);
            if (circleEnd != nullptr)
                this->removeItem(circleEnd);

            if (lineItem == nullptr)
            {
                // Add Line
                lineItem = new QGraphicsLineItem();
                lineItem->setPen(QPen(Qt::white, 2, Qt::SolidLine));
            }

            startPoint = event->scenePos();
            endPoint = event->scenePos();

            if (lineItem != nullptr)
            {
                lineItem->setLine(0, 0,
                              endPoint.x() - startPoint.x(),
                              endPoint.y() - startPoint.y());
                lineItem->setPos(startPoint);

                this->addItem(lineItem);
            }

            // Если ранее первая точка не была отрисована, создаем ее
            if (circleStart == nullptr)
            {
                circleStart = new QGraphicsEllipseItem();
                circleStart->setPen(QPen(Qt::red, 2, Qt::SolidLine));
            }
            circleStart->setRect(circleCurrent->rect().x(),
                                 circleCurrent->rect().y(),
                                 circleCurrent->rect().width(),
                                 circleCurrent->rect().height());

            this->addItem(circleStart);

            setMode(Mode::LeftButton);
        }

        // Окончание отрисовки (второе нажатие ЛКМ)
        if (currentMode == Mode::LeftButton)
        {
            // Если ранее вторая точка не была отрисована, создаем ее
            if (circleEnd == nullptr)
            {
                circleEnd = new QGraphicsEllipseItem();
                circleEnd->setPen(QPen(Qt::red, 2, Qt::SolidLine));
            }
            circleEnd->setRect(circleCurrent->rect());
            this->addItem(circleEnd);

            setMode(Mode::Undefined); // Сброс режима
        }

    }
    else if (event->buttons() & Qt::RightButton)
    {
        setMode(Mode::RightButton);
        if (circleStart != nullptr)
            this->removeItem(circleStart);
        if (circleEnd != nullptr)
            this->removeItem(circleEnd);
        if (lineItem != nullptr)
            this->removeItem(lineItem);
    }

    QGraphicsScene::mousePressEvent(event);
}

void CameraScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    CameraScene::Mode currentMode = getMode();
    bool circleFound = false;

    // Получаем конечную текущую точку
    endPoint = event->scenePos();

    // Рисуем линию (если отрисовка линейки начата)
    if ((lineItem != nullptr) && (currentMode == Mode::LeftButton))
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
            // Удаляем предыдущую точку, если такая была найдена ранее
            if (circleCurrent != nullptr)
                this->removeItem(circleCurrent);

            // Если ранее точка не была обнаружена, создаем объект и задаем характеристики
            if (circleCurrent == nullptr)
            {
                circleCurrent = new QGraphicsEllipseItem();
                circleCurrent->setPen(QPen(Qt::red, 1, Qt::SolidLine));
            }

            // Add real XY from 3D cloud data structure
            circleCurrent->setRect(clusterPoints.vu.at(i).at(0) - CIRCLE_D / 2, clusterPoints.vu.at(i).at(1) - CIRCLE_D / 2, CIRCLE_D, CIRCLE_D);
            this->addItem(circleCurrent);

            circleFound = true;
            break;
        }        
    }

    if ((!circleFound) && (circleCurrent != nullptr))
    {
        this->removeItem(circleCurrent);
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
