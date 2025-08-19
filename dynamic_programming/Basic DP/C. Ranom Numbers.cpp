https://codeforces.com/contest/1841/problem/C


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

int d[5] = {1, 10, 100, 1000, 10000};

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = s[i] - 'A';

    // dp[i][j][k]: max till i such that last max character is j and operation performed till i is k
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(6, vector<int>(2, -1)));

    vector<int> pw(6);
    pw[0] = 1;
    for (int i = 1; i < 6; i++)
        pw[i] = pw[i - 1] * 10;

    function<int(int, int, int)> ok = [&](int i, int mx, int op) -> int
    {
        if (i < 0)
            return 0;
        if (dp[i][mx][op] != -1)
            return dp[i][mx][op];

        int sign = (v[i] < mx ? -1 : 1);
        int ans = sign * pw[v[i]] + ok(i - 1, max(mx, v[i]), op);

        if (op == 0)
        {
            for (int j = 0; j < 5; j++)
            {
                if (v[i] == j)
                    continue;
                int sign2 = (j < mx ? -1 : 1);
                ans = max(ans, sign2 * pw[j] + ok(i - 1, max(mx, j), 1));
            }
        }
        return dp[i][mx][op] = ans;
    };
    cout << ok(n - 1, 0, 0) << endl;
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
