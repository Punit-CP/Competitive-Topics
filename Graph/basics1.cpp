// this is simple cycle detection in undirected graph , and the main curx in this is that , how i am handling the previous virtices using px , py
// https://codeforces.com/contest/510/problem/B
// B. Fox And Two Dots

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

int d[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

bool dfs(vector<vector<char>> &v, vector<vector<bool>> &vis, int px, int py, int i, int j, int n, int m)
{
    // Mark the cell as visited
    vis[i][j] = true;

    for (int k = 0; k < 4; k++)
    {
        int newx = i + d[k][0], newy = j + d[k][1];

        // Check bounds
        if (newx >= 0 && newx < n && newy >= 0 && newy < m)
        {
            if (v[newx][newy] == v[i][j]) 
            {
                // If already visited and not the previous cell, cycle found
                if (vis[newx][newy] && !(newx == px && newy == py))
                    return true;

                // If not visited, continue DFS
                if (!vis[newx][newy])
                {
                    if (dfs(v, vis, i, j, newx, newy, n, m))
                        return true;
                }
            }
        }
    }
    return false;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
        }
    }

    // Run DFS from every unvisited cell
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!vis[i][j])
            {
                if (dfs(v, vis, -1, -1, i, j, n, m))
                {
                    cout << "YES\n";
                    return;
                }
            }
        }
    }
    cout << "NO\n";
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
