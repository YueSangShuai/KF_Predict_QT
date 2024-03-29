#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <queue>
#include "qcustomplot.h"
#include <opencv2/core/core.hpp>

#include "KF/kf_cv_one.h"
#include "KF/kf_ca_one.h"
#include "KF/kf_cv_three.h"
#include "EKF/ekf_cv_one.h"
#include "EKF/ekf_cv_aw.h"
#include "EKF/ekf_cv_awb.h"

#include "TuoLuo/TuoLuo_EKF.h"

#include"predict/Buffpredict.h"
#include "predict/kffilter.h"

#include "tracker/tracker_KF.h"
#include"TuoLuo/TuoLuo_one.h"
#include "TuoLuo/TuoLuo_two.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void TimeData_Update(void);

private slots:
    void on_checkBox_1_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);


private:
    void keyPressEvent(QKeyEvent*event);
    int timeid;
    void timerEvent(QTimerEvent * event);

    KF_CV_1 kalman;
    KF_CA_1 kfCa1;
    KF_CV_3 kfCv3;

    EKF_CV_ONE ekfCvOne;
    EKF_CV_AW ekfCvAw;
    EKF_CV_AWB ekfCvAwb;
    TuoLuo_one tuoluo_one;
    TuoLuo_Two tuoluo_two;


    KF kf;
    BuffPredictor predicter;

    Tracker tracker;

    ExtendedKalmanFilter ekf;

    cv::RNG rng;                        // OpenCV随机数产生器
    Ui::MainWindow *ui;

    // 绘图控件的指针
    QCustomPlot *pPlot1;
    // 状态栏指针
    QStatusBar *sBar;
    // 绘图控件中曲线的指针
    QCPGraph *pGraph1_1;
    QCPGraph *pGraph1_2;
    QCPGraph *pGraph1_3;
    QCPGraph *pGraph1_4;

    void QPlot_init(QCustomPlot *customPlot);
    void Show_Plot(QCustomPlot *customPlot, double num);
};
#endif // MAINWINDOW_H
