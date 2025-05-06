// This problem teach us how to solve basic dp on trees problem 

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
    vector<int> l(n + 1), r(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    vector<int> adj[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> l[i] >> r[i];
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    function<void(int, int)> dfs = [&](int u, int p) -> void
    {
        for (auto v : adj[u])
        {
            if (v == p)
                continue;
            dfs(v, u);
        }
        for (auto v : adj[u])
        {
            if (v == p)
                continue;
            dp[u][0] += max(abs(l[u] - l[v]) + dp[v][0], abs(l[u] - r[v]) + dp[v][1]);
            dp[u][1] += max(abs(r[u] - l[v]) + dp[v][0], abs(r[u] - r[v]) + dp[v][1]);
        }
    };

    dfs(1, -1);
    cout << max(dp[1][0], dp[1][1]) << endl;
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
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
