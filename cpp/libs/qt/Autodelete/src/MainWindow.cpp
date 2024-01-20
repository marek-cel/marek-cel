#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myAction =  new MyAction("MyAction", ui->menuMenu);
    connect(myAction, SIGNAL(triggered()), SLOT(displayMessageAction()));
    ui->menuMenu->addAction(myAction);

    myDockWidget = new MyDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, myDockWidget);

    myMenu = new MyMenu(this);

    myShortcut = new MyShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(displayMessageShortcut()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayMessageAction()
{
    QString title = windowTitle();
    QString text = "Menu Action";
    QMessageBox::information(this, title, text);
}

void MainWindow::displayMessageShortcut()
{
    QString title = windowTitle();
    QString text = "Ctrl+S";
    QMessageBox::information(this, title, text);
}
