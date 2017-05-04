#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(NULL);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.clearWindow();
    w.update();

    a.exec();
    return 0;
}
