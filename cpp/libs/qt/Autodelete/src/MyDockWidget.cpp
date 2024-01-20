#include "MyDockWidget.h"
#include "ui_MyDockWidget.h"

#include <QDebug>

MyDockWidget::MyDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::MyDockWidget)
{
    ui->setupUi(this);
}

MyDockWidget::~MyDockWidget()
{
    qDebug() << "Deleting MyDockWidget";

    delete ui;
}
