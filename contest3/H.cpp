#include <algorithm>
#include <iostream>
#include <vector>

struct Rect {
  int x1;
  int y1;
  int x2;
  int y2;
};

struct Event {
  int x;
  bool add;
  int l;
  int r;
};

std::vector<long long> len;
std::vector<long long> full_len;
std::vector<int> cnt;
std::vector<long long> ys;
int tree_size;

void Build(int v, int vl, int vr) {
  if (vl == vr) {
    full_len[v] = ys[vl + 1] - ys[vl];
    len[v] = 0;
  } else {
    int vm = (vl + vr) / 2;
    Build(2 * v, vl, vm);
    Build(2 * v + 1, vm + 1, vr);
    full_len[v] = full_len[2 * v] + full_len[2 * v + 1];
    len[v] = 0;
  }
  cnt[v] = 0;
}

void Update(int v, int vl, int vr, int l, int r, int val) {
  if (l > r) {
    return;
  }

  if (l <= vl && vr <= r) {
    cnt[v] += val;
  } else {
    int vm = (vl + vr) / 2;
    if (l <= vm) {
      Update(2 * v, vl, vm, l, std::min(r, vm), val);
    }
    if (r > vm) {
      Update(2 * v + 1, vm + 1, vr, std::max(l, vm + 1), r, val);
    }
  }

  if (cnt[v] > 0) {
    len[v] = full_len[v];
  } else {
    if (vl == vr) {
      len[v] = 0;
    } else {
      len[v] = len[2 * v] + len[2 * v + 1];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;
  std::vector<Rect> rects(n);

  for (int i = 0; i < n; i++) {
    std::cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
    ys.push_back(rects[i].y1);
    ys.push_back(rects[i].y2);
  }

  if (n == 0) {
    std::cout << 0 << '\n';
    return 0;
  }

  std::sort(ys.begin(), ys.end());
  ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
  int m = ys.size();
  int seg_cnt = m - 1;

  if (seg_cnt == 0) {
    std::cout << 0 << '\n';
    return 0;
  }

  tree_size = 1;
  while (tree_size < seg_cnt) {
    tree_size *= 2;
  }

  len.resize(4 * seg_cnt);
  full_len.resize(4 * seg_cnt);
  cnt.resize(4 * seg_cnt);

  Build(1, 0, seg_cnt - 1);

  std::vector<Event> evts;
  for (const auto& r : rects) {
    int l_idx = std::lower_bound(ys.begin(), ys.end(), r.y1) - ys.begin();
    int r_idx = std::lower_bound(ys.begin(), ys.end(), r.y2) - ys.begin() - 1;

    if (l_idx <= r_idx) {
      evts.push_back({r.x1, true, l_idx, r_idx});
      evts.push_back({r.x2, false, l_idx, r_idx});
    }
  }

  std::sort(evts.begin(), evts.end(),
            [](const Event& a, const Event& b) { return a.x < b.x; });

  long long ans = 0;
  int prev_x = evts[0].x;
  for (const auto& e : evts) {
    ans += (e.x - prev_x) * len[1];
    Update(1, 0, seg_cnt - 1, e.l, e.r, e.add ? 1 : -1);
    prev_x = e.x;
  }

  std::cout << ans << '\n';
  return 0;
}
