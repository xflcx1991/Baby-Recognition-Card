#include "widget.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Widget aa;
    aa.show();
    return a.exec();
}
