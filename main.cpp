#include "loadrunner.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadRunner w;
    w.show();

    return a.exec();
}
