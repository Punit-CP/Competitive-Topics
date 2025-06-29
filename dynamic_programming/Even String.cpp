// https://codeforces.com/contest/2086/problem/D
// youTube-> https://www.youtube.com/watch?v=PXdVid6Yjo4&t=3250s&ab_channel=TLEEliminators-byPriyansh

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define int long long
#define ull unsigned long long
#define ff first
#define ss second
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
const int mod = 998244353;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef priority_queue<long long> maxheap;
typedef priority_queue<long long, vector<long long>, greater<long long>> minheap;

vector<int> fact;
vector<int> ifact;

int binary_exponentiation(int a, int b, int m)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = (1LL * ans * a) % m;
        }
        a = (1LL * a * a) % m;
        b >>= 1;
    }
    return ans % m;
}

int mod_mul(int a, int b, int m)
{
    return (1LL * a * b) % m;
}

int mod_inv(int a, int m)
{
    return binary_exponentiation(a, m - 2, m);
}

void precompute_factorials(int n)
{
    fact.resize(n + 1);
    ifact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fact[i] = mod_mul(fact[i - 1], i, mod);
    }
    ifact[n] = mod_inv(fact[n], mod);
    for (int i = n - 1; i >= 0; i--)
    {
        ifact[i] = mod_mul(ifact[i + 1], i + 1, mod);
    }
}

void solve()
{
    vector<int> v(26);
    for (int i = 0; i < 26; i++)
    {
        cin >> v[i];
    }

    int total = accumulate(all(v), 0LL);
    int a = (total + 1) / 2;
    int b = total / 2;

    int prod = 1;
    for (int num : v)
    {
        if (num == 0)
            continue;
        prod = mod_mul(prod, fact[num], mod);
    }
    int inv_prod = mod_inv(prod, mod);

    vector<int> dp(total + 1, 0);
    dp[0] = 1;
    for (int num : v)
    {
        if (num == 0)
            continue;
        for (int i = total; i >= num; i--)
        {
            dp[i] = (dp[i] + dp[i - num]) % mod;
        }
    }

    if (dp[a] == 0)
    {
        cout << 0 << endl;
        return;
    }
    int res = mod_mul(inv_prod, mod_mul(mod_mul(dp[a], fact[a], mod), fact[b], mod), mod);
    cout << res << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    precompute_factorials(5e5 + 10);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
