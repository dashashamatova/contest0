#include <cstdint>
#include <iostream>
#include <vector>

void LsdSort(std::vector<uint64_t>& array) {
  const int cBits = 64;
  const int cRadix = 256;
  const int cBytesPerPass = 8;
  const int cPasses = cBits / cBytesPerPass;
  const int cByteMask = 0xFF;

  std::vector<uint64_t> temp(array.size());

  for (int pass = 0; pass < cPasses; pass++) {
    std::vector<int> count(cRadix, 0);

    for (uint64_t num : array) {
      int byte_val = (num >> (cBytesPerPass * pass)) & cByteMask;
      count[byte_val]++;
    }

    for (int i = 1; i < cRadix; i++) {
      count[i] += count[i - 1];
    }

    for (int i = array.size() - 1; i >= 0; i--) {
      int byte_val = (array[i] >> (cBytesPerPass * pass)) & cByteMask;
      count[byte_val] -= 1;
      temp[count[byte_val]] = array[i];
    }

    array = temp;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<uint64_t> array(n);
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }

  LsdSort(array);

  for (int i = 0; i < n; i++) {
    std::cout << array[i] << "\n";
  }

  return 0;
}
