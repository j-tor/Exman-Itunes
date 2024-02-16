#include "mainwindow.h"
#include <QApplication>
#include "ctunes.h"


using namespace std;

// Clase enumeración Genero


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CTunes ctunes;


    return a.exec();
}
