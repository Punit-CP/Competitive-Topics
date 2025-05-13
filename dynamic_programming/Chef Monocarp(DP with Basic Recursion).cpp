// https://codeforces.com/contest/1437/problem/C


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
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(all(v)); 

    vector<vector<int>> dp(n + 1, vector<int>(2 * n + 1, -1));

    function<int(int, int)> ok = [&](int i, int j) -> int
    {
        if (i == n)
            return 0;
        if (j == 2 * n)  //This condition checks whether you have run out of available values in the [1, 2n] range to assign to v[i] . If j == 2 * n, that means you've tried all 2n values, and there are no values left to assign.
              return 1e18;         // But i is still less than n, so you haven't matched all v[i] yet. In this case, you return a very large value (1e18) to indicate this path is invalid and should not be chosen.

        if (dp[i][j] != -1) return dp[i][j];

        // Option 1: Assign a[j] to v[i]
        int assign = abs(v[i] - (j + 1)) + ok(i + 1, j + 1);
        // Option 2: Skip a[j]
        int skip = ok(i, j + 1);

        return dp[i][j] = min(assign, skip);
    };

    cout << ok(0, 0) << '\n';
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
