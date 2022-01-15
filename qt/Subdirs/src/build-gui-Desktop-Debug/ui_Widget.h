/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButtonTest_1;
    QPushButton *pushButtonTest_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(400, 300);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonTest_1 = new QPushButton(Widget);
        pushButtonTest_1->setObjectName(QString::fromUtf8("pushButtonTest_1"));

        gridLayout->addWidget(pushButtonTest_1, 0, 0, 1, 1);

        pushButtonTest_2 = new QPushButton(Widget);
        pushButtonTest_2->setObjectName(QString::fromUtf8("pushButtonTest_2"));

        gridLayout->addWidget(pushButtonTest_2, 0, 1, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Form", nullptr));
        pushButtonTest_1->setText(QApplication::translate("Widget", "Test 1", nullptr));
        pushButtonTest_2->setText(QApplication::translate("Widget", "Test 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
