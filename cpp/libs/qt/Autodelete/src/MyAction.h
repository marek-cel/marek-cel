#ifndef MYACTION_H
#define MYACTION_H

#include <QAction>

class MyAction : public QAction
{
    Q_OBJECT

public:

    explicit MyAction(QObject *parent = nullptr);
    explicit MyAction(const QString &text, QObject *parent = nullptr);
    explicit MyAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    ~MyAction();
};

#endif // MYACTION_H
