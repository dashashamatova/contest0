#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<int> w(n);
  std::vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> w[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];
  }

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= w[i - 1]) {
        dp[i][j] = std::max(dp[i][j], dp[i - 1][j - w[i - 1]] + c[i - 1]);
      }
    }
  }

  std::vector<int> chosen;
  int i = n;
  int j = m;
  while (i > 0 && j > 0) {
    if (dp[i][j] == dp[i - 1][j]) {
      --i;
    } else {
      chosen.push_back(i);
      j -= w[i - 1];
      --i;
    }
  }

  std::reverse(chosen.begin(), chosen.end());
  for (size_t k = 0; k < chosen.size(); ++k) {
    std::cout << chosen[k];
    if (k + 1 < chosen.size()) {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
