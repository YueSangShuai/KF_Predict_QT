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

bool BuffPredictor::predict(double angel,double speed,int timestamp) {

    auto t1=std::chrono::steady_clock::now();
    Buff target;

    if (history_buff.size() == 0 || target.timestamp - history_buff.front().timestamp >= max_timespan){

        history_buff.clear();
        history_buff.push_back(target);
    }
    return false;
}

/**
 * @brief 滑窗滤波
 *
 * @param start_idx 开始位置
 * @return double 滤波结果
 */
inline double BuffPredictor::shiftWindowFilter(int start_idx=0)
{
    //TODO:修改传入参数，由start_idx改为max_iter
    //计算最大迭代次数
    auto max_iter = int(history_buff.size() - start_idx) - window_size + 1;
    // cout<<max_iter<<endl;

    if (max_iter <= 0 || start_idx < 0)
        return history_buff.back().speed;
    // cout<<start_idx<<":"<<history_info.at(start_idx).speed<<endl;
    // cout<<start_idx + 1<<":"<<history_info.at(start_idx + 1).speed<<endl;
    // cout<<start_idx + 2<<":"<<history_info.at(start_idx + 2).speed<<endl;
    // cout<<start_idx + 3<<":"<<history_info.at(start_idx + 3).speed<<endl;

    double total_sum = 0;
    // cout<<max_iter<<endl;
    for (int i = 0; i < max_iter; i++)
    {
        // cout<<"i:"<<i<<endl;
        double sum = 0;
        for (int j = 0; j < window_size; j++)
            sum += history_buff.at(start_idx + i + j).speed;
        total_sum += sum / window_size;
        // cout<<total_sum<<endl;
    }
    return total_sum / max_iter;
}
