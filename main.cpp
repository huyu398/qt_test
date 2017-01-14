#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if (!w.loginTwitter()) {
        return EXIT_FAILURE;
    }
    w.show();
    w.prepare();

    return a.exec();
}
