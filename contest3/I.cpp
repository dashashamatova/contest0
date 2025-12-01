#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Node {
  std::vector<int> sorted_values;
};

std::vector<Node> tree;
std::vector<int> arr;
int n;

int CalculateTreeSize(int n) {
  int size = 1;
  while (size < n) {
    size *= 2;
  }
  return size * 2;
}

void Build(int v, int tl, int tr) {
  if (tl == tr) {
    if (tl < n) {
      tree[v].sorted_values = {arr[tl]};
    } else {
      tree[v].sorted_values = {};
    }
  } else {
    int tm = (tl + tr) / 2;
    Build(2 * v, tl, tm);
    Build(2 * v + 1, tm + 1, tr);

    tree[v].sorted_values.resize(tree[2 * v].sorted_values.size() +
                                 tree[2 * v + 1].sorted_values.size());
    std::merge(
        tree[2 * v].sorted_values.begin(), tree[2 * v].sorted_values.end(),
        tree[2 * v + 1].sorted_values.begin(),
        tree[2 * v + 1].sorted_values.end(), tree[v].sorted_values.begin());
  }
}

int Query(int v, int tl, int tr, const std::pair<int, int>& lr,
          const std::pair<int, int>& xy) {
  int l = lr.first;
  int r = lr.second;
  int x = xy.first;
  int y = xy.second;

  if (l > r) {
    return 0;
  }
  if (tl == l && tr == r) {
    auto left_it = std::lower_bound(tree[v].sorted_values.begin(),
                                    tree[v].sorted_values.end(), x);
    auto right_it = std::upper_bound(tree[v].sorted_values.begin(),
                                     tree[v].sorted_values.end(), y);
    return right_it - left_it;
  }

  int tm = (tl + tr) / 2;
  int left_count = Query(2 * v, tl, tm, {l, std::min(r, tm)}, xy);
  int right_count = Query(2 * v + 1, tm + 1, tr, {std::max(l, tm + 1), r}, xy);

  return left_count + right_count;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> n >> q;

  arr.resize(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  int tree_size = CalculateTreeSize(n);
  tree.resize(tree_size);

  Build(1, 0, tree_size / 2 - 1);

  for (int i = 0; i < q; i++) {
    int l;
    int r;
    int x;
    int y;
    std::cin >> l >> r >> x >> y;
    l--;
    r--;
    std::cout << Query(1, 0, tree_size / 2 - 1, {l, r}, {x, y}) << "\n";
  }

  return 0;
}
