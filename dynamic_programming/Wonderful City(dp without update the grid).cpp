// this teach how to go next state without update the state while in this problem updation was required but i didn't update and handle the cases beautifully 


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

const int inf = 1e18;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> h(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> h[i][j];

    vector<int> a(n), b(n);
    for (auto &i : a)
        cin >> i;
    for (auto &i : b)
        cin >> i;

    auto computeCost = [&](vector<int> &cost, vector<vector<int>> &grid) -> int
    {
        vector<vector<int>> dp(n, vector<int>(2, inf));
        dp[0][0] = 0;
        dp[0][1] = cost[0];

        for (int i = 1; i < n; i++)
        {
            for (int x = 0; x < 2; x++)
            {
                for (int y = 0; y < 2; y++)
                {
                    bool valid = true;
                    for (int j = 0; j < n; j++)
                    {
                        if (grid[i][j] + x == grid[i - 1][j] + y)
                        {
                            valid = false;
                            break;
                        }
                    }
                    if (valid)
                    {
                        dp[i][x] = min(dp[i][x], dp[i - 1][y] + (x ? cost[i] : 0));
                    }
                }
            }
        }
        return min(dp[n - 1][0], dp[n - 1][1]);
    };

    int horizontalCost = computeCost(a, h);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            swap(h[i][j], h[j][i]);
        }
    }

    int verticalCost = computeCost(b, h);
    int total = horizontalCost + verticalCost;

    if (total >= inf)
        cout << -1 << '\n';
    else
        cout << total << '\n';
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
