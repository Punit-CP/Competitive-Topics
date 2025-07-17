https://codeforces.com/contest/1974/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long
constexpr int INF = 1e18;
constexpr int MAX_H = 1e5 + 5;

int cost[55], happy[55];

void solve()
{
    int n, x;
    cin >> n >> x;

    for (int i = 0; i < n; ++i)
    {
        cin >> cost[i] >> happy[i];
    }

    int total_happy = accumulate(happy, happy + n, 0LL);

    vector<int> dp(total_happy + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < n; ++i)
    {
        vector<int> ndp = dp;
        for (int j = 0; j <= total_happy; ++j)
        {
            if (dp[j] == INF)
                continue;
            int jj = j + happy[i];
            int new_cost = dp[j] + cost[i];
            if (new_cost <= i * x)
                ndp[jj] = min(ndp[jj], new_cost);
        }
        dp = ndp;
    }

    for (int i = total_happy; i >= 0; --i)
    {
        if (dp[i] != INF)
        {
            cout << i << '\n';
            return;
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
