#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  long long ans = 0;

  for (int m = 1; m <= n; ++m) {
    int s = n - m;

    int r = std::min(2 * m - 1, n);

    if (s == 0) {
      ++ans;
      continue;
    }

    int x_max = std::min(r, s);

    std::vector<long long> dp(s + 1, 0);
    dp[0] = 1;

    for (int x = m + 1; x <= x_max; ++x) {
      for (int j = s; j >= x; --j) {
        dp[j] += dp[j - x];
      }
    }

    ans += dp[s];
  }

  std::cout << ans << "\n";
  return 0;
}
