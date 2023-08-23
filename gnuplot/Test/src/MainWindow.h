#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MyAction.h"
#include "MyDockWidget.h"
#include "MyMenu.h"
#include "MyShortcut.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    MyAction*     myAction;
    MyDockWidget* myDockWidget;
    MyMenu*       myMenu;
    MyShortcut*   myShortcut;

private slots:

    void displayMessageAction();
    void displayMessageShortcut();
};

#endif // MAINWINDOW_H
