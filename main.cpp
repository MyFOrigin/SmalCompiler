#include "mainwindow.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Login log;
    if(log.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    return 0;
}
