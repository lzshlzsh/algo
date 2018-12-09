/**
 * @file coin_change.cpp
 * @brief
 * @version 1.0
 * @date 02/02/2016 05:05:04 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    int coinChange(vector<int> &coins, int amount) {
        min_n_ = 0x7fffffff;
    }
private:
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    int coins(const std::vector<int> &coins, const int amount, int cur_amount, int n) {
        for (auto it = coins.begin(); it != coins.end(); ++it) {
            cur_amount += *it;
            n++;
            if (cur_amount < amount) {
            }
        }
    }

    int min_n_;
};

int main() {
    return 0;
}
