#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include "KF/kf.h"
#include "KF/kf_cv_one.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//   Kalman<3,2> kalman(0.01);

    return QApplication::exec();
}
