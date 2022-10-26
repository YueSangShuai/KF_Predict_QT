//
// Created by yuesang on 22-10-26.
//

#include "ekf_cv_awb.h"

EKF_CV_AWB::EKF_CV_AWB() {
    Eigen::MatrixXf x_in=Eigen::MatrixXf::Ones(5,1);
    x_=x_in;

    Eigen::MatrixXf x_pre_in=Eigen::MatrixXf::Zero(5,1);
    x_pre=x_pre_in;

    Eigen::MatrixXf P_in = Eigen::MatrixXf::Identity(5,5);
    P=P_in;

    Eigen::MatrixXf P_in_pre = Eigen::MatrixXf::Identity(5,5);
    P_pre=P_in_pre;

    Eigen::MatrixXf Q_in = Eigen::MatrixXf(5,5);
    Q_in<<  1,0,0,0,0,
            0,1,0,0,0,
            0,0,1,0,0,
            0,0,0,1,0,
            0,0,0,0,1;
    Q=Q_in;

    Eigen::MatrixXf R_in=Eigen::MatrixXf::Ones(1,1);
    R=R_in*1;
}

void EKF_CV_AWB::predict(double t) {
    x_pre(0)=x_(0)+t*(x_(3)*sin(x_(1))+x_(4));
    x_pre(1)=x_(1)+t*x_(2);

    x_pre(2)=x_(2);
    x_pre(3)=x_(3);
    x_pre(4)=x_(4);


    Eigen::MatrixXf F_in=Eigen::MatrixXf::Zero(5,5);
    F_in<<  1,
    x_(3)*cos(x_(1))*t,
    x_(3)*cos(x_(1)*t)*t*t,
    cos(x_(1)*t)*t,
    t,
            0,1,t,0,0,
            0,0,1,0,0,
            0,0,0,1,0,
            0,0,0,0,1;

    JF=F_in;
    P_pre=(JF)*P*(JF).transpose()+Q;
}

void EKF_CV_AWB::update(Eigen::MatrixXf z, double t) {

    Eigen::MatrixXf H_in=Eigen::MatrixXf::Zero(1,5);
    H_in<<1,0,0,0,0;

    JH=H_in;

    K=(P_pre*JH.transpose())*(JH*P_pre*JH.transpose()+R).inverse();

    x_=x_pre+K*(z-JH*x_pre);

    Eigen::MatrixXf I=Eigen::MatrixXf::Identity(5,5);
    P=(I-K*JH)*P_pre;
}
