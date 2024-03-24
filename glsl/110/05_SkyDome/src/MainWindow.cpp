#include <MainWindow.h>
#include <ui_MainWindow.h>

#include <QSettings>

#include <defs.h>
#include <utils.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settingsRead();
    timerId = startTimer(17);
}

MainWindow::~MainWindow()
{
    if ( timerId ) killTimer(timerId);
    settingsSave();
    if ( ui ) { delete ui; } ui = nullptr;
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    ///////////////////////////////
    QMainWindow::timerEvent(event);
    ///////////////////////////////
    
    ui->widgetCGI->update();

    ui->widgetCGI->_sceneRoot->_sunAzim_rad = deg2rad(ui->spinBoxSunAzim->value());
    ui->widgetCGI->_sceneRoot->_sunElev_rad = deg2rad(ui->spinBoxSunElev->value());
}

void MainWindow::settingsRead()
{
    QSettings settings(ORG_NAME, APP_NAME);
    settings.beginGroup("main_window");
    restoreState( settings.value("state").toByteArray() );
    restoreGeometry( settings.value("geometry").toByteArray() );
    settings.endGroup();
}

void MainWindow::settingsSave()
{
    QSettings settings(ORG_NAME, APP_NAME);
    settings.beginGroup("main_window");
    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}
