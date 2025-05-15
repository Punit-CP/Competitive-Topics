// https://codeforces.com/problemset/problem/459/D


#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

int BIT[MAXN]; // Binary Indexed Tree

void update(int index, int value) {
    while (index < MAXN) {
        BIT[index] += value;
        index += index & -index;
    }
}

int query(int index) {
    int res = 0;
    while (index > 0) {
        res += BIT[index];
        index -= index & -index;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n), left_count(n), right_count(n);
    unordered_map<int, int> freq_left, freq_right;

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    // Build left_count
    for (int i = 0; i < n; ++i) {
        freq_left[a[i]]++;
        left_count[i] = freq_left[a[i]];
    }

    // Build right_count
    for (int i = n - 1; i >= 0; --i) {
        freq_right[a[i]]++;
        right_count[i] = freq_right[a[i]];
    }

    long long ans = 0;

    // Traverse from right to left, using BIT
    for (int i = n - 1; i >= 0; --i) {
        ans += query(left_count[i] - 1);      // How many elements to the right of i have right_count[j] < left_count[i]
        update(right_count[i], 1);
    }

    cout << ans << "\n";
    return 0;
}
