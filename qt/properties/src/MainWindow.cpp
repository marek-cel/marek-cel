#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( this, SIGNAL(varChanged(int)), this, SLOT(onVar_changed(int)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    setVar( 2 );
    std::cout << _var << std::endl;
}

void MainWindow::onVar_changed(int var)
{
    std::cout << "var= " << var << std::endl;
}
