class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n + 1);

        for (auto &road : roads) {
            int u = road[0];
            int v = road[1];
            int w = road[2];

            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        vector<bool> visited(n + 1, false);
        int ans = INT_MAX;

        function<void(int)> dfs = [&](int node) {
            visited[node] = true;

            for (auto &[next, weight] : graph[node]) {
                ans = min(ans, weight);

                if (!visited[next]) {
                    dfs(next);
                }
            }
        };

        dfs(1);

        return ans;
    }
};