#include <iostream>

#include <QApplication>
#include "MainWindow.h"

#include <gnuplot-iostream.h>

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    std::vector<std::pair<double,double>> data;
    data.emplace_back(-2,-0.8);
    data.emplace_back(-1,-0.4);
    data.emplace_back(0,-0);
    data.emplace_back(1,0.4);
    data.emplace_back(1,0.8);

    Gnuplot gp;
    gp << "plot [-5:5] sin(x) tit 'sin(x)', '-' tit 'data'\n";
    gp.send1d(data);
    return 0;

    QApplication app(argc, argv);
    MainWindow win;

    win.show();

    return app.exec();
}
