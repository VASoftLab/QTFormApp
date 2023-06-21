#include "toolwindow.h"
#include "ui_toolwindow.h"

ToolWindow::ToolWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolWindow)
{
    ui->setupUi(this);

    // Border around the label
    ui->lblScreenshot->setStyleSheet("QLabel {"
                                     "border-style: solid;"
                                     "border-width: 1px;"
                                     "border-color: black; "
                                     "}");
}

ToolWindow::~ToolWindow()
{
    delete ui;
}
