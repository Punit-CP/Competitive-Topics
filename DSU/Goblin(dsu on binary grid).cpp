// This problem teach us how we can do operation on binary grid 

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

class UnionFind
{
private:
    vector<int> p, rank, sz;

public:
    UnionFind(int n)
    {
        rank.assign(n, 0);
        p.assign(n, 0);
        sz.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }

    int findSet(int i)
    {
        return (p[i] == i) ? i : p[i] = findSet(p[i]);
    }

    bool isSameSet(int i, int j)
    {
        return findSet(i) == findSet(j);
    }

    void unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        {
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y])
            {
                p[y] = x;
                sz[x] += sz[y];
            }
            else
            {
                p[x] = y;
                sz[y] += sz[x];
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }

    void setSize(int i, int val)
    {
        sz[i] = val;
    }

    int getSize(int i)
    {
        return sz[findSet(i)];
    }

    int getMaxSize()
    {
        int mx = 0;
        for (int i = 0; i < (int)sz.size(); i++)
        {
            mx = max(mx, sz[findSet(i)]);
        }
        return mx;
    }
};

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    UnionFind dsu(3 * n);
    for (int i = 0; i < n; i++)
    {
        int x = 3 * i, y = x + 1, z = y + 1;
        dsu.setSize(x, (s[i] == '0' ? i : 0));
        dsu.setSize(y, (s[i] == '0' ? 0 : 1));
        dsu.setSize(z, (s[i] == '0' ? n - i - 1 : 0));
    }

    for (int i = 1; i < n; i++)
    {
        char c = s[i];
        int x = 3 * i, y = x + 1, z = y + 1;
        int X = 3 * (i - 1), Y = X + 1, Z = Y + 1;

        if (c == '0')
        {
            dsu.unionSet(x, X);
            dsu.unionSet(z, Z);
            dsu.unionSet(x, Y);
        }
        else
        {
            dsu.unionSet(y, Z);
        }
    }

    cout << dsu.getMaxSize() << endl;
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
