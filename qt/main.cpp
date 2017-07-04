#include "initialscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initialScreen w;
    w.show();

    return a.exec();
}
