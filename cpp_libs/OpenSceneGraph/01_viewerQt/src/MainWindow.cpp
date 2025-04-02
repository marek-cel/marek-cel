#include <MainWindow.h>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerId = startTimer(17);
}

MainWindow::~MainWindow()
{
    if ( timerId ) killTimer(timerId);
    if ( ui ) { delete ui; } ui = nullptr;
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    ///////////////////////////////
    QMainWindow::timerEvent(event);
    ///////////////////////////////
    ui->widgetCGI->update();
}
