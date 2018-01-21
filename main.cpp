#include "finapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FinApp w;
    w.show();

    return a.exec();
}
