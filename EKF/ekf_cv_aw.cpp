//
// Created by yuesang on 22-10-26.
//

#include "ekf_cv_aw.h"

EKF_CV_AW::EKF_CV_AW() {
    Eigen::MatrixXf x_in=Eigen::MatrixXf::Ones(4,1);
    x_=x_in;

    Eigen::MatrixXf x_pre_in=Eigen::MatrixXf::Zero(4,1);
    x_pre=x_pre_in;

    Eigen::MatrixXf P_in = Eigen::MatrixXf::Identity(4,4);
    P=P_in;

    Eigen::MatrixXf P_in_pre = Eigen::MatrixXf::Identity(4,4);
    P_pre=P_in_pre;

    Eigen::MatrixXf Q_in = Eigen::MatrixXf::Identity(4,4);
    Q=Q_in*1;

    Eigen::MatrixXf R_in=Eigen::MatrixXf::Ones(1,1);
    R=R_in*1;
}

void EKF_CV_AW::predict(double t) {
    x_pre(0)=x_(0)+t*(x_(3)*sin(x_(1))+1.305);
    x_pre(1)=x_(1)+t*x_(2);
    x_pre(2)=x_(2);
    x_pre(3)=x_(3);


    Eigen::MatrixXf F_in=Eigen::MatrixXf::Zero(4,4);
    F_in<<  1, x_(3)*cos(x_(1))*t,x_(3)*cos(x_(1)*t)*t*t,cos(x_(1)*t)*t,
            0,1,t,0,
            0,0,1,0,
            0,0,0,1;

    JF=F_in;
    P_pre=(JF)*P*(JF).transpose()+Q;
}

void EKF_CV_AW::update(Eigen::MatrixXf z, double t) {

    Eigen::MatrixXf H_in=Eigen::MatrixXf::Zero(1,4);
    H_in<<1,0,0,0;

    JH=H_in;

    K=(P_pre*JH.transpose())*(JH*P_pre*JH.transpose()+R).inverse();

    x_=x_pre+K*(z-JH*x_pre);

    Eigen::MatrixXf I=Eigen::MatrixXf::Identity(4,4);
    P=(I-K*JH)*P_pre;
}
