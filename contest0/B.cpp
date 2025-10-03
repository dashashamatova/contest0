#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

const int PRECISION = 6;

int main() {
    int numbersCount;
    std::cin >> numbersCount;
    
    std::vector<long double> numbers(numbersCount);
    for (int i = 0; i < numbersCount; ++i) {
        std::cin >> numbers[i];
    }
    
    int queriesCount;
    std::cin >> queriesCount;
    
    std::vector<int> queryLeft(queriesCount);
    std::vector<int> queryRight(queriesCount);
    for (int i = 0; i < queriesCount; ++i) {
        std::cin >> queryLeft[i];
        std::cin >> queryRight[i];
    }
    
    std::vector<double> prefixLogSums(numbersCount);
    prefixLogSums[0] = std::log(numbers[0]);
    for (int i = 1; i < numbersCount; ++i) {
        prefixLogSums[i] = prefixLogSums[i - 1] + std::log(numbers[i]);
    }
    
    for (int i = 0; i < queriesCount; ++i) {
        int leftIndex = queryLeft[i];
        int rightIndex = queryRight[i];
        long double geometricMean;
        
        if (leftIndex == 0) {
            geometricMean = std::exp((prefixLogSums[rightIndex]) / (rightIndex - leftIndex + 1));
        } else {
            geometricMean = std::exp((prefixLogSums[rightIndex] - prefixLogSums[leftIndex - 1]) / (rightIndex - leftIndex + 1));
        }
        
        std::cout << std::fixed << std::setprecision(PRECISION) << geometricMean << '\n';
    }
}
```
