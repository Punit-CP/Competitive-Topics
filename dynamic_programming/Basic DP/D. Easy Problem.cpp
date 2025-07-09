https://codeforces.com/contest/1096/problem/D

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
    string s;
    cin >> s;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(5, LLONG_MAX));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (dp[i - 1][j] == LLONG_MAX)
                continue;

            if (j == 0)
            {
                if (s[i - 1] == 'h')
                {
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j]);    // take
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + v[i - 1]); // not take
                }
                else
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                }
            }
            if (j == 1)
            {
                if (s[i - 1] == 'a')
                {
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j]);    // take
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + v[i - 1]); // not take
                }
                else
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                }
            }
            if (j == 2)
            {
                if (s[i - 1] == 'r')
                {
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j]);    // take
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + v[i - 1]); // not take
                }
                else
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                }
            }
            if (j == 3)
            {
                if (s[i - 1] == 'd')
                {
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j]);    // take
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + v[i - 1]); // not take
                }
                else
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                }
            }
        }
    }

    int ans = min({dp[n][0], dp[n][1], dp[n][2], dp[n][3]});
    cout << ans << endl;
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
