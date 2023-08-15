//
// Created by yuesang on 23-8-15.
//

#include "TuoLuo_two.h"

TuoLuo_Two::TuoLuo_Two() {
    Eigen::MatrixXf x_in=Eigen::MatrixXf::Ones(5,1);
    x_=x_in;

    Eigen::MatrixXf x_pre_in=Eigen::MatrixXf::Zero(5,1);
    x_pre=x_pre_in;

    Eigen::MatrixXf P_in = Eigen::MatrixXf::Identity(5,5);
    P=P_in;

    Eigen::MatrixXf P_in_pre = Eigen::MatrixXf::Identity(5,5);
    P_pre=P_in_pre;

    Eigen::MatrixXf Q_in = Eigen::MatrixXf::Identity(5,5);
    Q=Q_in*0.1;

    Eigen::MatrixXf R_in=Eigen::MatrixXf::Identity(3,3);
    R_in<<0.1,0,0,
            0,1,0,
            0,0,1;
    R=R_in;
}

void TuoLuo_Two::update(Eigen::MatrixXf z, double t) {

    double xc=x_pre(0),yc=x_pre(1),theate=x_pre(2),r=x_pre(4);
    Eigen::MatrixXf H_in=Eigen::MatrixXf::Zero(3,5);

    H_in<<  1,0,r*sin(theate),0,-cos(theate),
            0,1,-r*cos(theate),0,-sin(theate),
            0,0,1,0,0;
    JH=H_in;

    K=(P_pre*JH.transpose())*(JH*P_pre*JH.transpose()+R).inverse();

    Eigen::VectorXf Z_pre=Eigen::VectorXf::Zero(3);
    Z_pre<<(xc-r*cos(theate)),(yc-r*sin(theate)),theate;

    x_=x_pre+K*(z-Z_pre);

    Eigen::MatrixXf I=Eigen::MatrixXf::Identity(5,5);
    P=(I-K*JH)*P_pre;

}

void TuoLuo_Two::predict(double t) {
    Eigen::MatrixXf F_in=Eigen::MatrixXf::Identity(5,5);
    F_in<< 1,0,0,0,0,
           0,1,0,0,0,
           0,0,1,t,0,
           0,0,0,1,0,
           0,0,0,0,1;

    JF=F_in;
    x_pre=JF*x_;
    P_pre=JF*P*JF.transpose()+Q;
}