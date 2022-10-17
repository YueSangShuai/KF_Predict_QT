//
// Created by yuesang on 22-10-14.
//

#ifndef KF_PREDICT_KF_H
#define KF_PREDICT_KF_H

#include <iostream>

#include <ctime>
#include <future>
#include <random>
#include <vector>

#include <ceres/ceres.h>
#include <Eigen/Core>

template<int V_X,int V_Y>//X代表变量的个数，Y代表测量个数，X*Y表示x中所有的变量个数
class Kalman{

public:
    //按照（行列构造）
    using Matrix_A=Eigen::Matrix<double,V_Y*V_X,V_Y*V_X>;//状态转移矩阵
    using Matrix_B=Eigen::Matrix<double,V_Y*V_X,V_X>;//控制矩阵
    using Matrix_H=Eigen::Matrix<double,V_Y,V_X*V_Y>;//观测矩阵 有几个测量就有几行，x几个变量就几列

    using Matrix_x_hat_pre=Eigen::Matrix<double,1,V_X*V_Y>;//xk的先验估计 x有几个变量就有几列
    using Matrix_x_hat=Eigen::Matrix<double,1,V_X*V_Y>;//xk的后验估计 x有几个变量就有几列

    using Matrix_Q=Eigen::Matrix<double,V_X*V_Y,V_X*V_Y>;//测量噪声 x几个变量就几行几列
    using Matrix_R=Eigen::Matrix<double,V_Y,V_Y>;//预测过程中噪声的偏方差 几个测量值就几行几列

    using Matrix_P_K=Eigen::Matrix<double,V_X*V_Y,V_X*V_Y>;//和Q同维度
    using Matrix_P_K_pre=Eigen::Matrix<double,V_X*V_Y,V_X*V_Y>;//和Q同维度

    using Matrix_S=Eigen::Matrix<double,V_X*V_Y,1>;//有几个x就几行
    using Matrix_K=Eigen::Matrix<double,V_X*V_Y,V_Y>;//几个x就几行，几个测量就几列
    using Matrix_Z=Eigen::Matrix<double,1,V_Y>;//测量值 几个测量值就几列
    using Matrix_I=Eigen::Matrix<double,V_Y,V_Y>;//单位矩阵 几个测量值就几行几列


private:
   Matrix_A A;
   Matrix_B B;
   Matrix_H H;

   Matrix_x_hat_pre x_hat_pre;
   Matrix_x_hat x_hat;

   Matrix_Q Q;
   Matrix_R R;

   Matrix_P_K P_K;
   Matrix_P_K_pre P_K_pre;

   Matrix_S S;
   Matrix_K K;
   Matrix_Z Z;
   Matrix_I I;

   bool is_set=false;
public:
    explicit Kalman(double t);

    Eigen::MatrixXd Predict(Eigen::MatrixXd _A);
};

template<int V_X, int V_Y>
Kalman<V_X, V_Y>::Kalman(double t) {
    for(int i=0;i<V_X*V_Y;i++){
        for(int j=0;j<V_X*V_Y;j++){
            if(i==j){
                A(i,j)=1;
            } else if(i==j-1){
                A(i,j)=t;
            }else{
                A(i,j)=0;
            }
        }
    }

    for(int i=0;i<V_X*V_Y;i++){
        for(int j=0;j<V_X*V_Y;j++){
            if(i==j){
                std::cout<<A(i,j)<<" ";
            } else if(i==j-1){
                std::cout<<A(i,j)<<" ";
            }else{
                std::cout<<A(i,j)<<" ";
            }
        }
        std::cout<<std::endl;
    }
}

template<int V_X, int V_Y>
Eigen::MatrixXd Kalman<V_X, V_Y>::Predict(Eigen::MatrixXd _A) {

    return Eigen::MatrixXd();
}


#endif //KF_PREDICT_KF_H
