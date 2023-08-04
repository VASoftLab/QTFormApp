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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ToolWindow
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayoutBtn;
    QListWidget *lswClusters;
    QPushButton *btn2D;
    QPushButton *btn3D;
    QPushButton *btnSave;

    void setupUi(QDialog *ToolWindow)
    {
        if (ToolWindow->objectName().isEmpty())
            ToolWindow->setObjectName(QString::fromUtf8("ToolWindow"));
        ToolWindow->setWindowModality(Qt::ApplicationModal);
        ToolWindow->resize(818, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ToolWindow->sizePolicy().hasHeightForWidth());
        ToolWindow->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(ToolWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        graphicsView = new QGraphicsView(ToolWindow);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMinimumSize(QSize(640, 480));
        graphicsView->setMaximumSize(QSize(640, 480));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout->addWidget(graphicsView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayoutBtn = new QVBoxLayout();
        verticalLayoutBtn->setObjectName(QString::fromUtf8("verticalLayoutBtn"));
        verticalLayoutBtn->setSizeConstraint(QLayout::SetFixedSize);
        lswClusters = new QListWidget(ToolWindow);
        lswClusters->setObjectName(QString::fromUtf8("lswClusters"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lswClusters->sizePolicy().hasHeightForWidth());
        lswClusters->setSizePolicy(sizePolicy2);
        lswClusters->setMinimumSize(QSize(150, 0));
        lswClusters->setMaximumSize(QSize(150, 16777215));

        verticalLayoutBtn->addWidget(lswClusters);

        btn2D = new QPushButton(ToolWindow);
        btn2D->setObjectName(QString::fromUtf8("btn2D"));
        sizePolicy1.setHeightForWidth(btn2D->sizePolicy().hasHeightForWidth());
        btn2D->setSizePolicy(sizePolicy1);
        btn2D->setMinimumSize(QSize(150, 60));
        btn2D->setMaximumSize(QSize(150, 60));

        verticalLayoutBtn->addWidget(btn2D);

        btn3D = new QPushButton(ToolWindow);
        btn3D->setObjectName(QString::fromUtf8("btn3D"));
        sizePolicy1.setHeightForWidth(btn3D->sizePolicy().hasHeightForWidth());
        btn3D->setSizePolicy(sizePolicy1);
        btn3D->setMinimumSize(QSize(150, 60));
        btn3D->setMaximumSize(QSize(150, 60));

        verticalLayoutBtn->addWidget(btn3D);

        btnSave = new QPushButton(ToolWindow);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        sizePolicy1.setHeightForWidth(btnSave->sizePolicy().hasHeightForWidth());
        btnSave->setSizePolicy(sizePolicy1);
        btnSave->setMinimumSize(QSize(150, 40));
        btnSave->setMaximumSize(QSize(40, 16777215));

        verticalLayoutBtn->addWidget(btnSave);


        gridLayout->addLayout(verticalLayoutBtn, 0, 1, 1, 1);


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
