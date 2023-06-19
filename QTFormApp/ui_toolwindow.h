/********************************************************************************
** Form generated from reading UI file 'toolwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLWINDOW_H
#define UI_TOOLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ToolWindow
{
public:
    QLabel *lblScreenshot;

    void setupUi(QDialog *ToolWindow)
    {
        if (ToolWindow->objectName().isEmpty())
            ToolWindow->setObjectName(QString::fromUtf8("ToolWindow"));
        ToolWindow->resize(660, 500);
        lblScreenshot = new QLabel(ToolWindow);
        lblScreenshot->setObjectName(QString::fromUtf8("lblScreenshot"));
        lblScreenshot->setGeometry(QRect(10, 10, 640, 480));
        lblScreenshot->setAlignment(Qt::AlignCenter);

        retranslateUi(ToolWindow);

        QMetaObject::connectSlotsByName(ToolWindow);
    } // setupUi

    void retranslateUi(QDialog *ToolWindow)
    {
        ToolWindow->setWindowTitle(QCoreApplication::translate("ToolWindow", "Tool Window", nullptr));
        lblScreenshot->setText(QCoreApplication::translate("ToolWindow", "SCREENSHOT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToolWindow: public Ui_ToolWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLWINDOW_H
