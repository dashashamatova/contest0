#include <iostream>
#include <stack>
#include <vector>

struct Vertex {
  std::vector<int> adj;
  bool visited1;
  bool visited2;
  Vertex() : visited1(false), visited2(false) {}
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;

  std::vector<Vertex> graph(n + 1);
  std::vector<Vertex> rev_graph(n + 1);

  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    graph[u].adj.push_back(v);
    rev_graph[v].adj.push_back(u);
  }

  std::vector<int> order;
  for (int start = 1; start <= n; ++start) {
    if (graph[start].visited1) {
      continue;
    }

    std::stack<std::pair<int, int>> st;
    st.push({start, 0});
    graph[start].visited1 = true;

    while (!st.empty()) {
      int v = st.top().first;
      int& idx = st.top().second;

      if (idx < (int)graph[v].adj.size()) {
        int to = graph[v].adj[idx];
        ++idx;
        if (!graph[to].visited1) {
          graph[to].visited1 = true;
          st.push({to, 0});
        }
      } else {
        order.push_back(v);
        st.pop();
      }
    }
  }

  int comp_cnt = 0;
  std::vector<int> comp_id(n + 1, 0);

  for (auto it = order.rbegin(); it != order.rend(); ++it) {
    int start = *it;
    if (rev_graph[start].visited2) {
      continue;
    }
    ++comp_cnt;
    std::stack<int> st;
    st.push(start);
    rev_graph[start].visited2 = true;

    while (!st.empty()) {
      int v = st.top();
      st.pop();
      comp_id[v] = comp_cnt;
      for (int to : rev_graph[v].adj) {
        if (!rev_graph[to].visited2) {
          rev_graph[to].visited2 = true;
          st.push(to);
        }
      }
    }
  }

  std::cout << comp_cnt << '\n';
  for (int i = 1; i <= n; ++i) {
    std::cout << comp_id[i] << ' ';
  }
  std::cout << '\n';

  return 0;
}
