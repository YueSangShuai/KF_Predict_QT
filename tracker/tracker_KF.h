//
// Created by yuesang on 23-5-8.
//

#ifndef KF_PREDICT_TRACKER_KF_H
#define KF_PREDICT_TRACKER_KF_H
#include "../KF/kf_cv_three.h"

enum State {
    DETECTING,
    TRACKING,
} ;

class Tracker {
public:
    explicit Tracker();
    Eigen::MatrixXf getPrediction();
    bool process(double dt,Eigen::MatrixXf z);
public:
    State tracker_state;
    double A;//卡方检验系数
    KF_CV_3 kfCv3;
};

#endif //KF_PREDICT_TRACKER_KF_H