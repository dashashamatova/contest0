#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

struct Edge {
    int weight;
    int vertex1;
    int vertex2;
};

struct DSU {
    std::vector<int> parent;
    std::vector<int> rank;

    DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int Find(int x) {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Unite(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b) {
            return;
        }
        if (rank[a] < rank[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        int u;
        int v;
        int c;
        std::cin >> u >> v >> c;
        edges[i] = {c, u, v};
    }

    std::sort(edges.begin(), edges.end(),
              [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

    DSU dsu(n);
    long long total_weight = 0;
    int edges_used = 0;

    for (const auto& edge : edges) {
        int c = edge.weight;
        int u = edge.vertex1;
        int v = edge.vertex2;
        if (dsu.Find(u) != dsu.Find(v)) {
            dsu.Unite(u, v);
            total_weight += c;
            ++edges_used;
            if (edges_used == n - 1) {
                break;
            }
        }
    }

    std::cout << total_weight << '\n';

    return 0;
}
