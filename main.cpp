#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/Montserrat-Medium.ttf");
    QFont font("Montserrat", 10);
    a.setFont(font);

    MainWindow w;
    w.show();
    return a.exec();
}
