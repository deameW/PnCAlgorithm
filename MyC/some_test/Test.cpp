#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <stack>
#include <map>
#include "Test.h"
#include <vector>
using namespace std;

// Function prototype
vector<int> Solution(const vector<int>& nums1, vector<int> nums2);

//int main(){
//    auto res = Solution(vector<int> {4,1,2}, vector<int>{1,3,4,2});
//}

vector<int> Solution(const vector<int>& nums1, vector<int> nums2) {
    int len2 = nums2.size();
    std::stack<int> s {};
    std::map<int, int> m{};

    for (int i = len2 -1; i>=0; i--){
        if (s.empty()){
            s.push(nums2[i]);
            m[nums2[i]] =-1;
        }else{
            if(nums2[i] <= s.top()){
                int nextBig = s.top();
                s.pop();
                m[nums2[i]] = nextBig;
                s.push(nums2[i]);
            }else{
                m[nums2[i]] = -1;
            }
        }
    }

    vector<int> res{};
    for (int i : nums1){
        auto find = m.find(i);
        if (find != m.end()) {
            res.push_back(find->first);
        }
    }
    return res;
}


