//
// Created by yuesang on 22-10-18.
//

#ifndef KF_PREDICT_KF_CA_ONE_H
#define KF_PREDICT_KF_CA_ONE_H

#include <ceres/ceres.h>
#include <Eigen/Core>

class KF_CA_1{
public:
    // 无参数构造函数
    KF_CA_1();
    //预测
    void predict(double t);
    // 状态更新
    void update(Eigen::MatrixXf z, double t);
    Eigen::MatrixXf get_x(){return   x_;}
public:
    Eigen::MatrixXf x_;

    Eigen::MatrixXf x_pre;

    Eigen::MatrixXf zk;                           //测量值

    Eigen::MatrixXf F;                           // 状态转移矩阵
    Eigen::MatrixXf B;                           // 状态转移矩阵

    Eigen::MatrixXf P;                          // 状态协方差矩阵
    Eigen::MatrixXf P_pre;                      // 先验状态协方差矩阵

    Eigen::MatrixXf Q;                          // 过程噪声
    Eigen::MatrixXf H;                          // 测量矩阵
    Eigen::MatrixXf R;                          // 测量噪声矩阵

    Eigen::MatrixXf K;                          // 卡尔曼增益


};

#endif //KF_PREDICT_KF_CA_ONE_H
