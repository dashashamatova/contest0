#include <iostream>
#include <list>
#include <string>
#include <vector>

const int cTableSize = 1000003;
const int cAlphabetSize = 26;
const unsigned long long cP = 127;

std::vector<std::list<std::string>> table(cTableSize);

int GetHash(const std::string& key) {
  unsigned long long hash = 0;
  for (char c : key) {
    hash = hash * cP + static_cast<unsigned char>(c);
  }
  return static_cast<int>(hash % cTableSize);
}

void Add(const std::string& key) {
  int idx = GetHash(key);
  for (const auto& s : table[idx]) {
    if (s == key) {
      return;
    }
  }
  table[idx].push_back(key);
}

bool Contains(const std::string& key) {
  int idx = GetHash(key);
  for (const auto& s : table[idx]) {
    if (s == key) {
      return true;
    }
  }
  return false;
}

std::string GetPattern(const std::string& s) {
  int map[cAlphabetSize];
  for (int i = 0; i < cAlphabetSize; ++i) {
    map[i] = -1;
  }

  std::string result;
  result.reserve(s.size());

  int counter = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    char current_char = s[i];
    int letter_index = current_char - 'a';

    if (map[letter_index] == -1) {
      map[letter_index] = counter;
      counter = counter + 1;
    }

    int pattern_value = map[letter_index];
    char pattern_char = static_cast<char>(pattern_value);
    result.push_back(pattern_char);
  }

  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> q;

  while (q != 0) {
    char op;
    std::string word;
    std::cin >> op >> word;

    std::string pattern = GetPattern(word);

    if (op == '+') {
      Add(pattern);
    } else if (op == '?') {
      std::cout << (Contains(pattern) ? "YES\n" : "NO\n");
    }

    q = q - 1;
  }

  return 0;
}
