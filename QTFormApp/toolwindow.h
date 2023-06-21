#ifndef TOOLWINDOW_H
#define TOOLWINDOW_H

#include <QDialog>

namespace Ui {
class ToolWindow;
}

class ToolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ToolWindow(QWidget *parent = nullptr);
    ~ToolWindow();

private:
    Ui::ToolWindow *ui;
};

#endif // TOOLWINDOW_H
