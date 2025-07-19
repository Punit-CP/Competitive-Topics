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
    int n, q;
    cin >> n >> q;
    vector<int> v(n), st(4 * n), lagy(4 * n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    // Built Tree
    function<void(int, int, int)> Built = [&](int idx, int start, int end) -> void
    {
        if (start == end)
        {
            st[idx] = v[start];
            return;
        }
        int mid = (start + end) / 2;
        Built(2 * idx + 1, start, mid);
        Built(2 * idx + 2, mid + 1, end);
        st[idx] = (st[2 * idx + 1] + st[2 * idx + 2]);
    };

    // Point Query
    function<int(int, int, int, int, int)> query = [&](int idx, int start, int end, int l, int r) -> int
    {
        if (r < start || l > end)
            return 0;
        if (l <= start && r >= end)
            return st[idx];
        int mid = (start + end) / 2;
        return query(2 * idx + 1, start, mid, l, r) + query(2 * idx + 2, mid + 1, end, l, r);
    };

    // Point Update
    function<void(int, int, int, int, int)> update = [&](int idx, int start, int end, int pos, int val) -> void
    {
        if (start == end)
        {
            st[idx] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (pos <= mid)
            update(2 * idx + 1, start, mid, pos, val);
        else
            update(2 * idx + 2, mid + 1, end, pos, val);
        st[idx] = st[2 * idx + 1] + st[2 * idx + 2];
    };

    // Push lazy value to children
    function<void(int, int, int)> push = [&](int idx, int start, int end) -> void
    {
        if (lagy[idx] != 0)
        {
            int len = end - start + 1;
            st[idx] += len * lagy[idx];
            if (start != end)
            {
                lagy[2 * idx + 1] += lagy[idx];
                lagy[2 * idx + 2] += lagy[idx];
            }
            lagy[idx] = 0;
        }
    };

    // Range Query
    function<int(int, int, int, int, int)> query = [&](int idx, int start, int end, int l, int r) -> int
    {
        push(idx, start, end);
        if (r < start || l > end)
            return 0;
        if (l <= start && r >= end)
            return st[idx];
        int mid = (start + end) / 2;
        return query(2 * idx + 1, start, mid, l, r) + query(2 * idx + 2, mid + 1, end, l, r);
    };

    // Range Update
    function<void(int, int, int, int, int, int)> update = [&](int idx, int start, int end, int l, int r, int val) -> void
    {
        push(idx, start, end);
        if (r < start || l > end)
        {
            return;
        }
        if (l <= start && r >= end)
        {
            int len = end - start + 1;
            st[idx] += len * val;
            if (start != end)
            {
                lagy[2 * idx + 1] += val;
                lagy[2 * idx + 2] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        update(2 * idx + 1, start, mid, l, r, val);
        update(2 * idx + 2, mid + 1, end, l, r, val);
        st[idx] = (st[2 * idx + 1] + st[2 * idx + 2]);
    };
    Built(0, 0, n - 1);
    while (q--)
    {
        int k;
        cin >> k;
        if (k == 1)
        {
            int l, r, val;
            cin >> l >> r >> val;
            l--;
            r--;
            update(0, 0, n - 1, l, r, val);
        }
        else
        {
            int pos;
            cin >> pos;
            pos--;
            cout << query(0, 0, n - 1, pos, pos) << endl;
        }
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
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
