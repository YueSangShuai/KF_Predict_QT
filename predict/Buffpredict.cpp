//
// Created by yuesang on 22-10-25.
//

#include "Buffpredict.h"

BuffPredictor::BuffPredictor() {
    is_params_confirmed=false;
    params[0] = 0;
    params[1] = 0;
    params[2] = 0;
    params[3] = 0;
}

BuffPredictor::~BuffPredictor() {
    auto t1=std::chrono::steady_clock::now();
}

