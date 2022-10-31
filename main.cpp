#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include <ceres/jet.h>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return QApplication::exec();

}
