#include <algorithm>
#include <queue>

struct BFS {
    std::vector<int> distance;
    std::vector<int> parent;

    BFS(const std::vector<std::vector<int>> &adj, const std::vector<int> &sources) {
        const int n = adj.size();
        distance.assign(n, -1);
        parent.assign(n, -1);

        std::queue<int> q;
        for (int i : sources) {
            q.push(i);
            distance[i] = 0;
        }

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            for (int j : adj[i]) {
                if (distance[j] != -1)
                    continue;

                q.push(j);
                distance[j] = distance[i] + 1;
                parent[j] = i;
            }
        }
    }

    std::vector<int> get_path(int destination) {
        if (distance[destination] == -1)
            return {};
        std::vector<int> path{};
        for (int i = destination; i != -1; i = parent[i])
            path.push_back(i);
        std::reverse(path.begin(), path.end());
        return path;
    }
};
