#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        int l = 0;
        int maxLen = 0;
        
        for (int r = 0; r < n; r++) {
            while ((long long)nums[r] > (long long)nums[l] * k) {
                l++;
            }
            maxLen = max(maxLen, r - l + 1);
        }
        
        return n - maxLen;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 6, 2, 9};
    int k = 3;

    cout << sol.minRemoval(nums, k) << endl;

    return 0;
}
