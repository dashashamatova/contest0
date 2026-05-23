#include <algorithm>
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
  std::vector<std::pair<int, int>> edges(m + 1);

  for (int i = 1; i <= m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    edges[i] = {u, v};
    if (u == v) {
      continue;
    }
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
  }

  std::vector<bool> is_bridge(m + 1, false);
  std::vector<int> tin(n + 1, 0);
  std::vector<int> low(n + 1, 0);
  std::vector<bool> visited(n + 1, false);
  int timer = 0;

  for (int start = 1; start <= n; ++start) {
    if (visited[start]) {
      continue;
    }

    std::stack<std::tuple<int, int, int>> st;
    st.push({start, -1, 0});
    visited[start] = true;
    tin[start] = low[start] = ++timer;

    while (!st.empty()) {
      auto& [v, parent_edge, idx] = st.top();

      if (idx < (int)adj[v].size()) {
        auto [to, eid] = adj[v][idx];
        ++idx;

        if (eid == parent_edge) {
          continue;
        }

        if (!visited[to]) {
          visited[to] = true;
          tin[to] = low[to] = ++timer;
          st.push({to, eid, 0});
        } else {
          low[v] = std::min(low[v], tin[to]);
        }
      } else {
        st.pop();

        if (parent_edge != -1) {
          const auto& [u, w] = edges[parent_edge];
          int parent = (u == v) ? w : u;

          low[parent] = std::min(low[parent], low[v]);
          if (low[v] > tin[parent]) {
            is_bridge[parent_edge] = true;
          }
        }
      }
    }
  }

  std::vector<int> bridges;
  for (int i = 1; i <= m; ++i) {
    if (is_bridge[i]) {
      bridges.push_back(i);
    }
  }

  std::cout << bridges.size() << '\n';
  for (size_t i = 0; i < bridges.size(); ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << bridges[i];
  }
  std::cout << '\n';

  return 0;
}
