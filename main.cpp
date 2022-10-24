#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include "KF/kf.h"
#include "KF/kf_cv_one.h"
#include <ceres/jet.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return QApplication::exec();
}
