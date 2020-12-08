//
// Created by lzs on 12/9/20.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<std::pair<int, int>> nums_with_index;

        for (auto i = 0; i < nums.size(); i++) {
            nums_with_index.emplace_back(std::pair<int, int>(nums[i], i));
        }

        std::sort(nums_with_index.begin(), nums_with_index.end(),
                  [](std::pair<int, int> a, std::pair<int, int> b) -> bool {
                      return a.first < b.first;
                  });
        int i, j;
        for (i = 0, j = nums_with_index.size() - 1; i < j;) {
            if (nums_with_index[i].first + nums_with_index[j].first > target) {
                j--;
            } else if (nums_with_index[i].first + nums_with_index[j].first < target) {
                i++;
            } else {
                break;
            }
        }
        return vector<int>{nums_with_index[i].second, nums_with_index[j].second};
    }
};

int main(int argc, char **argv) {
    Solution solution;

    vector<int> nums{2, 7, 11, 15};

    for (auto const &item: solution.twoSum(nums, 9)) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}