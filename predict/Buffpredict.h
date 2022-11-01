//
// Created by yuesang on 22-10-25.
//

#ifndef KF_PREDICT_BUFFPREDICT_H
#define KF_PREDICT_BUFFPREDICT_H

#include <ceres/ceres.h>
#include <Eigen/Core>
#include<deque>
#include"kffilter.h"
#include <opencv2/core/cvdef.h>


struct alignas(float) Buff{
  double angle;
  double speed;
  double timestamp;
};


class BuffPredictor
{
private:

    //用于拟合能量机关的三角函数
    struct CURVE_FITTING_COST
    {
        CURVE_FITTING_COST (double x, double y) : _x ( x ), _y ( y ) {}
        // 残差的计算
        template <typename T>
        bool operator() (
                const T* const params,     // 模型参数，有3维
                T* residual ) const     // 残差
        {
            residual[0] = T (_y) - params[0] * ceres::sin(params[1] * T (_x) )- params[2]; // f(x)=a*sin(ω*t)+b
            return true;
        }
        const double _x, _y;    // x,y数据

    };

public:
    std::deque<Buff> history_buff;//大符队列
    const int history_deque_len = 160;//队列长度
    const int max_cost = 100;                                                 //TODO:回归函数最大Cost
    const int max_timestamp=90000;
    double params[3];//待拟合的参数

    Buff last_buff;
    bool is_params_confirmed=false;
    int buff_statue=1;//大小符模式 1为小符 2为大符

    int predict_time=3;//拟合时长
    int del_time=0;//从拟合开始到当前拟合的时间

public:
    BuffPredictor();
    ~BuffPredictor();
    bool predict(Buff target);

};


#endif //KF_PREDICT_BUFFPREDICT_H
