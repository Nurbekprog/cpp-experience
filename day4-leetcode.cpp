#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();

        vector<int> up(n, 1), down(n, 1), up2(n, 1);

        for (int i = 1; i < n; i++)
            up[i] = (nums[i] > nums[i - 1]) ? up[i - 1] + 1 : 1;

        for (int i = 1; i < n; i++)
            down[i] = (nums[i] < nums[i - 1]) ? down[i - 1] + 1 : 1;

        for (int i = n - 2; i >= 0; i--)
            up2[i] = (nums[i] < nums[i + 1]) ? up2[i + 1] + 1 : 1;

        for (int q = 1; q < n - 1; q++) {
            if (down[q] >= 2 && up2[q] >= 2) {
                int p = q - down[q] + 1;
                if (p >= 1 && up[p] >= 2)
                    return true;
            }
        }

        return false;
    }
};

void test(int id, vector<int> nums, bool expected) {
    Solution sol;
    bool result = sol.isTrionic(nums);
    string status = (result == expected) ? "PASS" : "FAIL";

    cout << "[" << status << "] Test " << id << " | nums = [";
    for (int i = 0; i < (int)nums.size(); i++)
        cout << nums[i] << (i < (int)nums.size() - 1 ? ", " : "");
    cout << "] | Expected: " << (expected ? "true" : "false")
         << " | Got: " << (result ? "true" : "false") << endl;
}

int main() {
    cout << "========== Trionic Array Tests ==========" << endl;

    test(1, {1, 3, 5, 4, 2, 6},       true);   
    test(2, {2, 1, 3},                 false);  
    test(3, {1, 3, 2, 4, 3, 5},       false); 
    test(4, {1, 2, 3, 4, 5},          false);  
    test(5, {5, 4, 3, 2, 1},          false);  
    test(6, {1, 5, 3, 4, 2, 6},       false); 
    test(7, {1, 2, 1, 2, 1},          false);  
    test(8, {3, 7, 1},                false);  
    test(9, {1, 3, 2, 4},             true);   
    test(10, {1, 2, 3, 2, 1, 2, 3},   true);  

    test(11, {-5, -2, -4, -1},        true);  
    test(12, {-3, -1, -2, 0},         true);   

    test(13, {1, 2, 2, 1, 3},         false);  
    test(14, {1, 3, 3, 2, 4},         false);  
    test(15, {1, 3, 2, 2, 4},         false);  

    cout << "=========================================" << endl;
    return 0;
}