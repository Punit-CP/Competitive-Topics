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

// ------------------------- Mo's Algorithm Template -------------------------

const int MAXN = 1e5 + 5; // Increase if needed
int BLOCK;

struct Query {
    int l, r, idx;
};

int a[MAXN];        // Input array
int answer[MAXN];   // Stores answers for queries
int freq[MAXN];     // Frequency of elements

// ------------------------ Choose Use Case ------------------------

// Case 1: Count of elements with frequency exactly equal to their value
int current_answer = 0;

void add(int x) {
    if (x >= MAXN) return;
    if (freq[x] == x) current_answer--;
    freq[x]++;
    if (freq[x] == x) current_answer++;
}

void remove(int x) {
    if (x >= MAXN) return;
    if (freq[x] == x) current_answer--;
    freq[x]--;
    if (freq[x] == x) current_answer++;
}

/*
// Case 2: Count of distinct elements in range
int current_answer = 0;

void add(int x) {
    if (++freq[x] == 1) current_answer++;
}

void remove(int x) {
    if (--freq[x] == 0) current_answer--;
}
*/

/*
// Case 3: Sum of elements in the range
int current_answer = 0;

void add(int x) {
    current_answer += x;
}

void remove(int x) {
    current_answer -= x;
}
*/

/*
// Case 4: Maximum frequency of any element in the range
int current_answer = 0;
int freq_bucket[MAXN];

void add(int x) {
    freq_bucket[freq[x]]--;
    freq[x]++;
    freq_bucket[freq[x]]++;
    current_answer = max(current_answer, freq[x]);
}

void remove(int x) {
    freq_bucket[freq[x]]--;
    if (freq[x] == current_answer && freq_bucket[freq[x]] == 0)
        current_answer--;
    freq[x]--;
    freq_bucket[freq[x]]++;
}
*/

void mo_algorithm(int n, vector<Query> &queries)
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


// ------------------------- Solve Function -------------------------

void solve() {
    int n, q;
    cin >> n >> q;
    BLOCK = sqrt(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--, queries[i].r--; // Convert to 0-based indexing
        queries[i].idx = i;
    }

    mo_algorithm(n, queries);

    for (int i = 0; i < q; i++)
        cout << answer[i] << '\n';
}

// ------------------------- Main -------------------------

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}


// ❌ Don’t Use Mo’s Algorithm When:
// | Condition                                   | Reason                             |
// | ------------------------------------------- | ---------------------------------- |
// | Queries depend on dynamic updates           | Mo's is for static arrays only     |
// | You need answers in the same order as input | Mo's reorders queries offline      |
// | Problem asks for "first/last occurrence"    | Hard to maintain with add/remove   |
// | Problem uses prefix/suffix structure        | Better to use prefix/suffix arrays |

// 🧠 Intuition Rule:
// ❝ If the problem is “answer many range queries on a static array”, and you can maintain the result with add/remove logic, then Mo’s Algorithm is a great fit. ❞

// ✅ Classic Problems Where Mo’s Works:
// | Condition                                       | Answer |
// | ----------------------------------------------- | ------ |
// | Are all queries on a **static array**?          | ✅ Yes  |
// | Are all queries given **beforehand**?           | ✅ Yes  |
// | Can you maintain the answer using `add/remove`? | ✅ Yes  |
// | Are you asked to **answer many queries**?       | ✅ Yes  |
// → If all are Yes, use Mo's Algorithm.
