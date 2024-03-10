#include "CollapsableWidget.h"
#include "ui_CollapsableWidget.h"

CollapsableWidget::CollapsableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollapsableWidget)
{
    ui->setupUi(this);
}

CollapsableWidget::~CollapsableWidget()
{
    delete ui;
}

void CollapsableWidget::setContents(QWidget* contents)
{
    if ( contents )
    {
        QWidget* widget = ui->widget;
        ui->gridLayout->removeWidget(ui->widget);
        delete widget;
        ui->gridLayout->addWidget(contents, 1, 0, 1, 1);
    }
}

void CollapsableWidget::on_toolButton_toggled(bool checked)
{
    ui->toolButton->setArrowType(!checked ? Qt::ArrowType::RightArrow : Qt::ArrowType::DownArrow);
    ui->widget->setHidden(!checked);
}

