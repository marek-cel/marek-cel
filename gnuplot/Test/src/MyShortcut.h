#ifndef MYSHORTCUT_H
#define MYSHORTCUT_H

#include <QShortcut>

class MyShortcut : public QShortcut
{
    Q_OBJECT

public:

    explicit MyShortcut(QWidget *parent);
    MyShortcut(const QKeySequence &key, QWidget *parent,
               const char *member = nullptr, const char *ambiguousMember = nullptr,
               Qt::ShortcutContext shortcutContext = Qt::WindowShortcut);

    ~MyShortcut();
};

#endif // MYSHORTCUT_H
