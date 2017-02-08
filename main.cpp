#include "transferserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransferServer w;
    w.show();

    return a.exec();
}
