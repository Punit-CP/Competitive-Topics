// this is beautifully handle the bigger subproblem using smaller subproblems
// and i learn this technique (https://www.youtube.com/watch?v=lMny-GZD0IA) Naman Bansal 
// transiton is dp[i]= (dp[i-1] + dp[i-2] ....... dp[1]) + divisors[i]

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
#define mod 998244353
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef priority_queue<long long> maxheap;
typedef priority_queue<long long, vector<long long>, greater<long long>> minheap;
const int N = 1e6 + 10;
int divisors[N];
int precomputed()
{
    for (int i = 1; i < N; i++)
    {
        divisors[i] = 1;
    }
    for (int i = 2; i < N; i++)
    {
        for (int j = i; j < N; j += i)
        {
            divisors[j]++;
        }
    }
}
int mod_add(int a, int b, int m)
{
    return (a % m + (b + m) % m) % m;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> dp(n + 1, 0), prefix(n + 1, 0);

    dp[1] = divisors[1];
    prefix[1] = dp[1];

    for (int i = 2; i <= n; i++)
    {
        dp[i] = mod_add(prefix[i - 1], divisors[i], mod);
        prefix[i] = mod_add(prefix[i - 1], dp[i], mod);
    }
    cout << dp[n] << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif
    precomputed();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
