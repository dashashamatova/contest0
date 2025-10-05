#include <iostream>
#include <vector>

const int cRange = 2;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int arraySize;
  std::cin >> arraySize;

  std::vector<long long> firstArray(arraySize);
  std::vector<long long> secondArray(arraySize);

  for (int i = 0; i < arraySize; ++i) {
    std::cin >> firstArray[i];
  }
  for (int i = 0; i < arraySize; ++i) {
    std::cin >> secondArray[i];
  }

  long long queriesCount;
  std::cin >> queriesCount;

  for (long long queryIndex = 0; queryIndex < queriesCount; ++queryIndex) {
    long long x;
    std::cin >> x;

    if (firstArray[arraySize - 1] + x <= secondArray[arraySize - 1]) {
      std::cout << arraySize << '\n';
      continue;
    }

    long long leftBound = -1;
    long long rightBound = arraySize - 1;
    while (rightBound - leftBound > 1) {
      long long middleIndex = (leftBound + rightBound) / 2;
      if (firstArray[middleIndex] + x < secondArray[middleIndex]) {
        leftBound = middleIndex;
      } else {
        rightBound = middleIndex;
      }
    }
    long long bestIndex = rightBound;
    for (long long j = rightBound - cRange; j <= rightBound + cRange; ++j) {
      if (j >= 0 && j < arraySize &&
          std::max(firstArray[j] + x, secondArray[j]) <
              std::max(firstArray[bestIndex] + x, secondArray[bestIndex])) {
        bestIndex = j;
      }
    }
    std::cout << bestIndex + 1 << '\n';
  }

  return 0;
}
