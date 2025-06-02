https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/description/

// M-1
class Solution {
public:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    int minMoves(vector<string>& v, int energy) {
        int n = v.size(), m = v[0].size();
        int litter_cnt = 0;
        map<pair<int, int>, int> litter_id;
        int sx = -1, sy = -1;

        // Preprocess start and litter positions
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (v[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if (v[i][j] == 'L') {
                    litter_id[{i, j}] = litter_cnt++;
                }
            }
        }

        if (litter_cnt == 0) return 0;
        int final_mask = (1 << litter_cnt) - 1;

        // 4D visited: x, y, energy, mask
        vector<vector<vector<vector<bool>>>> visited(
            n, vector<vector<vector<bool>>>(
                   m, vector<vector<bool>>(
                          energy + 1, vector<bool>(1 << litter_cnt, false))));

        queue<tuple<int, int, int, int, int>> q; // dist, energy left, mask, x, y
        q.emplace(0, energy, 0, sx, sy);
        visited[sx][sy][energy][0] = true;

        while (!q.empty()) {
            auto [dist, enr, mask, x, y] = q.front();
            q.pop();

            if (mask == final_mask) return dist;

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && v[nx][ny] != 'X' && enr > 0) {
                    int nenr = (v[nx][ny] == 'R') ? energy : enr - 1;
                    int new_mask = mask;

                    if (v[nx][ny] == 'L') {
                        new_mask |= (1 << litter_id[{nx, ny}]);
                    }

                    if (!visited[nx][ny][nenr][new_mask]) {
                        visited[nx][ny][nenr][new_mask] = true;
                        q.emplace(dist + 1, nenr, new_mask, nx, ny);
                    }
                }
            }
        }

        return -1;
    }
};



// M-2 But it can give tle
class Solution {
public:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    int minMoves(vector<string>& v, int energy) {
        int n = v.size(), m = v[0].size();
        int litter_cnt = 0;
        map<pair<int, int>, int> litter_id;
        int sx = -1, sy = -1;

        // Find start and litter positions
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (v[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if (v[i][j] == 'L') {
                    litter_id[{i, j}] = litter_cnt++;
                }
            }
        }

        if (litter_cnt == 0) return 0;
        int final_mask = (1 << litter_cnt) - 1;

        queue<tuple<int, int, int, int, int>> q; // dist, energy left, mask, x, y
        set<tuple<int, int, int, int>> visited;  // x, y, energy left, mask

        q.emplace(0, energy, 0, sx, sy);
        visited.emplace(sx, sy, energy, 0);

        while (!q.empty()) {
            auto [dist, enr, mask, x, y] = q.front();
            q.pop();

            if (mask == final_mask) return dist;

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && v[nx][ny] != 'X' && enr > 0) {
                    int nenr = (v[nx][ny] == 'R') ? energy : enr - 1;
                    int new_mask = mask;
                    if (v[nx][ny] == 'L') {
                        new_mask |= (1 << litter_id[{nx, ny}]);
                    }

                    if (visited.count({nx, ny, nenr, new_mask}) == 0) {
                        visited.emplace(nx, ny, nenr, new_mask);
                        q.emplace(dist + 1, nenr, new_mask, nx, ny);
                    }
                }
            }
        }

        return -1;
    }
};

