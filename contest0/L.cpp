#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string s;
  std::string t;
  std::cin >> s >> t;
  size_t n = s.size();
  std::vector<int> p(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> p[i];
  }

  int left = 0;
  int right = n;
  int mid = 0;
  int answer = 0;
  while (left <= right) {
    mid = (left + right) / 2;

    std::vector<int> removed(n, 0);
    for (int i = 0; i < mid; i++) {
      removed[p[i] - 1] = 1;
    }

    size_t j = 0;
    for (size_t i = 0; i < n && j < t.size(); i++) {
      if (removed[i] != 1 && s[i] == t[j]) {
        j++;
      }
    }

    if (j == t.size()) {
      answer = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  std::cout << answer << '\n';

  return 0;
}
