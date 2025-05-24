#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
using namespace std;

#define int long long
#define ull unsigned long long
#define lld long double
#define  ff first
#define  ss second
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
constexpr int L = 232792560;
#define mod 1000000007
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
template <class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag,tree_order_statistics_node_update>;

typedef priority_queue<long long> maxheap;
typedef priority_queue<long long, vector<long long>, greater<long long>> minheap;

// ------------------------ KMP ALGORITHM START ------------------------

// Builds LPS (Longest Prefix Suffix) array
vector<int> buildLPS(const string &pat) {
    int m = pat.size();
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
                // len--;
            } else {
                lps[i++] = 0;
                //i++;
            }
        }
    }
    return lps;
}

// Returns 1-based indices of all occurrences of pat in txt
vector<int> KMPSearch(const string &pat, const string &txt) {
    int m = pat.size(), n = txt.size();
    vector<int> lps = buildLPS(pat);
    vector<int> indices;
    int i = 0, j = 0;
    while (i < n) {
        if (pat[j] == txt[i]) {
            i++; j++;
        }
        if (j == m) {
            indices.pb(i - j + 1); // +1 for 1-based indexing
            j = lps[j - 1];
        } else if (pat[j] != txt[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return indices;
}

// ------------------------ KMP ALGORITHM END ------------------------

void solve()
{
    string txt, pat;
    cin >> txt >> pat;
    vector<int> matches = KMPSearch(pat, txt);
    for (int idx : matches) cout << idx << " ";
    cout << "\n";
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
    while (t--) {
        solve();
    }
    return 0;
}

