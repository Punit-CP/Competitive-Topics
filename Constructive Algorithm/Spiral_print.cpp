// // n=4
// 9 2 1 8 
// 10 3 0 7 
// 11 4 5 6 
// 12 13 14 15 

// n=5
// 12  11 10 9 24 
// 13  2  1  8 23 
// 14  3  0  7 22 
// 15  4  5  6 21 
// 16 17 18 19 20 






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
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n, -1));

    int x = n / 2;
    int y = n / 2;
    if (n % 2 == 0)
        x--;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};
    int dir = 0, steps = 1, filled = 0, val = 0;

    v[x][y] = val++;
    filled++;

    while (filled < n * n)
    {
        for (int d = 0; d < 2; ++d)
        {
            for (int k = 0; k < steps; ++k)
            {
                x += dx[dir];
                y += dy[dir];
                if (x >= 0 && x < n && y >= 0 && y < n)
                {
                    v[x][y] = val++;
                    filled++;
                }
            }
            dir = (dir + 1) % 4;
        }
        steps++;
    }

    for (auto &row : v)
    {
        for (auto j : row)
            cout << j << " ";
        cout << "\n";
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
