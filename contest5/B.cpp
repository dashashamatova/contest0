#include <iostream>
#include <list>
#include <vector>

const int cTableSize = 1000003;
const int cShift = 16;
const unsigned int cMult = 0x45d9f3bU;

struct Node {
  int val;
  int cnt;
};

std::vector<std::list<Node>> table(cTableSize);

int GetHash(int key) {
  unsigned int x = static_cast<unsigned int>(key);
  x = ((x >> cShift) ^ x) * cMult;
  x = ((x >> cShift) ^ x) * cMult;
  x = (x >> cShift) ^ x;
  return static_cast<int>(x % cTableSize);
}

void Add(int key) {
  int idx = GetHash(key);
  for (auto& node : table[idx]) {
    if (node.val == key) {
      node.cnt++;
      return;
    }
  }
  table[idx].push_back({key, 1});
}

bool Take(int key) {
  int idx = GetHash(key);
  for (auto& node : table[idx]) {
    if (node.val == key && node.cnt > 0) {
      node.cnt--;
      return true;
    }
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    Add(x);
  }

  std::cin >> m;
  std::vector<int> res;

  for (int i = 0; i < m; ++i) {
    int x;
    std::cin >> x;
    if (Take(x)) {
      res.push_back(x);
    }
  }

  std::cout << res.size() << "\n";
  for (size_t i = 0; i < res.size(); ++i) {
    std::cout << res[i];
    if (i + 1 < res.size()) {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
