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
const int N = 1005;

int n, q;
char grid[N][N];
int st[4 * N][4 * N];

// Build column segment tree for node_row in row range [r1, r2]
void build_col(int node_row, int r1, int r2, int node_col, int c1, int c2)
{
    if (c1 == c2)
    {
        if (r1 == r2)
        {
            st[node_row][node_col] = (grid[r1][c1] == '*');
        }
        else
        {
            st[node_row][node_col] = st[2 * node_row][node_col] + st[2 * node_row + 1][node_col];
        }
        return;
    }

    int mid = (c1 + c2) / 2;
    build_col(node_row, r1, r2, 2 * node_col, c1, mid);
    build_col(node_row, r1, r2, 2 * node_col + 1, mid + 1, c2);
    st[node_row][node_col] = st[node_row][2 * node_col] + st[node_row][2 * node_col + 1];
}

// Build row segment tree
void build_row(int node_row, int r1, int r2)
{
    if (r1 == r2)
    {
        build_col(node_row, r1, r2, 1, 0, n - 1);
        return;
    }

    int mid = (r1 + r2) / 2;
    build_row(2 * node_row, r1, mid);
    build_row(2 * node_row + 1, mid + 1, r2);
    build_col(node_row, r1, r2, 1, 0, n - 1);
}

// Query in column segment tree
int query_col(int node_row, int node_col, int c1, int c2, int qc1, int qc2)
{
    if (qc2 < c1 || c2 < qc1)
        return 0;
    if (qc1 <= c1 && c2 <= qc2)
        return st[node_row][node_col];

    int mid = (c1 + c2) / 2;
    return query_col(node_row, 2 * node_col, c1, mid, qc1, qc2) +
           query_col(node_row, 2 * node_col + 1, mid + 1, c2, qc1, qc2);
}

// Query in full 2D segment tree
int query_row(int node_row, int r1, int r2, int qr1, int qr2, int qc1, int qc2)
{
    if (qr2 < r1 || r2 < qr1)
        return 0;
    if (qr1 <= r1 && r2 <= qr2)
        return query_col(node_row, 1, 0, n - 1, qc1, qc2);

    int mid = (r1 + r2) / 2;
    return query_row(2 * node_row, r1, mid, qr1, qr2, qc1, qc2) +
           query_row(2 * node_row + 1, mid + 1, r2, qr1, qr2, qc1, qc2);
}

// Update in column segment tree
void update_col(int node_row, int r1, int r2, int node_col, int c1, int c2, int ur, int uc, int val)
{
    if (c1 == c2)
    {
        if (r1 == r2)
        {
            st[node_row][node_col] = val;
        }
        else
        {
            st[node_row][node_col] = st[2 * node_row][node_col] + st[2 * node_row + 1][node_col];
        }
        return;
    }

    int mid = (c1 + c2) / 2;
    if (uc <= mid)
        update_col(node_row, r1, r2, 2 * node_col, c1, mid, ur, uc, val);
    else
        update_col(node_row, r1, r2, 2 * node_col + 1, mid + 1, c2, ur, uc, val);

    st[node_row][node_col] = st[node_row][2 * node_col] + st[node_row][2 * node_col + 1];
}

// Update in row tree
void update_row(int node_row, int r1, int r2, int ur, int uc, int val)
{
    if (r1 == r2)
    {
        update_col(node_row, r1, r2, 1, 0, n - 1, ur, uc, val);
        return;
    }

    int mid = (r1 + r2) / 2;
    if (ur <= mid)
        update_row(2 * node_row, r1, mid, ur, uc, val);
    else
        update_row(2 * node_row + 1, mid + 1, r2, ur, uc, val);

    update_col(node_row, r1, r2, 1, 0, n - 1, ur, uc, val);
}

void solve()
{
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
        {
            grid[i][j] = s[j];
        }
    }

    build_row(1, 0, n - 1);

    while (q--)
    {
        string type;
        cin >> type;
        if (type == "Q")
        {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        --r1, --c1, --r2, --c2;
        cout << query_row(1, 0, n - 1, r1, r2, c1, c2) << '\n';
        }
        else if (type == "U")
        {
            int r, c;
            cin >> r >> c;
            --r, --c;
            grid[r][c] = (grid[r][c] == '*') ? '.' : '*';
            update_row(1, 0, n - 1, r, c, (grid[r][c] == '*'));
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
