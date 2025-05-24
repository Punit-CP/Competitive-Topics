// Manacher's Algorithm is a powerful linear-time algorithm used to find palindromic substrings in a string.
// | Task                                | Manacher Benefit |
// | ----------------------------------- | ---------------- |
// | Longest palindromic substring       | ✅ Linear time    |
// | Count palindromic substrings        | ✅ Linear time    |
// | Palindrome substring check \[l, r]  | ✅ Constant time  |
// | Longest palindromic prefix/suffix   | ✅ Efficient      |
// | Substring-based palindrome problems | ✅ Fast checking  |

// Y-Tube video link:  https://www.youtube.com/watch?v=ei7qghJEj4Y&ab_channel=VivekGupta

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

// ---- MANACHER ALGORITHM STRUCT ----
struct Manacher
{
    vector<int> p;
    string t;

    void run_manacher(const string &s)
    {
        int n = s.length();
        p.assign(n, 1);
        int l = 1, r = 1;

        for (int i = 1; i < n; i++)
        {
            p[i] = max(0LL, min(r - i, p[l + r - i]));
            while (i + p[i] < n && i - p[i] >= 0 && s[i + p[i]] == s[i - p[i]])
            {
                p[i]++;
            }
            if (i + p[i] > r)
            {
                l = i - p[i];
                r = i + p[i];
            }
        }
    }

    void build(const string &s)
    {
        t = "#";
        for (char c : s)
        {
            t += c;
            t += "#";
        }
        run_manacher(t);
    }

    int getLongest(int cen, bool odd)
    {
        int pos = 2 * cen + 1 + (!odd);
        return p[pos] - 1;
    }

    void print()
    {
        for (auto i : p)
            cout << i << " ";
    }

    string findmaxPalindrome()
{
    int pos = -1, len = 0;

    for (int i = 0; i < p.size(); i++)
    {
        if (p[i] > len)
        {
            len = p[i];
            pos = i;
        }
    }

    int start = pos - len + 1;
    int end = pos + len - 1;

    string res = "";
    for (int i = start; i <= end; i++)
    {
        if (t[i] != '#')
            res += t[i];
    }

    return res;
}


    bool checkPalin(int l, int r)
    {
        int len = r - l + 1;
        int cen = (l + r) / 2;
        bool odd = (l % 2 == r % 2);
        return getLongest(cen, odd) >= len;
    }
};

// ---- DRIVER CODE ----
void solve()
{
    string s;
    cin >> s;
    int i = 0, n = s.size();
    string ans = "";

    while (i < n - i - 1 && s[i] == s[n - i - 1])
    {
        ans += s[i];
        i++;
    }

    string mid = s.substr(i, n - 2 * i);
    // cout << mid << "  ";
    Manacher m;
    m.build(mid);
    string pal = m.findmaxPalindrome();
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
