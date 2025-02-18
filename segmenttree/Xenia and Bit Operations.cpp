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

class Node
{
public:
    int level;
    int ans;

    Node() : level(0), ans(0) {}
    Node(int val) : level(1), ans(val) {} 
};

Node combine(Node &a, Node &b)
{
    Node c;
    c.level = a.level + 1; 
    if (c.level % 2 == 0)
    {
        c.ans = a.ans | b.ans;
    }
    else
    {
        c.ans = a.ans ^ b.ans;
    }
    return c;
}

void build(vector<Node> &tree, vector<int> &a, int n)
{
    for (int i = 0; i < n; i++)
    {
        tree[i + n] = Node(a[i]);
    }
    for (int i = n - 1; i > 0; i--)
    {
        tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
    }
}

void update(vector<Node> &tree, int n, int p, int v)
{
    p += n;
    tree[p] = Node(v);
    while (p > 1)
    {
        p /= 2;
        tree[p] = combine(tree[2 * p], tree[2 * p + 1]);
    }
}

void solve()
{
    int n, q;
    cin >> n >> q;
    n = 1 << n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    vector<Node> tree(2 * n);
    build(tree, v, n);

    while (q--)
    {
        int l, val;
        cin >> l >> val;
        l--;
        update(tree, n, l, val);
        cout << tree[1].ans << endl; 
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
