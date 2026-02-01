#include <vector>
#include <climits>
#include <iostream>
using namespace std;
class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int min1 = INT_MAX, min2 = INT_MAX;
        for (int i = 1; i < (int)nums.size(); i++) {
            if (nums[i] < min1) {
                min2 = min1;
                min1 = nums[i];
            } else if (nums[i] < min2) {
                min2 = nums[i];
            }
        }
        return nums[0] + min1 + min2;
    }
};

int main() {
    Solution sol;

    vector<int> t1 = {1, 2, 3, 12};
    cout << "Test 1: " << sol.minimumCost(t1) << " (expected 6)" << endl;

    vector<int> t2 = {5, 4, 3};
    cout << "Test 2: " << sol.minimumCost(t2) << " (expected 12)" << endl;

    vector<int> t3 = {10, 3, 1, 1};
    cout << "Test 3: " << sol.minimumCost(t3) << " (expected 12)" << endl;

    vector<int> t4 = {1, 1, 1};
    cout << "Test 4: " << sol.minimumCost(t4) << " (expected 3)" << endl;

    vector<int> t5 = {3, 2, 1};
    cout << "Test 5: " << sol.minimumCost(t5) << " (expected 6)" << endl;

    vector<int> t6 = {50, 50, 50, 1, 1};
    cout << "Test 6: " << sol.minimumCost(t6) << " (expected 52)" << endl;

    return 0;
}