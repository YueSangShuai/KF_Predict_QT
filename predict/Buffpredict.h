//
// Created by yuesang on 22-10-25.
//

#ifndef KF_PREDICT_BUFFPREDICT_H
#define KF_PREDICT_BUFFPREDICT_H

#include <ceres/ceres.h>
#include <Eigen/Core>
#include<deque>

struct alignas(float) Buff{
  float angle;
  float speed;
  int timestamp;
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
            residual[0] = T (_y) - params[0] * ceres::sin(params[1] * T (_x) + params[2]); // f(x) = a * sin(ω * t + θ)
            return true;
        }
        const double _x, _y;    // x,y数据
    };

private:
    int rotate;//大符的旋转方向 -1为逆时针 0 初始化状态 1为顺时针

    double params[4];//待拟合的参数
    std::deque<Buff> history_buff;//大符队列
    const int delay=200;       //延迟
    const int max_timespan=90000; //最大时间 超过这个时间则重置队列
    const int window_size = 2;                                              //滑动窗口大小
public:
    BuffPredictor();
    ~BuffPredictor();
    double shiftWindowFilter(int start_idx);
    bool predict(double angel,double speed,int timestamp);
    bool is_params_confirmed;
    int buff_statue;//大小符模式 1为小符 2为大符
};


#endif //KF_PREDICT_BUFFPREDICT_H
