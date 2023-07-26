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
        if (lineItemAdded)
        {
            this->removeItem(lineItem);
            lineItemAdded = false;
        }
        delete lineItem;
    }

    if (circleCurrent != nullptr)
    {
        if (circleCurrentAdded)
        {
            this->removeItem(circleCurrent);
            circleCurrentAdded = false;
        }
        delete circleCurrent;
    }

    if (circleStart != nullptr)
    {
        if (circleStartAdded)
        {
            this->removeItem(circleStart);
            circleStartAdded = false;
        }
        delete circleStart;
    }

    if (circleEnd != nullptr)
    {
        if (circleEndAdded)
        {
            this->removeItem(circleEnd);
            circleEndAdded = false;
        }
        delete circleEnd;
    }
}

void CameraScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CameraScene::Mode currentMode = getMode();

    startPoint = event->scenePos();
    endPoint = event->scenePos();

    if (event->buttons() & Qt::LeftButton)
    {
        // Начало отрисовки (первое нажатие ЛКМ)
        if ((currentMode == Mode::Undefined) ||
            (currentMode == Mode::RightButton))
        {
            if (circleStart != nullptr)
            {
                if (circleStartAdded)
                {
                    this->removeItem(circleStart);
                    circleStartAdded = false;
                }
            }

            if (circleEnd != nullptr)
            {
                if (circleEndAdded)
                {
                    this->removeItem(circleEnd);
                    circleEndAdded = false;
                }
            }

            if (lineItem == nullptr)
            {                
                lineItem = new QGraphicsLineItem();
                lineItem->setPen(QPen(Qt::white, 2, Qt::SolidLine));
            }

            if (lineItem != nullptr)
            {
                lineItem->setLine(0, 0,
                              endPoint.x() - startPoint.x(),
                              endPoint.y() - startPoint.y());
                lineItem->setPos(startPoint);

                if (!lineItemAdded)
                {
                    this->addItem(lineItem);
                    lineItemAdded = true;
                }
            }

            createCircleStart(circleCurrent->rect()); // Создаем первую точку
            setMode(Mode::LeftButton); // Устанавливаем режим
        }

        // Окончание отрисовки (второе нажатие ЛКМ)
        if (currentMode == Mode::LeftButton)
        {
            createCircleEnd(circleCurrent->rect()); // Создаем вторую точку
            setMode(Mode::Undefined); // Сброс режима
        }

    }
    else if (event->buttons() & Qt::RightButton)
    {
        removeRule(); // Удаляем текущую линейку (точки, линия, метка)
        setMode(Mode::RightButton);
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
            {
                if (circleCurrentAdded)
                    this->removeItem(circleCurrent);
                circleCurrentAdded = false;
            }


            // Если ранее точка не была обнаружена,
            // создаем объект и задаем характеристики
            if (circleCurrent == nullptr)
            {
                circleCurrent = new QGraphicsEllipseItem();
                circleCurrent->setPen(QPen(Qt::red, 1, Qt::SolidLine));
            }

            // Add real XY from 3D cloud data structure
            circleCurrent->setRect(clusterPoints.vu.at(i).at(0) - CIRCLE_D / 2,
                                   clusterPoints.vu.at(i).at(1) - CIRCLE_D / 2,
                                   CIRCLE_D, CIRCLE_D);
            this->addItem(circleCurrent);
            circleCurrentAdded = true;

            circleFound = true;
            break;
        }        
    }

    if ((!circleFound) && (circleCurrent != nullptr))
    {
        if (circleCurrentAdded)
            this->removeItem(circleCurrent);
        circleCurrentAdded = false;
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
        elipse->setRect(points.vu.at(i).at(0) - CIRCLE_D / 2,
                        points.vu.at(i).at(1) - CIRCLE_D / 2,
                        CIRCLE_D, CIRCLE_D);
        circleItems.push_back(elipse);
        this->addItem(elipse);

        clusterPoints.cluster.push_back(points.cluster.at(i));
        clusterPoints.rgb.push_back(points.rgb.at(i));
        clusterPoints.vu.push_back(points.vu.at(i));
        clusterPoints.xyz.push_back(points.xyz.at(i));
    }
}

void CameraScene::createCircleStart(QRectF rect)
{
    if (circleStart == nullptr)
    {
        circleStart = new QGraphicsEllipseItem();
        circleStart->setPen(QPen(Qt::red, 2, Qt::SolidLine));
    }
    circleStart->setRect(rect);
    if (!circleStartAdded)
    {
        this->addItem(circleStart);
        circleStartAdded = true;
    }
}
void CameraScene::createCircleEnd(QRectF rect)
{
    if (circleEnd == nullptr)
    {
        circleEnd = new QGraphicsEllipseItem();
        circleEnd->setPen(QPen(Qt::red, 2, Qt::SolidLine));
    }
    circleEnd->setRect(rect);
    if (!circleEndAdded)
    {
        this->addItem(circleEnd);
        circleEndAdded = true;
    }
}
void CameraScene::removeRule()
{
    if (circleStart != nullptr)
    {
        if (circleStartAdded)
        {
            this->removeItem(circleStart);
            circleStartAdded = false;
        }
    }

    if (circleEnd != nullptr)
    {
        if (circleEndAdded)
        {
            this->removeItem(circleEnd);
            circleEndAdded = false;
        }
    }

    if (lineItem != nullptr)
    {
        if (lineItemAdded)
        {
            this->removeItem(lineItem);
            lineItemAdded = false;
        }
    }
}
