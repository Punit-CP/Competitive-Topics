// https://codeforces.com/problemset/problem/706/D

🔢 What is a Bitwise Trie?
A Bitwise Trie is a tree where:
Each node has two children: 0 and 1.
Each path from root to leaf represents a number in binary form.
Each level represents a bit position — we usually go from the most significant bit (MSB) to the least significant bit (LSB).

In this problem --> We are told:
1 ≤ x ≤ 1e9
So the largest number is < 2^30, meaning:
We need 30 bits, so our Trie has 30 levels.

Trie Node Structure-->
Each node should: Have a child for 0 and 1.
Optionally, keep a count to support multiple insertions and deletions (multiset).





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

struct TrieNode
{
    TrieNode *child[2];
    int count;
    TrieNode()
    {
        child[0] = child[1] = nullptr;
        count = 0;
    }
};
void insert(TrieNode *root, int num)
{
    TrieNode *node = root;
    for (int i = 29; i >= 0; --i)
    {
        int bit = (num >> i) & 1;
        if (!node->child[bit])
            node->child[bit] = new TrieNode();
        node = node->child[bit];
        node->count++;
    }
}

void remove(TrieNode *root, int num)
{
    TrieNode *node = root;
    for (int i = 29; i >= 0; --i)
    {
        int bit = (num >> i) & 1;
        node = node->child[bit];
        node->count--;
    }
}
int maxXor(TrieNode *root, int x)
{
    TrieNode *node = root;
    int ans = 0;
    for (int i = 29; i >= 0; i--)
    {
        int bit = (x >> i) & 1;
        int preferred = 1 - bit;
        if (node->child[preferred] && node->child[preferred]->count > 0)
        {
            ans |= (1 << i);
            node = node->child[preferred];
        }
        else
        {
            node = node->child[bit];
        }
    }
    return ans;
}

void solve()
{
    int q;
    cin >> q;
    TrieNode *root = new TrieNode();
    insert(root, 0);
    for (int i = 0; i < q; i++)
    {
        char type;
        int x;
        cin >> type >> x;
        if (type == '+')
            insert(root, x);
        else if (type == '-')
            remove(root, x);
        else
            cout << maxXor(root, x) << '\n';
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

