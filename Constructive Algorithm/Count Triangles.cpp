//   https://codeforces.com/contest/1355/problem/C

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

const int N = 1e6 + 10; 

int a[N];

void solve()
{
    memset(a, 0, sizeof a); 
    int A, B, C, D;
    cin >> A >> B >> C >> D;

    // Build Range Frequencies for (x + y)
    for (int i = A; i <= B; i++)
    {
        a[i + B]++;
        a[i + C + 1]--;
    }

    // not a[s]= no. of pairs such that x+y=s and A<=x<=B, B<=y<=C
    for (int i = 1; i < N; i++)
        a[i] += a[i - 1];

    // Now a[i] = number of pairs (x, y) such that x+y<=i
    for (int i = 1; i < N; i++)
        a[i] += a[i - 1];
    
    // This helps quickly compute number of pairs (𝑥,𝑦)(x,y) where 𝑥+𝑦>𝑧
    // by:count=total pairs−number of pairs where 𝑥+𝑦≤𝑧     so  count=total pairs−number of pairs where x+y≤z
    int ans = 0;
    for (int i = C; i <= D; i++)
    {
        ans += a[N - 1] - a[i];
    }

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
