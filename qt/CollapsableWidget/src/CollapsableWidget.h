#ifndef COLLAPSABLEWIDGET_H
#define COLLAPSABLEWIDGET_H

#include <QWidget>

namespace Ui {
class CollapsableWidget;
}

class CollapsableWidget : public QWidget
{
    Q_OBJECT

public:

    explicit CollapsableWidget(QWidget *parent = nullptr);

    ~CollapsableWidget();

    void setContents(QWidget* contents);

private:

    Ui::CollapsableWidget *ui;

private slots:

    void on_toolButton_toggled(bool checked);
};

#endif // COLLAPSABLEWIDGET_H
