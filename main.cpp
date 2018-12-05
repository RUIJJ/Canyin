#include "login.h"
#include "sqlconnect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    sqlconnect sc;
    sc.Connect();

    Login w;
    w.show();

    return a.exec();
}
