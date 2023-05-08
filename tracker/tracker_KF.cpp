#include "tracker_KF.h"

bool Tracker::process(double dt,Eigen::MatrixXf z) {
if(tracker_state==DETECTING){
    kfCv3.predict(dt);
    if(kfCv3.getChi(z)<A){
        tracker_state=TRACKING;
        kfCv3.update(z);
        return true;
    }else{
        kfCv3.update(z);
        return false;
    }

}else if(tracker_state==TRACKING){
    kfCv3.predict(dt);
    if(kfCv3.getChi(z)>A){
        tracker_state=DETECTING;
        kfCv3=*new KF_CV_3();
        return false;
    }else{
        kfCv3.update(z);
        return true;
    }

}

}

Tracker::Tracker():A(0.01),tracker_state(DETECTING)
{

}

Eigen::MatrixXf Tracker::getPrediction() {
    return kfCv3.get_x();
}







