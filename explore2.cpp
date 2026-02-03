#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
using namespace std;

class Solution {
public:
    int rotatedDigits(int n) {
        int count = 0;
        for (int x = 1; x <= n; x++) {
            bool valid = true, different = false;
            int tmp = x;
            while (tmp > 0) {
                int d = tmp % 10;
                if (d == 3 || d == 4 || d == 7) { valid = false; break; }
                if (d == 2 || d == 5 || d == 6 || d == 9) different = true;
                tmp /= 10;
            }
            count += (valid && different);
        }
        return count;
    }
};

class BruteForce {
public:
    int rotate(int d) {
        if (d == 0) return 0;
        if (d == 1) return 1;
        if (d == 2) return 5;
        if (d == 5) return 2;
        if (d == 6) return 9;
        if (d == 8) return 8;
        if (d == 9) return 6;
        return -1; 
    }

    int rotatedDigits(int n) {
        int count = 0;
        for (int x = 1; x <= n; x++) {
            int tmp = x, rotated = 0, mul = 1;
            bool valid = true;
            while (tmp > 0) {
                int r = rotate(tmp % 10);
                if (r == -1) { valid = false; break; }
                rotated += r * mul;
                mul *= 10;
                tmp /= 10;
            }
            if (valid && rotated != x) count++;
        }
        return count;
    }
};

int main() {
    Solution sol;
    BruteForce brute;
    int passed = 0, failed = 0;

    cout << "============================================" << endl;
    cout << "   788. Rotated Digits — Local Test Runner  " << endl;
    cout << "============================================\n" << endl;

    vector<pair<int,int>> tests = {
        {1,     0},
        {2,     1},
        {5,     2},
        {9,     4},
        {10,    4},
        {11,    4},
        {12,    5},
        {25,    12},
        {100,   40},
        {1000,  316},
        {10000, 2320}
    };

    for (auto& [n, expected] : tests) {
        auto start = chrono::high_resolution_clock::now();
        int result  = sol.rotatedDigits(n);
        auto end    = chrono::high_resolution_clock::now();
        double ms   = chrono::duration<double, milli>(end - start).count();

        bool ok = (result == expected);
        ok ? passed++ : failed++;

        cout << (ok ? "[PASS]" : "[FAIL]")
             << "  n="    << n
             << "\t got=" << result
             << "\t exp=" << expected
             << "\t " << ms << " ms" << endl;

        if (!ok) {
            cout << "        ^^^ MISMATCH ^^^" << endl;
        }
    }

    cout << "\n--- Stress Test (solution vs brute force, n=1..10000) ---\n";
    {
        auto start = chrono::high_resolution_clock::now();
        bool stress_ok = true;
        for (int n = 1; n <= 10000; n++) {
            int a = sol.rotatedDigits(n);
            int b = brute.rotatedDigits(n);
            if (a != b) {
                cout << "[FAIL] Mismatch at n=" << n
                     << " sol=" << a << " brute=" << b << endl;
                stress_ok = false;
                failed++;
                break;
            }
        }
        auto end = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(end - start).count();

        if (stress_ok) {
            passed++;
            cout << "[PASS]  All 10000 values match brute force  ("
                 << ms << " ms)" << endl;
        }
    }

    cout << "\n============================================" << endl;
    cout << "  Results: " << passed << " passed, " << failed << " failed" << endl;
    cout << "============================================" << endl;

    return failed > 0 ? 1 : 0;
}