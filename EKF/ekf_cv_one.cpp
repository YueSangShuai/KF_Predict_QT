//
// Created by yuesang on 22-10-18.
//

#include "ekf_cv_one.h"

EKF_CV_ONE::EKF_CV_ONE() {
    Eigen::MatrixXf x_in=Eigen::MatrixXf::Ones(3,1);
    x_=x_in;

    Eigen::MatrixXf x_pre_in=Eigen::MatrixXf::Zero(3,1);
    x_pre=x_pre_in;

    Eigen::MatrixXf P_in = Eigen::MatrixXf::Identity(3,3);
    P=P_in;

    Eigen::MatrixXf P_in_pre = Eigen::MatrixXf::Identity(3,3);
    P_pre=P_in_pre;

    Eigen::MatrixXf Q_in = Eigen::MatrixXf::Identity(3,3);
    Q=Q_in*0.01;

    Eigen::MatrixXf R_in=Eigen::MatrixXf::Ones(1,1);
    R=R_in*10;
}

void EKF_CV_ONE::predict(double t) {
    x_pre(0)=x_(0)+t*(0.785*sin(x_(1))+1.305);
    x_pre(1)=x_(1)+t*x_(2);
    x_pre(2)=x_pre(2);


    Eigen::MatrixXf F_in=Eigen::MatrixXf::Identity(3,3);
    F_in<<  1, 0.785*cos(x_(1))*t, 0.785*t*t*cos(x_(2)*t),
            0,1,t,
            0,0,1;
    JF=F_in;
    P_pre=JF*P*JF.transpose()+Q;
}

void EKF_CV_ONE::update(Eigen::MatrixXf z, double t) {

    Eigen::MatrixXf H_in=Eigen::MatrixXf::Zero(1,3);
    H_in<<1,0,0;

    JH=H_in;

    K=(P_pre*JH.transpose())*(JH*P_pre*JH.transpose()+R).inverse();

    x_=x_pre+K*(z-JH*x_pre);

    Eigen::MatrixXf I=Eigen::MatrixXf::Identity(3,3);
    P=(I-K*JH)*P_pre;
}
