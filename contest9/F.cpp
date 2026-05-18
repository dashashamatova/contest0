#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int Bfs(int s, int t, const std::vector<std::vector<int>>& cap,
        std::vector<int>& parent) {
  int n = cap.size() - 1;
  parent.assign(n + 1, -1);
  parent[s] = s;
  std::queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = 1; v <= n; ++v) {
      if (parent[v] == -1 && cap[u][v] > 0) {
        parent[v] = u;
        if (v == t) {
          int flow = cap[u][v];
          int cur = v;
          while (cur != s) {
            int p = parent[cur];
            flow = std::min(flow, cap[p][cur]);
            cur = p;
          }
          return flow;
        }
        q.push(v);
      }
    }
  }
  return 0;
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<int> u_orig(m + 1);
  std::vector<int> v_orig(m + 1);
  std::vector<int> c_orig(m + 1);

  std::vector<std::vector<int>> cap(n + 1, std::vector<int>(n + 1, 0));

  for (int i = 1; i <= m; ++i) {
    std::cin >> u_orig[i] >> v_orig[i] >> c_orig[i];
    cap[u_orig[i]][v_orig[i]] += c_orig[i];
    cap[v_orig[i]][u_orig[i]] += c_orig[i];
  }

  std::vector<int> parent(n + 1);
  while (true) {
    int flow = Bfs(1, n, cap, parent);
    if (flow == 0) {
      break;
    }
    int v = n;
    while (v != 1) {
      int u = parent[v];
      cap[u][v] -= flow;
      cap[v][u] += flow;
      v = u;
    }
  }

  std::vector<bool> visited(n + 1, false);
  std::queue<int> q;
  visited[1] = true;
  q.push(1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = 1; v <= n; ++v) {
      if (!visited[v] && cap[u][v] > 0) {
        visited[v] = true;
        q.push(v);
      }
    }
  }

  std::vector<int> cut_edges;
  long long sum_cost = 0;
  for (int i = 1; i <= m; ++i) {
    int u = u_orig[i];
    int v = v_orig[i];
    if (visited[u] != visited[v]) {
      cut_edges.push_back(i);
      sum_cost += c_orig[i];
    }
  }

  std::cout << cut_edges.size() << ' ' << sum_cost << '\n';
  for (size_t i = 0; i < cut_edges.size(); ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << cut_edges[i];
  }
  std::cout << '\n';

  return 0;
}
