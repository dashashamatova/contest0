#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const long long cInf = 1e18;

struct Edge {
  int to;
  int rev;
  long long cap;
  long long cost;
};

class MinCostMaxFlow {
 public:
  int n;
  std::vector<std::vector<Edge>> g;

  MinCostMaxFlow(int n) : n(n) { g.resize(n + 1); }

  void AddEdge(int from, int to, long long cap, long long cost) {
    Edge fwd = {to, (int)g[to].size(), cap, cost};
    Edge rev = {from, (int)g[from].size(), 0, -cost};
    g[from].push_back(fwd);
    g[to].push_back(rev);
  }

  long long GetMinCostMaxFlow(int s, int t) {
    long long total_cost = 0;

    while (true) {
      std::vector<long long> dist(n + 1, cInf);
      std::vector<bool> inqueue(n + 1, false);
      std::vector<int> parent_v(n + 1, -1);
      std::vector<int> parent_e(n + 1, -1);

      std::queue<int> q;
      dist[s] = 0;
      q.push(s);
      inqueue[s] = true;

      while (!q.empty()) {
        int v = q.front();
        q.pop();
        inqueue[v] = false;

        for (int i = 0; i < (int)g[v].size(); ++i) {
          Edge& e = g[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
            dist[e.to] = dist[v] + e.cost;
            parent_v[e.to] = v;
            parent_e[e.to] = i;
            if (!inqueue[e.to]) {
              q.push(e.to);
              inqueue[e.to] = true;
            }
          }
        }
      }

      if (dist[t] == cInf) {
        break;
      }

      long long f = cInf;
      for (int v = t; v != s; v = parent_v[v]) {
        int u = parent_v[v];
        int e_idx = parent_e[v];
        f = std::min(f, g[u][e_idx].cap);
      }

      total_cost += f * dist[t];

      for (int v = t; v != s; v = parent_v[v]) {
        int u = parent_v[v];
        int e_idx = parent_e[v];
        g[u][e_idx].cap -= f;
        int rev_idx = g[u][e_idx].rev;
        g[v][rev_idx].cap += f;
      }
    }

    return total_cost;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;

  MinCostMaxFlow mcmf(n);

  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    long long c;
    long long w;
    std::cin >> u >> v >> c >> w;
    mcmf.AddEdge(u, v, c, w);
  }

  long long result = mcmf.GetMinCostMaxFlow(1, n);
  std::cout << result << '\n';

  return 0;
}
