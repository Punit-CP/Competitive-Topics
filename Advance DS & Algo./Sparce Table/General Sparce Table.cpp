// This is Template for sparce table



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

// =================== Sparse Table (Generic + Idempotent) ===================
template <typename T, class F>
struct SparseTable
{
    int n, maxLog;
    vector<vector<T>> st;
    F func;
    bool is_idempotent;

    SparseTable() {}

    SparseTable(const vector<T> &a, F f, bool idem = false) : func(f), is_idempotent(idem)
    {
        n = a.size();
        maxLog = 32 - __builtin_clz(n);
        st.assign(maxLog, vector<T>(n));
        st[0] = a;
        for (int j = 1; j < maxLog; ++j)
        {
            for (int i = 0; i + (1 << j) <= n; ++i)
            {
                st[j][i] = func(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // O(log n) for general associative; O(1) for idempotent
    T query(int l, int r)
    {
        if (is_idempotent)
        {
            int j = 31 - __builtin_clz(r - l + 1);
            return func(st[j][l], st[j][r - (1 << j) + 1]);
        }
        else
        {
            T res = st[0][l];
            for (int j = maxLog - 1; j >= 0; --j)
            {
                if ((1 << j) <= r - l + 1)
                {
                    res = func(res, st[j][l]);
                    l += (1 << j);
                }
            }
            return res;
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> v(n), d(n - 1);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    // For generic associative function like sum, xor:
    // Example: Range Sum Query
    SparseTable<int, function<int(int, int)>> st(v, [](int a, int b)
                                                     { return a + b; }, false); // O(log n) query

    // For idempotent function ((a func a)==a) like min, max, gcd:
    SparseTable<int, function<int(int, int)>> st(v, [](int a, int b)
                                                     { return __gcd(a, b); }, true); // O(1) query
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n'; // Here (l and r) 0-based indexing 
    }
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
