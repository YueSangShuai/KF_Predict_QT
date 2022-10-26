//
// Created by yuesang on 22-10-21.
//

#include "kf_cv_three.h"
#include "kf_cv_one.h"
KF_CV_3::KF_CV_3() {
    Eigen::MatrixXf x_in=Eigen::MatrixXf::Ones(6,1);
    x_=x_in;

    Eigen::MatrixXf x_pre_in=Eigen::MatrixXf::Zero(6,1);
    x_pre=x_pre_in;

    Eigen::MatrixXf P_in = Eigen::MatrixXf::Identity(6,6);
    P=P_in;

    Eigen::MatrixXf P_in_pre = Eigen::MatrixXf::Identity(6,6);
    P_pre=P_in_pre;

    Eigen::MatrixXf H_in=Eigen::MatrixXf::Zero(3,6);
    for(int i=0;i<3;i++){
        H_in(i,2*i)=1;
    }
    H=H_in;

    Eigen::MatrixXf Q_in = Eigen::MatrixXf::Identity(3,3);
    Q=Q_in*10;



    Eigen::MatrixXf R_in=Eigen::MatrixXf::Identity(3,3);
    R=R_in*1;

}

void KF_CV_3::update(Eigen::MatrixXf z) {
    K=(P_pre*H.transpose())*(H*P_pre*H.transpose()+R).inverse();

    x_=x_pre+K*(z-H*x_pre);

    Eigen::MatrixXf I=Eigen::MatrixXf::Identity(6,6);
               P=(I-K*H)*P_pre;
}

void KF_CV_3::predict(double t) {
    Eigen::MatrixXf F_in=Eigen::MatrixXf::Identity(6,6);
    for(int i=0;i<3;i++){
        F_in(2*i,2*i+1)=t;
    }
    F=F_in;


    Eigen::MatrixXf B_in=Eigen::MatrixXf::Zero(6,3);
    for(int i=0;i<3;i++){
        B_in(2*i,i)=t*t/2;
        B_in(2*i+1,i)=t;
    }
    B=B_in;


    x_pre=F*x_;
    P_pre=F*P*F.transpose()+B*Q*B.transpose();
}
