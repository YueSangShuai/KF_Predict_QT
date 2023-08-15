//
// Created by yuesang on 23-8-14.
//

#include "TuoLuo_one.h"
TuoLuo_one::TuoLuo_one() {
    Eigen::MatrixXf x_in=Eigen::MatrixXf::Ones(3,1);
    x_=x_in;

    Eigen::MatrixXf x_pre_in=Eigen::MatrixXf::Zero(3,1);
    x_pre=x_pre_in;

    Eigen::MatrixXf P_in = Eigen::MatrixXf::Identity(3,3);
    P=P_in;

    Eigen::MatrixXf P_in_pre = Eigen::MatrixXf::Identity(3,3);
    P_pre=P_in_pre;

    Eigen::MatrixXf Q_in = Eigen::MatrixXf::Identity(3,3);
    Q=Q_in*0.1;

    Eigen::MatrixXf R_in=Eigen::MatrixXf::Identity(3,3);
    R_in<<0.1,0,0,
          0,1,0,
          0,0,1;
    R=R_in*0.01;

}

void TuoLuo_one::update(Eigen::MatrixXf z, double t) {

    double xc=0,yc=0,theate=x_pre(0),r=x_pre(2);

    Eigen::MatrixXf H_in=Eigen::MatrixXf::Zero(3,3);

    H_in<<  r*sin(theate),0,-cos(theate),
            -r*cos(theate),0,-sin(theate),
            1,0,0;
    JH=H_in;

    K=(P_pre*JH.transpose())*(JH*P_pre*JH.transpose()+R).inverse();

    Eigen::VectorXf Z_pre=Eigen::VectorXf::Zero(3);
    Z_pre<<(xc-r*cos(theate)),(yc-r*sin(theate)),theate;

    x_=x_pre+K*(z-Z_pre);

    Eigen::MatrixXf I=Eigen::MatrixXf::Identity(3,3);
    P=(I-K*JH)*P_pre;

}

void TuoLuo_one::predict(double t) {
    Eigen::MatrixXf F_in=Eigen::MatrixXf::Identity(3,3);
    F_in<<  1,t,0,
            0,1,0,
            0,0,1;
    JF=F_in;

    x_pre=JF*x_;
    P_pre=JF*P*JF.transpose()+Q;
}