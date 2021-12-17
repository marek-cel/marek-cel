#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int var MEMBER _var READ getVar WRITE setVar NOTIFY varChanged)

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getVar() const { return _var; }

    void setVar( int v )
    {
        _var = v;
        emit varChanged(_var);
    }

public slots:

    void onVar_changed(int var);

signals:

    void varChanged(int);

private:
    Ui::MainWindow *ui;

    int _var;

private slots:

    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
