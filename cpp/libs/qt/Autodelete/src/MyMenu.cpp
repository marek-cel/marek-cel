#include "MyMenu.h"

#include <QDebug>

MyMenu::MyMenu(QWidget *parent)
    : QMenu(parent)
{}

MyMenu::MyMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{}

MyMenu::~MyMenu()
{
    qDebug() << "Deleting MyMenu";
}
