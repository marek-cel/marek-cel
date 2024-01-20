#include "Widget.h"
#include "ui_Widget.h"

#include <QDebug>

#include <Test.h>
#include <test/Test.h>

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
    gui::Test test;

    qDebug() << test.fun( 1, 2 );
}


void Widget::on_pushButtonTest_2_clicked()
{
    test::Test test;

    qDebug() << test.fun( 1, 2 );
}

