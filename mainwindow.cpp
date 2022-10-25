#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/core.hpp"

bool flag= false;
double positon=0;
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // 给widget绘图控件，设置个别名，方便书写
    pPlot1 = ui->widget_1;

    // 状态栏指针
    sBar = statusBar();

    // 初始化图表1
    QPlot_init(pPlot1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 绘图图表初始化
void MainWindow::QPlot_init(QCustomPlot *customPlot)
{
    // 创建定时器，用于定时生成曲线坐标点数据
    timeid=startTimer(10);

    // 图表添加两条曲线
    pGraph1_1 = customPlot->addGraph();
    pGraph1_2 = customPlot->addGraph();

    pGraph1_3 = customPlot->addGraph();
    pGraph1_4 = customPlot->addGraph();

    // 设置曲线颜色
    pGraph1_1->setPen(QPen(Qt::red));
    pGraph1_2->setPen(QPen(Qt::yellow));

    pGraph1_1->setPen(QPen(Qt::green));
    pGraph1_2->setPen(QPen(Qt::blue));
    // 设置坐标轴名称
    customPlot->xAxis->setLabel("X");
    customPlot->yAxis->setLabel("Y");

    // 设置y坐标轴显示范围
    customPlot->yAxis->setRange(-120,120);

    // 显示图表的图例
    customPlot->legend->setVisible(true);
    // 添加曲线名称
    pGraph1_1->setName("真实位置");
    pGraph1_2->setName("卡尔曼位置");

    pGraph1_3->setName("真实速度");
    pGraph1_4->setName("观测速度");

    // 设置波形曲线的复选框字体颜色
    ui->checkBox_1->setStyleSheet("QCheckBox{color:rgb(255,0,0)}");//设定前景颜色,就是字体颜色

    // 允许用户用鼠标拖动轴范围，用鼠标滚轮缩放，点击选择图形:
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}
void MainWindow::timerEvent ( QTimerEvent * event ){
    TimeData_Update();
}
// 定时器溢出处理槽函数。用来生成曲线的坐标数据。
void MainWindow::TimeData_Update(void)
{
    // 生成坐标数据
    static float f=0;

    f++;


//    kfCa1.predict(1);
//    Eigen::MatrixXf Z_in=Eigen::MatrixXf(1,1);
//    Z_in<<positon;
//    kfCa1.update(Z_in,1);

    //qDebug() << sin(f)*100;
    // 将坐标数据，传递给曲线
    Show_Plot(pPlot1, positon);
}

// 曲线更新绘图
void MainWindow::Show_Plot(QCustomPlot *customPlot, double num)
{
    static double cnt=0;
    cnt++;

    double Ts=0.1;


//TODO：卡尔曼滤波CV模型
//    kalman.predict(Ts);
//    Eigen::MatrixXf Z_in=Eigen::MatrixXf(1,1);
//    Z_in<<positon;
//    kalman.update(Z_in,Ts);


//TODO：卡尔曼滤波CA模型
    //positon=3*(Ts*cnt)*(Ts*cnt);
//    kfCa1.predict(Ts);
//    Eigen::MatrixXf Z_in=Eigen::MatrixXf(1,1);
//    Z_in<<positon;
//    kfCa1.update(Z_in,Ts);

//TODO：扩展卡尔曼滤波CV模型
    double v=0.785*sin(1.884*Ts*cnt)+1.305;
    positon=positon+Ts*v;

    ekfCvOne.predict(Ts);
    Eigen::MatrixXf Z_in=Eigen::MatrixXf(1,1);
    Z_in<<positon;
    ekfCvOne.update(Z_in,Ts);
//    // 给曲线添加数据
    pGraph1_1->addData(cnt, v);
    pGraph1_2->addData(cnt, 0.785*sin(ekfCvOne.get_x()(1))+1.305);



//    pGraph1_3->addData(cnt, num/cnt);
//    pGraph1_4->addData(cnt, kalman.get_x()(1));

    // 设置x坐标轴显示范围，使其自适应缩放x轴，x轴最大显示1000个点
    customPlot->xAxis->setRange((pGraph1_1->dataCount()>1000)?(pGraph1_1->dataCount()-1000):0, pGraph1_1->dataCount());
    // 更新绘图，这种方式在高填充下太浪费资源。有另一种方式rpQueuedReplot，可避免重复绘图。
    // 最好的方法还是将数据填充、和更新绘图分隔开。将更新绘图单独用定时器更新。例程数据量较少没用单独定时器更新，实际工程中建议大家加上。
    //customPlot->replot();
    customPlot->replot(QCustomPlot::rpQueuedReplot);

    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0; // 开始到现在的时间，单位秒
    ////计算帧数
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 1) // 每1秒求一次平均值
    {
        //状态栏显示帧数和数据总数
        ui->statusbar->showMessage(
                QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(customPlot->graph(0)->data()->size()+customPlot->graph(1)->data()->size())
                , 0);
        lastFpsKey = key;
        frameCount = 0;
    }

}


/// 隐藏曲线有两种方法：1.设置为透明色，但也会影响图例中的颜色    2.设置可见性属性
// 1. setPen设置为透明色的方法，隐藏曲线，但也会影响图例中的颜色。不建议使用。
void MainWindow::on_checkBox_1_stateChanged(int arg1)
{
    if(arg1){
        // 显示
        pGraph1_1->setPen(QPen(Qt::red));
    }else{
        // 不显示，透明色
        pGraph1_1->setPen(QColor(0,0,0,0));
    }
    pPlot1->replot();
}

// 2. setVisible设置可见性属性，隐藏曲线，不会对图例有任何影响。推荐使用。
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1){
        pGraph1_2->setVisible(true);
    }else{
        pGraph1_2->setVisible(false);//void QCPLayerable::setVisible(bool on)
    }
    pPlot1->replot();
}

// 2. setVisible设置可见性属性，隐藏曲线，不会对图例有任何影响。推荐使用。
void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1){
        pGraph1_3->setVisible(true);
    }else{
        pGraph1_3->setVisible(false);//void QCPLayerable::setVisible(bool on)
    }
    pPlot1->replot();
}
// 2. setVisible设置可见性属性，隐藏曲线，不会对图例有任何影响。推荐使用。
void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1){
        pGraph1_4->setVisible(true);
    }else{
        pGraph1_4->setVisible(false);//void QCPLayerable::setVisible(bool on)
    }
    pPlot1->replot();
}

void MainWindow::keyPressEvent(QKeyEvent*event) {
if(event->key()==Qt::Key_Q){
    killTimer(timeid);
}else if(event->key()==Qt::Key_S){
    timeid= startTimer(10);
}
}
