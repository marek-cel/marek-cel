#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>

#include "TreeModel.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui {
class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //TreeModel treeModel;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
