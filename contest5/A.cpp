#include <iostream>
#include <list>
#include <vector>

const int cTableSize = 1000003;
const int cShiftBits = 16;
const unsigned int cMultiplier = 0x45d9f3bU;

std::vector<std::list<int>> hash_table(cTableSize);

int HashFunc(int key) {
  unsigned int x = static_cast<unsigned int>(key);
  x = ((x >> cShiftBits) ^ x) * cMultiplier;
  x = ((x >> cShiftBits) ^ x) * cMultiplier;
  x = (x >> cShiftBits) ^ x;
  return static_cast<int>(x % cTableSize);
}

void Insert(int key) {
  int index = HashFunc(key);
  for (int value : hash_table[index]) {
    if (value == key) {
      return;
    }
  }
  hash_table[index].push_back(key);
}

void Remove(int key) {
  int index = HashFunc(key);
  hash_table[index].remove(key);
}

bool Contains(int key) {
  int index = HashFunc(key);
  for (int value : hash_table[index]) {
    if (value == key) {
      return true;
    }
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    char op;
    int x;
    std::cin >> op >> x;

    if (op == '+') {
      Insert(x);
    } else if (op == '-') {
      Remove(x);
    } else if (op == '?') {
      std::cout << (Contains(x) ? "YES\n" : "NO\n");
    }
  }

  return 0;
}
