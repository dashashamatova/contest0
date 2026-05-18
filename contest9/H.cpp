#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const long long cInf = 1e18;

struct Edge {
  int to;
  int rev;
  long long cap;
};

class Dinic {
 public:
  int n;
  std::vector<std::vector<Edge>> g;
  std::vector<int> level;
  std::vector<int> iter;

  Dinic(int n) : n(n) {
    g.resize(n + 1);
    level.resize(n + 1);
    iter.resize(n + 1);
  }

  void AddEdge(int from, int to, long long cap) {
    Edge fwd = {to, (int)g[to].size(), cap};
    Edge rev = {from, (int)g[from].size(), 0};
    g[from].push_back(fwd);
    g[to].push_back(rev);
  }

  void Bfs(int s) {
    for (int i = 1; i <= n; ++i) {
      level[i] = -1;
    }
    std::queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto& e : g[v]) {
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          q.push(e.to);
        }
      }
    }
  }

  long long Dfs(int v, int t, long long f) {
    if (v == t) {
      return f;
    }
    for (int& i = iter[v]; i < (int)g[v].size(); ++i) {
      Edge& e = g[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) {
        long long d = Dfs(e.to, t, std::min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          g[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  long long MaxFlow(int s, int t) {
    long long flow = 0;
    while (true) {
      Bfs(s);
      if (level[t] < 0) {
        return flow;
      }
      for (int i = 1; i <= n; ++i) {
        iter[i] = 0;
      }
      long long f;
      while ((f = Dfs(s, t, cInf)) > 0) {
        flow += f;
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;

  Dinic dinic(n);

  std::vector<int> u_orig(m);
  std::vector<int> v_orig(m);
  std::vector<long long> c_orig(m);
  std::vector<int> pos_in_g(m);

  for (int i = 0; i < m; ++i) {
    std::cin >> u_orig[i] >> v_orig[i] >> c_orig[i];
    dinic.AddEdge(u_orig[i], v_orig[i], c_orig[i]);
    pos_in_g[i] = (int)dinic.g[u_orig[i]].size() - 1;
  }

  long long maxflow = dinic.MaxFlow(1, n);
  std::cout << maxflow << '\n';

  for (int i = 0; i < m; ++i) {
    int u = u_orig[i];
    int pos = pos_in_g[i];
    long long residual = dinic.g[u][pos].cap;
    long long flow = c_orig[i] - residual;
    std::cout << flow << '\n';
  }

  return 0;
}
