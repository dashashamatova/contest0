#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    const int cC = 100000;
    std::vector<Edge> edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int w;
            std::cin >> w;
            if (w != cC) {
                edges.push_back({i, j, w});
            }
        }
    }

    std::vector<int> dist(n + 1, 0);
    std::vector<int> prev(n + 1, -1);
    int last = -1;

    for (int i = 1; i <= n; ++i) {
        bool updated = false;
        for (const auto& e : edges) {
            int u = e.from;
            int v = e.to;
            int c = e.weight;
            if (dist[v] > dist[u] + c) {
                dist[v] = dist[u] + c;
                prev[v] = u;
                updated = true;
                if (i == n) {
                    last = v;
                }
            }
        }
        if (!updated) {
            break;
        }
    }

    if (last == -1) {
        std::cout << "NO\n";
    } else {
        int cycle_start = last;
        for (int i = 0; i < n; ++i) {
            cycle_start = prev[cycle_start];
        }
        std::vector<int> cycle;
        int v = cycle_start;
        do {
            cycle.push_back(v);
            v = prev[v];
        } while (v != cycle_start);
        cycle.push_back(cycle_start);
        std::reverse(cycle.begin(), cycle.end());

        std::cout << "YES\n";
        std::cout << cycle.size() << "\n";
        for (size_t i = 0; i < cycle.size(); ++i) {
            std::cout << cycle[i];
            if (i + 1 < cycle.size()) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}
