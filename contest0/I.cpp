#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string u;
  std::string v;
  int k;
  std::cin >> u >> v >> k;
  int n = u.size();
  int m = v.size();
  const int cInf = 1e9;

  std::vector<std::vector<std::vector<int>>> dp(
      n + 1,
      std::vector<std::vector<int>>(m + 1, std::vector<int>(k + 1, cInf)));
  dp[0][0][0] = 0;

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      for (int d = 0; d <= k; ++d) {
        if (dp[i][j][d] == cInf) {
          continue;
        }

        if (i < n && d + 1 <= k) {
          dp[i + 1][j][d + 1] = std::min(dp[i + 1][j][d + 1], dp[i][j][d]);
        }

        if (j < m && d + 1 <= k) {
          dp[i][j + 1][d + 1] = std::min(dp[i][j + 1][d + 1], dp[i][j][d]);
        }

        if (i < n && j < m) {
          int add = (u[i] != v[j]) ? 1 : 0;
          dp[i + 1][j + 1][d] =
              std::min(dp[i + 1][j + 1][d], dp[i][j][d] + add);
        }

        if (i < n && j < m && d + 1 <= k) {
          dp[i + 1][j + 1][d + 1] =
              std::min(dp[i + 1][j + 1][d + 1], dp[i][j][d]);
        }
      }
    }
  }

  int ans = cInf;
  for (int d = 0; d <= k; ++d) {
    ans = std::min(ans, dp[n][m][d]);
  }
  if (ans != cInf) {
    std::cout << ans << "\n";
  } else {
    std::cout << -1 << "\n";
  }
  return 0;
}
