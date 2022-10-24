#ifndef KF_PREDICT_EKF_CV_ONE_H
#define KF_PREDICT_EKF_CV_ONE_H
#include <ceres/ceres.h>
#include <Eigen/Core>
struct Predict {
    /*
     * 此处定义能量机关的运动模型
     */
    template<class T>
    void operator()(const T x0[5], T x1[5]) {
        x1[0] = x0[0] + delta_t * (0.785*sin(x1[2])+1.305);
        x1[2] = x0[2] + delta_t * x0[3];  //0.1
        x1[3] = x0[3];  //100
    }
    double delta_t;
};


class EKF_CV_ONE{
public:
    // 无参数构造函数
    EKF_CV_ONE();
    //预测
    void predict(double t);
    // 状态更新
    void update(Eigen::MatrixXf z, double t);
    Eigen::MatrixXf get_x(){return   x_;}
public:
    Eigen::MatrixXf x_;

    Eigen::MatrixXf x_pre;

    Eigen::MatrixXf zk;                           //测量值

    Eigen::MatrixXf JF;                           // 状态转移矩阵
    Eigen::MatrixXf B;                           // 状态转移矩阵

    Eigen::MatrixXf P;                          // 状态协方差矩阵
    Eigen::MatrixXf P_pre;                      // 先验状态协方差矩阵

    Eigen::MatrixXf Q;                          // 过程噪声
    Eigen::MatrixXf JH;                          // 测量矩阵
    Eigen::MatrixXf R;                          // 测量噪声矩阵

    Eigen::MatrixXf K;                          // 卡尔曼增益
};

#endif //KF_PREDICT_EKF_CV_ONE_H