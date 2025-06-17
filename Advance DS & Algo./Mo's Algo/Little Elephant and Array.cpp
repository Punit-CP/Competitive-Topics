// https://codeforces.com/contest/221/problem/D     

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

struct Query
{
    int l, r, idx;
};

const int MAXN = 1e5 + 5;
int BLOCK;
int a[MAXN], answer[MAXN], freq[MAXN];

int current_answer = 0;

void add(int x)
{
    if (x >= MAXN)
        return;
    if (freq[x] == x)
        current_answer--;
    freq[x]++;
    if (freq[x] == x)
        current_answer++;
}

void remove(int x)
{
    if (x >= MAXN)
        return;
    if (freq[x] == x)
        current_answer--;
    freq[x]--;
    if (freq[x] == x)
        current_answer++;
}

void mo_algorithm(int n, int m, vector<Query> &queries)
{
    sort(all(queries), [&](const Query &a, const Query &b)
         {
    int block_a = a.l / BLOCK;
    int block_b = b.l / BLOCK;
    if (block_a != block_b)
        return block_a < block_b;
    return (block_a & 1) ? (a.r < b.r) : (a.r > b.r); });

    int l = 0, r = -1;
    for (auto q : queries)
    {
        while (l > q.l)
            add(a[--l]);
        while (r < q.r)
            add(a[++r]);
        while (l < q.l)
            remove(a[l++]);
        while (r > q.r)
            remove(a[r--]);
        answer[q.idx] = current_answer;
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    BLOCK = sqrt(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<Query> queries(m);
    for (int i = 0; i < m; i++)
    {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--; 
        queries[i].idx = i;
    }

    mo_algorithm(n, m, queries);

    for (int i = 0; i < m; i++)
        cout << answer[i] << '\n';
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
