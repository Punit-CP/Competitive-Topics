https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/

// Key DFS Pattern: Bottom-Up Aggregation
// For each node:
// Recurse on all children, collecting some form of result (e.g., path cost, subtree info).
// Aggregate the results (e.g., take the max).
// Compare each child result to the aggregate (e.g., if less than max, record an adjustment).
// Return the combined result for the parent to use.

// This DFS pattern falls under:   "Post-order Tree Dynamic Programming (DP on Trees)"

// code:
class Solution {
public:
    vector<vector<int>> adj;
    int result = 0;

    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        adj.resize(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        function<int(int, int)> dfs = [&](int u, int p) -> int {
            vector<int> childCost;
            for (int v : adj[u]) {
                if (v == p) continue;
                childCost.push_back(dfs(v, u));
            }

            if (childCost.empty()) return cost[u]; // Leaf node

            int maxCost = *max_element(childCost.begin(), childCost.end());
            for (int val : childCost) {
                if (val < maxCost) result++;
            }

            return cost[u] +0LL+ maxCost;
        };

        dfs(0, -1);
        return result;
    }
};



// 🏗 Template (Generalized) for Post order or Bottom up processing:
int dfs(int u, int parent) {
    vector<int> childValues;
    for (int v : tree[u]) {
        if (v == parent) continue;
        childValues.push_back(dfs(v, u));
    }

    if (childValues.empty()) return baseValue[u];

    int aggregate = some_function(childValues);
    for (auto val : childValues) {
        if (val < aggregate) operations++; // tracking adjustment
    }

    return baseValue[u] + aggregate;
}
// 
