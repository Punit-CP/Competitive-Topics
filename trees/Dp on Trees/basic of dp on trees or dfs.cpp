
    function<void(int, int)> dfs = [&](int u, int p) -> void
    {
       // This is the area where you know about the parents data and you calculate dp[u] using dp[par[u]], dp[par[par[u]]]....etc;
        dp[u]= somthing +  dp[par[u]], dp[par[par[u]]]....etc;
        for (auto v : adj[u])
        {
            if (v == p)
                continue;
            dfs(v, u);
            // This is the area where you know about the child data and you calculate dp[u] using dp[child[u]], dp[child[child[u]]]....etc;
            dp[u]= somthing +  dp[child[u]], dp[child[child[u]]]....etc;
        }
    };

 
