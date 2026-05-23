#include <deque>
#include <iostream>
#include <queue>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::queue<int> left;
  std::deque<int> right;

  for (int i = 0; i < n; ++i) {
    char operation;
    std::cin >> operation;

    if (operation == '+') {
      int x;
      std::cin >> x;
      right.push_back(x);
    } else if (operation == '*') {
      int x;
      std::cin >> x;
      right.push_front(x);
    } else if (operation == '-') {
      std::cout << left.front() << "\n";
      left.pop();
    }

    if (left.size() < right.size()) {
      left.push(right.front());
      right.pop_front();
    }
  }

  return 0;
}
