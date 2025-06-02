https://leetcode.com/problems/candy/description/?envType=daily-question&envId=2025-06-02

class Solution
{
    public:
        int candy(vector<int> &a)
        {
            int i, x, sum = 0, n = a.size();
            vector<int> b(n, 1);
            for (i = 1; i < n; i++)
            {
                if (a[i] > a[i - 1])
                    b[i] = b[i - 1] + 1;
            }
            for (i = n - 2; i >= 0; i--)
            {
                if (a[i] > a[i + 1] && b[i] <= b[i + 1])
                    b[i] = b[i + 1] + 1;
            }
            for (auto x: b)
                sum += x;
            return sum;
        }
};

📌 Where to Use This Technique:
You can use the two-pass greedy pattern in problems such as:
| Problem Type                                    | Description                                                                            |
| ----------------------------------------------- | -------------------------------------------------------------------------------------- |
| **Candy Distribution**                          | Like your example — ensure children with higher ratings get more candy than neighbors. |
| **Gas Station Problem**                         | Simulate trips in both directions.                                                     |
| **Mountain / Peak Problems**                    | Handle increasing/decreasing patterns like finding the longest mountain.               |
| **Stock Buy & Sell (at most two transactions)** | Forward and backward pass to track profits.                                            |
| **Histogram problems**                          | Like "Trapping Rain Water" — requires left max and right max.                          |
| **Scheduling / Rewards**                        | Enforce increasing constraints on both sides.                                          |
