// This is the problem like Finding the Number of sequence 

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define int long long
#define mod 1000000007

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 1e5 + 10;
int dp[N];
int t, k;

void preprocess()
{
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i < N; i++)
    {
        // k=2
        // 1 --> R
        // 2--> RR , WW 
        // 3  --> RRR, WWR, RWW
        // 4 --> RRRR, WWRR, RWWR,WWWW, RRWW(last 2 from 2 and first 3 from 3)
      
        dp[i] = dp[i - 1]; // RR --> RRR,  In this number of sequence doesn't change 
        if (i >= k)
        {
            dp[i] = (dp[i] + dp[i - k]) % mod; // if k=2 then RR will become RRRR and RRWW 
        }
    }
    for (int i = 1; i < N; i++)
    {
        dp[i] = (dp[i] + dp[i - 1]) % mod;
    }
}

void solve()
{
    int a, b;
    cin >> a >> b;
    // for (int i = 1; i <= b; i++)
    //     cout << dp[i] << " ";
    // cout << endl;
    cout << (dp[b] - dp[a - 1] + mod) % mod << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t >> k;
    preprocess();

    while (t--)
    {
        solve();
    }

    return 0;
}
