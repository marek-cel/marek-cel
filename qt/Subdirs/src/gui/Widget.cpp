#include "Widget.h"
#include "ui_Widget.h"

#include <QDebug>

#include <testlib1/TestLib1.h>
#include <testlib2/TestLib2.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonTest_1_clicked()
{
    TestLib1 test;

    qDebug() << test.fun( 1, 2 );
}


void Widget::on_pushButtonTest_2_clicked()
{
    TestLib2 test;

    qDebug() << test.fun( 1, 2 );
}

