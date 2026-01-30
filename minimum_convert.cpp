#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

class Solution {
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        int n = source.length();
        
        unordered_map<string, vector<pair<string, int>>> graph;
        for (int i = 0; i < original.size(); ++i) {
            graph[original[i]].emplace_back(changed[i], cost[i]);
        }
        
        unordered_map<string, unordered_map<string, long long>> minCost;
        
        auto dijkstra = [&](const string& start) {
            unordered_map<string, long long> dist;
            priority_queue<pair<long long, string>, vector<pair<long long, string>>, greater<>> pq;
            
            dist[start] = 0;
            pq.emplace(0, start);
            
            while (!pq.empty()) {
                auto [currDist, node] = pq.top();
                pq.pop();
                
                if (currDist > dist[node]) continue;
                
                for (const auto& [neighbor, weight] : graph[node]) {
                    long long newDist = currDist + weight;
                    if (dist.find(neighbor) == dist.end() || newDist < dist[neighbor]) {
                        dist[neighbor] = newDist;
                        pq.emplace(newDist, neighbor);
                    }
                }
            }
            
            return dist;
        };
        
        unordered_map<string, bool> processed;
        for (const auto& s : original) {
            if (!processed[s]) {
                minCost[s] = dijkstra(s);
                processed[s] = true;
            }
        }
        
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        
        for (int i = 0; i < n; ++i) {
            if (dp[i] == LLONG_MAX) continue;
            
            for (int j = i + 1; j <= n; ++j) {
                string srcSub = source.substr(i, j - i);
                string tgtSub = target.substr(i, j - i);
                
                if (srcSub == tgtSub) {
                    dp[j] = min(dp[j], dp[i]);
                } else {
                    if (minCost.count(srcSub) && minCost[srcSub].count(tgtSub)) {
                        dp[j] = min(dp[j], dp[i] + minCost[srcSub][tgtSub]);
                    }
                }
            }
        }
        
        return dp[n] == LLONG_MAX ? -1 : dp[n];
    }
};