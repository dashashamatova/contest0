#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Fenwick1D {
  std::vector<long long> tree;

  void Init(int size) { tree.assign(size + 1, 0); }

  void Update(int index, long long delta) {
    for (++index; index < (int)tree.size(); index += index & -index) {
      tree[index] += delta;
    }
  }

  long long Query(int index) const {
    long long result = 0;
    for (++index; index > 0; index -= index & -index) {
      result += tree[index];
    }
    return result;
  }
};

struct Fenwick2D {
  int size;
  std::vector<std::vector<int>> y_coords;
  std::vector<Fenwick1D> trees;

  Fenwick2D(int n) : size(n), y_coords(n + 1), trees(n + 1) {}

  void AddPoint(int x, int y) {
    for (++x; x <= size; x += x & -x) {
      y_coords[x].push_back(y);
    }
  }

  void Build() {
    for (int i = 1; i <= size; i++) {
      std::sort(y_coords[i].begin(), y_coords[i].end());
      y_coords[i].erase(std::unique(y_coords[i].begin(), y_coords[i].end()),
                        y_coords[i].end());
      trees[i].Init((int)y_coords[i].size());
    }
  }

  void Update(int x, int y, long long delta) {
    for (++x; x <= size; x += x & -x) {
      int y_index =
          (int)(std::lower_bound(y_coords[x].begin(), y_coords[x].end(), y) -
                y_coords[x].begin());
      trees[x].Update(y_index, delta);
    }
  }

  long long Query(int x, int y) const {
    long long result = 0;
    for (++x; x > 0; x -= x & -x) {
      int y_index =
          (int)(std::upper_bound(y_coords[x].begin(), y_coords[x].end(), y) -
                y_coords[x].begin() - 1);
      if (y_index >= 0) {
        result += trees[x].Query(y_index);
      }
    }
    return result;
  }
};

struct Point {
  int x;
  int y;
  long long weight;
};

struct Query {
  std::string type;
  int param1;
  int param2;
};

struct InputData {
  std::vector<Point> points;
  std::vector<Query> queries;
  std::vector<int> all_x_coords;
  std::vector<int> all_y_coords;
};

InputData ReadInput() {
  InputData data;
  int n;
  std::cin >> n;
  data.points.resize(n);

  for (int i = 0; i < n; i++) {
    int x, y;
    long long weight;
    std::cin >> x >> y >> weight;
    data.points[i] = {x, y, weight};
    data.all_x_coords.push_back(x);
    data.all_y_coords.push_back(y);
  }

  int q;
  std::cin >> q;
  data.queries.resize(q);

  for (int i = 0; i < q; i++) {
    std::string type;
    std::cin >> type;
    if (type == "get") {
      int a, b;
      std::cin >> a >> b;
      data.queries[i] = {type, a, b};
      data.all_x_coords.push_back(a);
      data.all_y_coords.push_back(b);
    } else {
      int index, new_weight;
      std::cin >> index >> new_weight;
      data.queries[i] = {type, index, new_weight};
    }
  }

  return data;
}

void CompressCoordinates(std::vector<int>& x_coords, std::vector<int>& y_coords) {
  std::sort(x_coords.begin(), x_coords.end());
  x_coords.erase(std::unique(x_coords.begin(), x_coords.end()), x_coords.end());
  std::sort(y_coords.begin(), y_coords.end());
  y_coords.erase(std::unique(y_coords.begin(), y_coords.end()), y_coords.end());
}

void InitializeFenwickTree(Fenwick2D& fenwick_tree, const InputData& data) {
  for (const auto& point : data.points) {
    int x_idx = std::lower_bound(data.all_x_coords.begin(), data.all_x_coords.end(), point.x) -
                data.all_x_coords.begin();
    int y_idx = std::lower_bound(data.all_y_coords.begin(), data.all_y_coords.end(), point.y) -
                data.all_y_coords.begin();
    fenwick_tree.AddPoint(x_idx, y_idx);
  }

  for (const auto& query : data.queries) {
    if (query.type == "get") {
      int x_idx = std::lower_bound(data.all_x_coords.begin(), data.all_x_coords.end(), query.param1) -
                  data.all_x_coords.begin();
      int y_idx = std::lower_bound(data.all_y_coords.begin(), data.all_y_coords.end(), query.param2) -
                  data.all_y_coords.begin();
      fenwick_tree.AddPoint(x_idx, y_idx);
    }
  }
}

void ProcessQueries(Fenwick2D& fenwick_tree, const InputData& data) {
  std::vector<long long> current_weights(data.points.size());
  std::vector<std::pair<int, int>> coords(data.points.size());

  for (int i = 0; i < (int)data.points.size(); i++) {
    const auto& point = data.points[i];
    int x_idx = std::lower_bound(data.all_x_coords.begin(), data.all_x_coords.end(), point.x) -
                data.all_x_coords.begin();
    int y_idx = std::lower_bound(data.all_y_coords.begin(), data.all_y_coords.end(), point.y) -
                data.all_y_coords.begin();
    fenwick_tree.Update(x_idx, y_idx, point.weight);
    current_weights[i] = point.weight;
    coords[i] = {x_idx, y_idx};
  }

  for (const auto& query : data.queries) {
    if (query.type == "get") {
      int x_idx = std::upper_bound(data.all_x_coords.begin(), data.all_x_coords.end(), query.param1) -
                  data.all_x_coords.begin() - 1;
      int y_idx = std::upper_bound(data.all_y_coords.begin(), data.all_y_coords.end(), query.param2) -
                  data.all_y_coords.begin() - 1;
      if (x_idx < 0 || y_idx < 0) {
        std::cout << 0 << '\n';
      } else {
        std::cout << fenwick_tree.Query(x_idx, y_idx) << '\n';
      }
    } else {
      int point_index = query.param1 - 1;
      long long old_w = current_weights[point_index];
      long long new_w = query.param2;
      long long delta = new_w - old_w;
      int x = coords[point_index].first;
      int y = coords[point_index].second;
      fenwick_tree.Update(x, y, delta);
      current_weights[point_index] = new_w;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  InputData data = ReadInput();
  CompressCoordinates(data.all_x_coords, data.all_y_coords);

  int size_x = data.all_x_coords.size();
  Fenwick2D fenwick_tree(size_x);

  InitializeFenwickTree(fenwick_tree, data);
  fenwick_tree.Build();
  ProcessQueries(fenwick_tree, data);

  return 0;
}
