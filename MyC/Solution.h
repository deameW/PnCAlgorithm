//
// Created by QianWu on 2024/3/7.
//

#ifndef MYC_SOLUTION_H
#define MYC_SOLUTION_H


#include <vector>

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        int first = 0;
        int end = nums.size() -1;

        while(first < end){
            int mid = (first + end) / 2;
            // 统计数组中的小于mid的个数
            int times = getLessNums(nums, mid);
            if(times >= mid){
                end = mid;
            }else{
                first = mid;
            }
        }
        return first;
    }

    int getLessNums(std::vector<int> & nums, int target){
        int res = 0;
        for(const auto & num : nums){
            if(num <= target){
                res ++;
            }
        }
        return res;
    }
};


#endif //MYC_SOLUTION_H
