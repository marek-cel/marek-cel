#include "MyAction.h"

#include <QDebug>

MyAction::MyAction(QObject *parent)
    : QAction{parent}
{}

MyAction::MyAction(const QString &text, QObject *parent)
    : QAction(text, parent)
{}

MyAction::MyAction(const QIcon &icon, const QString &text, QObject *parent)
    : QAction(icon, text, parent)
{}

MyAction::~MyAction()
{
    qDebug() << "Deleting MyAction";
}
