#include <vector>

// If there is a cycle, the returned array will not contain all vertices.
std::vector<int> topological_sort(const std::vector<std::vector<int>> &adj) {
    const int n = int(adj.size());
    std::vector<int> deg(n);
    std::vector<int> ans;

    for (int i = 0; i < n; i++) {
        for (int j : adj[i])
            deg[j]++;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] == 0)
            ans.push_back(i);
    }

    int q = 0;
    while (q < int(ans.size())) {
        int cur = ans[q++];
        for (int next : adj[cur]) {
            if (--deg[next] == 0)
                ans.push_back(next);
        }
    }

    return ans;
}
