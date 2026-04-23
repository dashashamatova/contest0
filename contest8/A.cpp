#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;
  const int cInf = 2009000999;

  while (t != 0) {
    t--;
    int n;
    int m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
      int u;
      int v;
      int c;
      std::cin >> u >> v >> c;
      adj[u].push_back({v, c});
      adj[v].push_back({u, c});
    }

    int s;
    std::cin >> s;

    std::vector<int> dist(n, cInf);
    dist[s] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    pq.push({0, s});

    while (!pq.empty()) {
      int d = pq.top().first;
      int u = pq.top().second;
      pq.pop();
      if (d != dist[u]) {
        continue;
      }
      for (auto& edge : adj[u]) {
        int v = edge.first;
        int w = edge.second;
        if (dist[v] > dist[u] + w) {
          dist[v] = dist[u] + w;
          pq.push({dist[v], v});
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      std::cout << dist[i] << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
