//
// Created by yuesang on 22-10-25.
//

#include <opencv2/core/cvdef.h>
#include "Buffpredict.h"

BuffPredictor::BuffPredictor() {
    is_params_confirmed=false;
    params[0] = 0;
    params[1] = 0;
    params[2] = 0;
}

BuffPredictor::~BuffPredictor() {

}

bool BuffPredictor::predict(Buff target) {
    auto t1=std::chrono::steady_clock::now();

    if(target.timestamp - history_buff.front().timestamp >= max_timestamp){
        history_buff.clear();
        history_buff.emplace_back(target);
        last_buff=target;
        is_params_confirmed= false;
        return false;
    }

    if(history_buff.size()<history_deque_len){
        history_buff.emplace_back(target);
        last_buff=target;
        return false;
    }else{
        history_buff.pop_front();
        history_buff.push_back(target);
    }

    if(buff_statue==1 && !is_params_confirmed){
        ceres::Problem problem;
        ceres::Solver::Options options;
        ceres::Solver::Summary summary;       // 优化信息
        double params_fitting[3] = {1, 1, 1};
        for (auto target_info : history_buff)
        {
            problem.AddResidualBlock (     // 向问题中添加误差项
                    // 使用自动求导，模板参数：误差类型，输出维度，输入维度，维数要与前面struct中一致
                    new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3> (
                            new CURVE_FITTING_COST (target_info.timestamp,
                                                    target_info.speed)
                    ),
                    new ceres::CauchyLoss(0.7),
                    params_fitting                 // 待估计参数
            );
        }

        ceres::Solve(options, &problem, &summary);
        std::cout<<"cost:"<<summary.final_cost<<std::endl;
        if (summary.final_cost < max_cost)
        {
            params[0] = params_fitting[0];
            params[1] = params_fitting[1];
            params[2] = params_fitting[2];
            is_params_confirmed = true;
            std::cout<<"Confirmed!"<<std::endl;
        }
        else
        {
            return false;
        }
    }

    return true;
}

