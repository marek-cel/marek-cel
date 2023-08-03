#ifndef MYDOCKWIDGET_H
#define MYDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class MyDockWidget;
}

class MyDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit MyDockWidget(QWidget *parent = nullptr);
    ~MyDockWidget();

private:
    Ui::MyDockWidget *ui;
};

#endif // MYDOCKWIDGET_H
