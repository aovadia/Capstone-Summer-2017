#include "initialscreen.h"
#include <QApplication>

/*
 * Class used to launch the application.
 * Open the 'initialScreen' window
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initialScreen w;
    w.show();

    return a.exec();
}
