//  https://codeforces.com/contest/271/problem/D
// this is my first problem which i have solved using trie


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

class TrieNode
{
public:
    bool isWord;
    TrieNode *child[26];
    TrieNode()
    {
        isWord = 0;
        for (int i = 0; i < 26; i++)
        {
            child[i] = 0;
        }
    }
};

void solve()
{
    TrieNode *head = new TrieNode();
    int ans = 0;
    string s;
    cin >> s;
    string mask;
    cin >> mask;
    int k;
    cin >> k;
    for (int i = 0; i < s.size(); i++)
    {
        TrieNode *temp = head;
        int bad = 0;
        for (int j = i; j < s.size(); j++)
        {
            char ch = s[j];
            int ind = ch - 'a';
            if (mask[ind] == '0')
            {
                bad++;
            }
            if (bad > k)
                break;
            if (temp->child[ind] == NULL)
            {
                temp->child[ind] = new TrieNode();
                temp->isWord = 1;
                ans++;
            }
            temp = temp->child[ind];
        }
    }
    cout << ans << "\n";
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
