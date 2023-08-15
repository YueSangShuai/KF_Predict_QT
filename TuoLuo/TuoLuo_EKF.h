//
// Created by yuesang on 23-5-2.
//

#ifndef KF_PREDICT_TUOLUO_EKF_H
#define KF_PREDICT_TUOLUO_EKF_H

#include <Eigen/Dense>
#include <functional>

class ExtendedKalmanFilter
{
public:

    explicit ExtendedKalmanFilter();
    using HNonlinearFunc = std::function<Eigen::VectorXd(const Eigen::VectorXd &)>;
    using HJacobianFunc = std::function<Eigen::MatrixXd(const Eigen::VectorXd &)>;
    using FNonlinearFunc = std::function<Eigen::VectorXd(const Eigen::VectorXd &,const double &)>;
    using FJacobianFunc = std::function<Eigen::MatrixXd(const Eigen::VectorXd &,const double &)>;

    // Set the initial state
    void setState(const Eigen::VectorXd & x0);

    // Compute a predicted state
    Eigen::MatrixXd predict(const double & dt_);

    // Update the estimated state based on measurement
    Eigen::MatrixXd update(const Eigen::VectorXd & z);


private:
    // Process nonlinear vector function
    FNonlinearFunc f;
    // Observation nonlinear vector function
    HNonlinearFunc h;
    // Jacobian of f()
    FJacobianFunc Jf;
    Eigen::MatrixXd F;
    // Jacobian of h()
    HJacobianFunc Jh;
    Eigen::MatrixXd H;
    // Process noise covariance matrix
    Eigen::MatrixXd Q;
    // Measurement noise covariance matrix
    Eigen::MatrixXd R;

    // Priori error estimate covariance matrix
    Eigen::MatrixXd P_pri;
    // Posteriori error estimate covariance matrix
    Eigen::MatrixXd P_post;

    // Kalman gain
    Eigen::MatrixXd K;

    // N-size identity
    Eigen::MatrixXd I;

    // Priori state
    Eigen::VectorXd x_pri;
    // Posteriori state
    Eigen::VectorXd x_post;
};

#endif //KF_PREDICT_TUOLUO_EKF_H
