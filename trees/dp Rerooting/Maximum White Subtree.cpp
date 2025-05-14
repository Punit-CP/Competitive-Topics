// https://codeforces.com/problemset/problem/1324/F



// Method-1
#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> color(n + 1); // 1 for white, 0 for black
    for (int i = 1; i <= n; i++)
    {
        cin >> color[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dp(n + 1), res(n + 1);

    function<void(int, int)> dfs = [&](int u, int p)
    {
        dp[u] = (color[u] == 1 ? 1 : -1);
        for (int v : adj[u])
        {
            if (v == p) continue;
            dfs(v, u);
            dp[u] += max(0LL, dp[v]);
        }
    };

    function<void(int, int)> reroot = [&](int u, int p)
    {
        res[u] = dp[u];
        for (int v : adj[u])
        {
            if (v == p) continue;

            int orig_u = dp[u];
            int orig_v = dp[v];

            // Reroot: remove v's contribution from u, add u's to v
            dp[u] -= max(0LL, dp[v]);
            dp[v] += max(0LL, dp[u]);

            reroot(v, u);

            // Restore
            dp[u] = orig_u;
            dp[v] = orig_v;
        }
    };

    dfs(1, 0);
    reroot(1, 0);

    for (int i = 1; i <= n; i++)
        cout << res[i] << " ";
    cout << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();

    return 0;
}




// Method-2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define int long long
#define ull unsigned long long
#define lld long double
#define ff first
#define ss second
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
constexpr int L = 232792560;
#define mod 1000000007
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef priority_queue<long long> maxheap;
typedef priority_queue<long long, vector<long long>, greater<long long>> minheap;

void solve()
{
    int n;
    cin >> n;
    vector<int> v(n + 1), adj[n + 1], dp(n + 1), res(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
    }
    for (int i = 1; i < n; i++)
    {
        int u, vv;
        cin >> u >> vv;
        adj[u].pb(vv);
        adj[vv].pb(u);
    }

    function<int(int, int)> dfs = [&](int u, int p) -> int
    {
        dp[u] = (v[u] == 0 ? -1 : 1);
        for (auto i : adj[u])
        {
            if (i == p)
                continue;
            dfs(i, u);
            dp[u] += max(dp[i], 0LL);
        }
        return dp[u];
    };

    function<void(int, int, int)> reroot = [&](int u, int p, int ans) -> void
    {
        res[u] = ans;
        for (auto i : adj[u])
        {
            if (i == p)
                continue;
            int without_i = ans - max(0LL, dp[i]);
            int new_dp_i = dp[i] + max(0LL, without_i);
            reroot(i, u, new_dp_i);
        }
    };

    int root_val = dfs(1, 0);
    reroot(1, 0, root_val);

    for (int i = 1; i <= n; i++)
        cout << res[i] << " ";
    cout << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}




// | Aspect                           | **First Version (Correct, `dp[u]` is mutable)**                                | **Second Version (Functional rerooting)**                                            |
// | -------------------------------- | ------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------ |
// | **Rerooting function signature** | `void reroot(int u, int p)`                                                    | `void reroot(int u, int p, int ans)`                                                 |
// | **Technique**                    | Temporarily modifies `dp[u]` and `dp[v]` during traversal, then restores them. | Uses `ans` to carry final answer as it reroots; doesn't change `dp[]` during reroot. |
// | **State management**             | Destructive (modifies state, saves and restores it)                            | Pure functional (no mutation of state)                                               |
// | **Clarity**                      | Easier to implement and debug locally                                          | Slightly more elegant and "functional", but harder to reason about                   |
// | **Final output**                 | Uses `res[u] = dp[u]` after modifying `dp`                                     | Uses `res[u] = ans` passed from above                                                |






