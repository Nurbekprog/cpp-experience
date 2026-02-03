#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;

class Solution {
public:
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        int myDist = abs(target[0]) + abs(target[1]);
        for (auto& g : ghosts)
            if (abs(g[0] - target[0]) + abs(g[1] - target[1]) <= myDist)
                return false;
        return true;
    }
};

int main() {
    Solution sol;
    int passed = 0, failed = 0;

    cout << "============================================" << endl;
    cout << "  789. Escape The Ghosts — Local Test Runner" << endl;
    cout << "============================================\n" << endl;

    struct Test {
        vector<vector<int>> ghosts;
        vector<int> target;
        bool expected;
    };

    vector<Test> tests = {
        {{{1,0},{0,3}},                  {0,1},       true},   
        {{{1,0}},                        {2,0},       false}, 
        {{{2,0}},                        {1,0},       false},  
        {{{-1,0},{0,-1}},                {1,1},       true},  
        {{{0,0}},                        {1,1},       false},  
        {{{1,1}},                        {1,1},       false}, 
        {{{-1,-1}},                      {1,1},       true},   
        {{{3,0},{0,3}},                  {1,1},       true},  
        {{{2,2}},                        {1,1},       false}, 
        {{{-10000,-10000}},              {10000,10000}, true}, 
        {{{10000,10000}},                {10000,10000}, false},
        {{{5,0},{0,5},{-5,0},{0,-5}},    {3,3},       false},  
        {{{1,0},{0,1},{-1,0},{0,-1}},    {1,1},       false},
        {{{100,100}},                    {1,0},       true},  
        {{{0,2}},                        {0,1},       false}, 
        {{{0,3}},                        {0,1},       true},  
    };

    for (int i = 0; i < (int)tests.size(); i++) {
        auto start  = chrono::high_resolution_clock::now();
        bool result = sol.escapeGhosts(tests[i].ghosts, tests[i].target);
        auto end    = chrono::high_resolution_clock::now();
        double ms   = chrono::duration<double, milli>(end - start).count();

        bool ok = (result == tests[i].expected);
        ok ? passed++ : failed++;

        cout << (ok ? "[PASS]" : "[FAIL]")
             << "  Test " << i+1
             << "\t got=" << (result  ? "true " : "false")
             << "\t exp=" << (tests[i].expected ? "true " : "false")
             << "\t " << ms << " ms" << endl;

        if (!ok) {
            cout << "        target=[" << tests[i].target[0] << "," << tests[i].target[1] << "]  ghosts=";
            for (auto& g : tests[i].ghosts) cout << "[" << g[0] << "," << g[1] << "] ";
            cout << endl;
        }
    }

    cout << "\n============================================" << endl;
    cout << "  Results: " << passed << " passed, " << failed << " failed" << endl;
    cout << "============================================" << endl;

    return failed > 0 ? 1 : 0;
}