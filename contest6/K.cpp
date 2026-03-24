#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> d;
  std::vector<int> prev(n, -1);
  std::vector<int> last;

  for (int i = 0; i < n; ++i) {
    int x = a[i];
    int left = 0;
    int right = d.size();
    while (left < right) {
      int mid = (left + right) / 2;
      if (d[mid] < x) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    int p = left;

    if (p < static_cast<int>(d.size())) {
      d[p] = x;
      prev[i] = (p > 0 ? last[p - 1] : -1);
      last[p] = i;
    } else {
      d.push_back(x);
      prev[i] = (d.size() > 1 ? last[d.size() - 2] : -1);
      last.push_back(i);
    }
  }

  int l = d.size();
  std::cout << l << "\n";

  std::vector<int> ans;
  int cur = last[l - 1];
  while (cur != -1) {
    ans.push_back(cur + 1);
    cur = prev[cur];
  }
  std::reverse(ans.begin(), ans.end());

  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i];
    if (i + 1 < ans.size()) {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
