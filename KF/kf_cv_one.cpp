#include "kf_cv_one.h"
KF_CV_1::KF_CV_1() {
    Eigen::MatrixXf x_in=Eigen::MatrixXf::Ones(2,1);
    x_=x_in;

    Eigen::MatrixXf x_pre_in=Eigen::MatrixXf::Zero(2,1);
    x_pre=x_pre_in;

    Eigen::MatrixXf P_in = Eigen::MatrixXf::Identity(2,2);
    P=P_in;

    Eigen::MatrixXf P_in_pre = Eigen::MatrixXf::Identity(2,2);
    P_pre=P_in_pre;

    Eigen::MatrixXf H_in=Eigen::MatrixXf(1,2);
    H_in<<1,0;
    H=H_in;

    Eigen::MatrixXf Q_in = Eigen::MatrixXf::Identity(2,2);
    Q=Q_in*0.01;

    Eigen::MatrixXf R_in=Eigen::MatrixXf::Ones(1,1);
    R=R_in*10;
}

void KF_CV_1::update(Eigen::MatrixXf z, double t) {

    K=(P_pre*H.transpose())*(H*P_pre*H.transpose()+R).inverse();

    x_=x_pre+K*(z-H*x_pre);

    Eigen::MatrixXf I=Eigen::MatrixXf::Ones(2,2);
    P=(I-K*H)*P_pre;

}

void KF_CV_1::predict(double t) {
    Eigen::MatrixXf F_in=Eigen::MatrixXf::Identity(2,2);
    F_in<<1,t,0,1;
    F=F_in;
    x_pre=F*x_;

    P_pre=F*P*F.transpose()+Q;

}
