#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        double lo = 0.0, hi = 1.0;

        while (lo < hi) {
            double mid = (lo + hi) / 2.0;
            int count = 0;
            int num = 0, den = 1;   
            double maxFrac = 0.0;

            int i = 0;
            for (int j = 1; j < n; j++) {
                while (i < j && (double)arr[i] <= mid * arr[j]) {
                    if ((double)arr[i] / arr[j] > maxFrac) {
                        maxFrac = (double)arr[i] / arr[j];
                        num = arr[i];
                        den = arr[j];
                    }
                    i++;
                }
                count += i; 
            }

            if (count == k)
                return {num, den};
            else if (count < k)
                lo = mid;  
            else
                hi = mid;   
        }

        return {};  
    }
};