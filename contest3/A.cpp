#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

const int cInf = 2147483647;

using Elem = std::pair<int, int>;
using Node = std::pair<Elem, Elem>;

Node Combine(const Node& a, const Node& b) {
  Elem cand[4] = {a.first, a.second, b.first, b.second};
  std::sort(cand, cand + 4, [](const Elem& x, const Elem& y) {
    if (x.first != y.first) {
      return x.first < y.first;
    }
    return x.second < y.second;
  });
  Elem first = cand[0];
  Elem second = {cInf, -1};
  for (int i = 1; i < 4; ++i) {
    if (cand[i].second != first.second) {
      second = cand[i];
      break;
    }
  }
  return {first, second};
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  int q;
  if (!(std::cin >> n >> q)) {
    return 0;
  }

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  int max_k = 1;
  while ((1 << max_k) <= n) {
    ++max_k;
  }

  std::vector<std::vector<Node>> st(
      max_k, std::vector<Node>(n, {{cInf, -1}, {cInf, -1}}));

  for (int i = 0; i < n; i++) {
    st[0][i] = {{a[i], i}, {cInf, -1}};
  }

  for (int k = 1; k < max_k; k++) {
    for (int i = 0; i + (1 << k) <= n; i++) {
      st[k][i] = Combine(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
  }

  std::vector<int> log_table(n + 1);
  log_table[1] = 0;
  for (int i = 2; i <= n; i++) {
    log_table[i] = log_table[i / 2] + 1;
  }

  for (int qindex = 0; qindex < q; qindex++) {
    int left;
    int right;
    std::cin >> left;
    std::cin >> right;

    int length = right - left + 1;
    int power = log_table[length];

    Node segment1 = st[power][left - 1];
    Node segment2 = st[power][right - (1 << power)];
    Node result = Combine(segment1, segment2);

    std::cout << result.second.first << '\n';
  }

  return 0;
}
