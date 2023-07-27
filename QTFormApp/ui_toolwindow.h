/********************************************************************************
** Form generated from reading UI file 'toolwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLWINDOW_H
#define UI_TOOLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolWindow
{
public:
    QPushButton *btn2D;
    QPushButton *btn3D;
    QPushButton *btnSave;
    QListWidget *lswClusters;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QDialog *ToolWindow)
    {
        if (ToolWindow->objectName().isEmpty())
            ToolWindow->setObjectName(QString::fromUtf8("ToolWindow"));
        ToolWindow->resize(800, 500);
        btn2D = new QPushButton(ToolWindow);
        btn2D->setObjectName(QString::fromUtf8("btn2D"));
        btn2D->setGeometry(QRect(660, 320, 131, 60));
        btn3D = new QPushButton(ToolWindow);
        btn3D->setObjectName(QString::fromUtf8("btn3D"));
        btn3D->setGeometry(QRect(660, 390, 131, 60));
        btnSave = new QPushButton(ToolWindow);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(660, 460, 131, 31));
        lswClusters = new QListWidget(ToolWindow);
        lswClusters->setObjectName(QString::fromUtf8("lswClusters"));
        lswClusters->setGeometry(QRect(660, 10, 131, 301));
        verticalLayoutWidget = new QWidget(ToolWindow);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 642, 482));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(verticalLayoutWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(640, 480));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout->addWidget(graphicsView);


        retranslateUi(ToolWindow);

        QMetaObject::connectSlotsByName(ToolWindow);
    } // setupUi

    void retranslateUi(QDialog *ToolWindow)
    {
        ToolWindow->setWindowTitle(QCoreApplication::translate("ToolWindow", "Tool Window", nullptr));
        btn2D->setText(QString());
        btn3D->setText(QString());
        btnSave->setText(QCoreApplication::translate("ToolWindow", "SAVE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToolWindow: public Ui_ToolWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLWINDOW_H
