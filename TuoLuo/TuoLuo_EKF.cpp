//
// Created by yuesang on 23-5-2.
//

#include <iostream>
#include "TuoLuo_EKF.h"
ExtendedKalmanFilter::ExtendedKalmanFilter()
{
    auto h_func = [](const Eigen::VectorXd & x) {
        Eigen::VectorXd z(4);
        double xc = x(0), yc = x(1), yaw = x(3), r = x(8);
        z(0) = xc - r * cos(yaw);  // xa
        z(1) = yc - r * sin(yaw);  // ya
        z(2) = x(2);               // za
        z(3) = x(3);               // yaw
        return z;
    };
    this->h=h_func;

    auto j_h_func = [](const Eigen::VectorXd & x) {
        Eigen::MatrixXd h(4, 9);
        double yaw = x(3), r = x(8);
        // clang-format off
        //    xc   yc   zc   yaw         vxc  vyc  vzc  vyaw r
        h <<    1,   0,   0,   r*sin(yaw), 0,   0,   0,   0,   -cos(yaw),
                0,   1,   0,   -r*cos(yaw),0,   0,   0,   0,   -sin(yaw),
                0,   0,   1,   0,          0,   0,   0,   0,   0,
                0,   0,   0,   1,          0,   0,   0,   0,   0;
        // clang-format on
        return h;
    };
    this->Jh=j_h_func;

    auto f_func = [this](const Eigen::VectorXd & x, const double & dt_) {
        Eigen::VectorXd x_new = x;
        x_new(0) += x(4) * dt_;
        x_new(1) += x(5) * dt_;
        x_new(2) += x(6) * dt_;
        x_new(3) += x(7) * dt_;
        return x_new;
    };
    this->f=f_func;

    auto j_f_fun = [this](const Eigen::VectorXd &,const double & dt_) {
        Eigen::MatrixXd f(9, 9);

        f <<  1,   0,   0,   0,   dt_, 0,   0,   0,   0,
                0,   1,   0,   0,   0,   dt_, 0,   0,   0,
                0,   0,   1,   0,   0,   0,   dt_, 0,   0,
                0,   0,   0,   1,   0,   0,   0,   dt_, 0,
                0,   0,   0,   0,   1,   0,   0,   0,   0,
                0,   0,   0,   0,   0,   1,   0,   0,   0,
                0,   0,   0,   0,   0,   0,   1,   0,   0,
                0,   0,   0,   0,   0,   0,   0,   1,   0,
                0,   0,   0,   0,   0,   0,   0,   0,   1;
        // clang-format on
        return f;
    };
    this->Jf=j_f_fun;



    auto q_v =  std::vector<double>{//xc  yc    zc    yaw   vxc   vyc   vzc   vyaw  r
                                    1e-2, 1e-2, 1e-2, 1e-2, 1e-2, 1e-2, 1e-2, 1e-2, 1e-2};
    Eigen::DiagonalMatrix<double, 9> q;
    q.diagonal() << q_v[0], q_v[1], q_v[2], q_v[3], q_v[4], q_v[5], q_v[6], q_v[7], q_v[8];
    this->Q=q;

    auto r_v = std::vector<double>{//xa  ya    za    yaw
                                    1e-1, 1e-1, 1e-1, 1e-1};
    Eigen::DiagonalMatrix<double, 4> r;
    r.diagonal() << r_v[0], r_v[1], r_v[2], r_v[3];
    this->R=r;

    this->x_post=Eigen::VectorXd::Zero(9);
    this->x_pri=Eigen::VectorXd::Zero(9);

    Eigen::DiagonalMatrix<double, 9> p0;
    p0.setIdentity();
    this->P_pri=p0;
    this->P_post=p0;
    this->I=Eigen::MatrixXd::Identity(9, 9);
}

void ExtendedKalmanFilter::setState(const Eigen::VectorXd & x0) {
    x_post = x0;
}

Eigen::MatrixXd ExtendedKalmanFilter::predict(const double & dt_)
{
    x_pri = f(x_post,dt_);

    F = Jf(x_post,dt_);
    P_pri = F * P_post * F.transpose() + Q;

    // handle the case when there will be no measurement before the next predict
    x_post = x_pri;
    P_post = P_pri;

    return x_pri;
}

Eigen::MatrixXd ExtendedKalmanFilter::update(const Eigen::VectorXd & z)
{
    H = Jh(x_pri);
    K = P_pri * H.transpose() * (H * P_pri * H.transpose() + R).inverse();
    x_post = x_pri + K * (z - h(x_pri));
    P_post = (I - K * H) * P_pri;

    return x_post;
}

