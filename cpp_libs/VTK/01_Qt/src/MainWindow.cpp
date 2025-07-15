#include <MainWindow.h>
#include <ui_MainWindow.h>

#include <QSettings>

#include <defs.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _scViewDefault = std::make_shared<QShortcut>(QKeySequence(Qt::Key_0)            , this, SLOT(on_actionViewDefault_triggered()));
    _scViewTop     = std::make_shared<QShortcut>(QKeySequence(Qt::Key_7)            , this, SLOT(on_actionViewTop_triggered()));
    _scViewBottom  = std::make_shared<QShortcut>(QKeySequence(Qt::CTRL + Qt::Key_7) , this, SLOT(on_actionViewBottom_triggered()));
    _scViewLeft    = std::make_shared<QShortcut>(QKeySequence(Qt::Key_1)            , this, SLOT(on_actionViewLeft_triggered()));
    _scViewRight   = std::make_shared<QShortcut>(QKeySequence(Qt::CTRL + Qt::Key_1) , this, SLOT(on_actionViewRight_triggered()));
    _scViewBack    = std::make_shared<QShortcut>(QKeySequence(Qt::Key_3)            , this, SLOT(on_actionViewBack_triggered()));
    _scViewFront   = std::make_shared<QShortcut>(QKeySequence(Qt::CTRL + Qt::Key_3) , this, SLOT(on_actionViewFront_triggered()));
    _scViewOrtho   = std::make_shared<QShortcut>(QKeySequence(Qt::Key_5)            , this, SLOT(on_actionViewOrtho_triggered()));

    _sim = std::make_shared<Simulation>();

    _vis = std::make_shared<Visualization>();
    _ui->widgetVtk->setRenderWindow(_vis->getRenderWindow());
    _ui->widgetVtk->renderWindow()->AddRenderer(_vis->getRenderer());
    _vis->init();

    settingsRead();

    // 25 fps
    //_timerId = startTimer(1000 / 25);
    _timerId = startTimer(10);
    _timer.start();
}

MainWindow::~MainWindow()
{
    if ( _timerId ) killTimer( _timerId );

    // if ( _sim )
    // {
    //     while ( _sim->isRunning() )
    //     {
    //         _sim->quit();
    //     }
    // }

    settingsSave();
    delete _ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    QMainWindow::timerEvent(event);
    double dt = static_cast<double>(_timer.restart()) / 1000.0;
    double fps = 1.0 / dt;
    _ui->statusbar->showMessage(QString("FPS: %1").arg(fps, 0, 'f', 2));
    _vis->update(_sim->getParticles());
    _ui->widgetVtk->renderWindow()->Render();
    // _ui->widgetVtk->update();
    _sim->update(dt);
}

void MainWindow::settingsRead()
{
    QSettings settings(ORG_NAME, APP_NAME );
    settings.beginGroup("main_window");
    restoreState(settings.value("state").toByteArray());
    restoreGeometry(settings.value("geometry").toByteArray());
    settings.endGroup();
}

void MainWindow::settingsSave()
{
    QSettings settings(ORG_NAME, APP_NAME );
    settings.beginGroup("main_window");
    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}

void MainWindow::on_actionViewDefault_triggered()
{
    _vis->setViewDefault();
}

void MainWindow::on_actionViewTop_triggered()
{
    _vis->setViewTop();
}

void MainWindow::on_actionViewBottom_triggered()
{
    _vis->setViewBottom();
}

void MainWindow::on_actionViewLeft_triggered()
{
    _vis->setViewLeft();
}

void MainWindow::on_actionViewRight_triggered()
{
    _vis->setViewRight();
}

void MainWindow::on_actionViewBack_triggered()
{
    _vis->setViewBack();
}

void MainWindow::on_actionViewFront_triggered()
{
    _vis->setViewFront();
}

void MainWindow::on_actionViewOrtho_triggered()
{
    _vis->toggleViewOrthographic();
}

void MainWindow::on_actionViewPoints_toggled(bool arg1)
{
    _vis->setPointsVisibility(arg1);
}

void MainWindow::on_actionViewSurface_toggled(bool arg1)
{
    _vis->setSurfaceVisibility(arg1);
}
