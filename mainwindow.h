#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <queue>
#include "qcustomplot.h"
#include "KF/kf_cv_one.h"

struct Armor{
    int time=0;
    float positon=0;
    float vx=0;
};


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
    std::vector<Armor> ArmorList;

    KF_CV_1 kalman;
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
