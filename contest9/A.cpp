#include <iostream>
#include <vector>

bool Dfs(int u, const std::vector<std::vector<int>>& g,
         std::vector<int>& match_r, std::vector<bool>& visited) {
  for (int v : g[u - 1]) {
    if (!visited[v]) {
      visited[v] = true;
      if (match_r[v] == 0 || Dfs(match_r[v], g, match_r, visited)) {
        match_r[v] = u;
        return true;
      }
    }
  }
  return false;
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    int x;
    while (std::cin >> x, x != 0) {
      g[i].push_back(x);
    }
  }
  std::vector<int> match_r(k + 1, 0);
  int matching_size = 0;
  for (int u = 1; u <= n; ++u) {
    std::vector<bool> visited(k + 1, false);
    if (Dfs(u, g, match_r, visited)) {
      ++matching_size;
    }
  }
  std::cout << matching_size << "\n";
  for (int v = 1; v <= k; ++v) {
    if (match_r[v] != 0) {
      std::cout << match_r[v] << " " << v << "\n";
    }
  }
  return 0;
}
