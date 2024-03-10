#include "MyShortcut.h"

#include <QDebug>

MyShortcut::MyShortcut(QWidget *parent)
    : QShortcut(parent)
{

}

MyShortcut::MyShortcut(const QKeySequence &key, QWidget *parent, const char *member, const char *ambiguousMember, Qt::ShortcutContext shortcutContext)
    : QShortcut(key, parent, member, ambiguousMember, shortcutContext)
{

}

MyShortcut::~MyShortcut()
{
    qDebug() << "Deleting MyShortcut";
}
