🔹 1. Basic DFS
// Traverses all nodes in depth-first order.
// Used for both trees and graphs.
void dfs(int u, int parent) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v, u);
    }
}



🔹 2. Preorder / Postorder DFS

// 🔸 Preorder (process parent before children):
void dfs(int u) {
    cout << u << " "; // process before children
    for (int v : adj[u]) {
        dfs(v);
    }
}
// 🔸 Postorder (process children before parent):
void dfs(int u) {
    for (int v : adj[u]) {
        dfs(v);
    }
    cout << u << " "; // process after children
}



🔹 3. DFS for Subtree Size / Tree DP
// Used to compute properties about subtrees (like size, sum, min/max, DP, etc.).
int dfs(int u) {
    int size = 1;
    for (int v : adj[u]) {
        size += dfs(v);
    }
    subtree[u] = size;
    return size;
}




 4. DFS with Entry/Exit Times (Euler Tour)
// Used for LCA, segment trees on trees, binary lifting, etc.
int timer = 0;
void dfs(int u, int p) {
    in[u] = ++timer;
    for (int v : adj[u]) {
        if (v != p) dfs(v, u);
    }
    out[u] = ++timer;
}



🔹 5. Topological Sort (DFS-based)
// Used for DAGs to find an ordering.
void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v);
    }
    order.push_back(u);
}



6. Cycle Detection in Graphs
// 🔸 Undirected Graph:
bool dfs(int u, int parent) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (dfs(v, u)) return true;
        } else if (v != parent) {
            return true;
        }
    }
    return false;
}

// 🔸 Directed Graph:
// Use color array: 0 = unvisited, 1 = visiting, 2 = visited
bool dfs(int u) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 1) return true; // back edge
        if (color[v] == 0 && dfs(v)) return true;
    }
    color[u] = 2;
    return false;
}



🔹 7. Backtracking DFS
// Used in combinatorics, N-Queens, permutations, path finding, etc.
void dfs(int level) {
    if (level == n) {
        print();
        return;
    }
    for (int i = 0; i < choices; i++) {
        if (is_valid(i)) {
            state[level] = i;
            dfs(level + 1);
            state[level] = -1; // backtrack
        }
    }
}



🔹 8. DFS with Memoization (DP on Graphs)
// Used to compute DP on DAGs or trees.
int dfs(int u) {
    if (dp[u] != -1) return dp[u];
    dp[u] = 1;
    for (int v : adj[u]) {
        dp[u] = max(dp[u], 1 + dfs(v));
    }
    return dp[u];
}



🔹 9. DFS for Bridges and Articulation Points (Tarjan's Algo)
// Used in graph theory to find bridges and cut vertices.
void dfs(int u, int p) {
    tin[u] = low[u] = timer++;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (tin[v] != -1) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                // (u, v) is a bridge
            }
        }
    }
}



🔹 10. Iterative DFS
// DFS using stack (not recursion). Useful when recursion depth is an issue.
void iterativeDFS(int start) {
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int v : adj[u]) {
            if (!vis[v]) st.push(v);
        }
    }
}



🔹 11. DFS on Grids (2D DFS)
// Used in path finding, flood fill, island counting, etc.
void dfs(int x, int y) {
    vis[x][y] = true;
    for (auto [dx, dy] : directions) {
        int nx = x + dx, ny = y + dy;
        if (valid(nx, ny) && !vis[nx][ny]) {
            dfs(nx, ny);
        }
    }
}



🔹 12. Heavy-Light Decomposition (HLD DFS)
// Advanced DFS to decompose trees for range queries using segment trees.
// first dfs to compute sizes and heavy child
void dfs_sz(int u) {
    sz[u] = 1;
    for (int &v : adj[u]) {
        dfs_sz(v);
        sz[u] += sz[v];
        if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]); // heavy child first
    }
}



| Purpose               | DFS Variant               |
| --------------------- | ------------------------- |
| Traverse graph/tree   | Basic DFS                 |
| Tree processing       | Preorder / Postorder      |
| Subtree calculations  | Subtree DFS               |
| Euler tour / LCA      | DFS with time             |
| Topological sort      | Postorder DFS             |
| Cycle detection       | DFS with parent or colors |
| Solve puzzles / paths | Backtracking DFS          |
| DP on DAG/tree        | DFS with memo             |
| Bridges/cuts          | Tarjan's DFS              |
| Avoid recursion       | Iterative DFS             |
| Grid problems         | 2D DFS                    |
| Advanced trees        | HLD DFS                   |
