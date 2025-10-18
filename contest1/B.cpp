#include <iostream>
#include <vector>

const int cModulo = 10000000 + 4321;
const int cMultiplier1 = 123;
const int cMultiplier2 = 45;

int NextVal(int a_early, int a_early2) {
  return (1LL * a_early * cMultiplier1 + 1LL * a_early2 * cMultiplier2) %
         cModulo;
}

void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int MedianOfFive(std::vector<int>& arr, int left) {
  int a = arr[left];
  int b = arr[left + 1];
  int c = arr[left + 2];
  int d = arr[left + 3];
  int e = arr[left + 4];

  if (a > b) {
    Swap(a, b);
  }
  if (c > d) {
    Swap(c, d);
  }
  if (a > c) {
    Swap(a, c);
    Swap(b, d);
  }
  if (b > e) {
    Swap(b, e);
  }
  if (a > b) {
    Swap(a, b);
    Swap(c, e);
  }
  if (c > e) {
    Swap(c, e);
  }
  if (b > c) {
    Swap(b, c);
    Swap(d, e);
  }
  if (c > d) {
    Swap(c, d);
  }
  if (b > c) {
    Swap(b, c);
  }

  return c;
}

int MedianOfUpToFive(std::vector<int>& arr, int left, int right) {
  int n = right - left + 1;

  if (n == 1) {
    return arr[left];
  }
  if (n == 2) {
    return arr[left];
  }
  if (n == 3) {
    int x = arr[left];
    int y = arr[left + 1];
    int z = arr[left + 2];
    if (x > y) {
      Swap(x, y);
    }
    if (x > z) {
      Swap(x, z);
    }
    if (y > z) {
      Swap(y, z);
    }
    return y;
  }
  if (n == 4) {
    int a = arr[left];
    int b = arr[left + 1];
    int c = arr[left + 2];
    int d = arr[left + 3];
    if (a > b) {
      Swap(a, b);
    }
    if (c > d) {
      Swap(c, d);
    }
    if (a > c) {
      Swap(a, c);
      Swap(b, d);
    }
    if (b > d) {
      Swap(b, d);
    }
    if (b > c) {
      Swap(b, c);
    }
    return b;
  }
  // n == 5
  return MedianOfFive(arr, left);
}

int FindMedian(std::vector<int>& arr, int left, int right) {
  int n = right - left + 1;

  if (n <= 5) {
    return MedianOfUpToFive(arr, left, right);
  }

  std::vector<int> medians;
  for (int i = left; i <= right; i += 5) {
    int group_end = i + 4;
    if (group_end > right) {
      group_end = right;
    }
    medians.push_back(MedianOfUpToFive(arr, i, group_end));
  }

  return FindMedian(medians, 0, static_cast<int>(medians.size()) - 1);
}

int DeterministicPartition(std::vector<int>& arr, int left, int right) {
  int pivot_value = FindMedian(arr, left, right);

  int pivot_index = left;
  for (int i = left; i <= right; ++i) {
    if (arr[i] == pivot_value) {
      pivot_index = i;
      break;
    }
  }

  Swap(arr[pivot_index], arr[right]);

  int store_index = left;
  for (int i = left; i < right; ++i) {
    if (arr[i] <= pivot_value) {
      Swap(arr[store_index], arr[i]);
      ++store_index;
    }
  }

  Swap(arr[store_index], arr[right]);
  return store_index;
}

int QuickSelect(std::vector<int>& arr, int left, int right, int k) {
  if (left == right) {
    return arr[left];
  }

  int pivot_index = DeterministicPartition(arr, left, right);

  if (k == pivot_index) {
    return arr[k];
  }
  if (k < pivot_index) {
    return QuickSelect(arr, left, pivot_index - 1, k);
  }
  return QuickSelect(arr, pivot_index + 1, right, k);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int k;
  int a0;
  int a1;
  std::cin >> n >> k >> a0 >> a1;

  std::vector<int> arr(n);
  if (n >= 1) {
    arr[0] = a0;
  }
  if (n >= 2) {
    arr[1] = a1;
  }

  for (int i = 2; i < n; ++i) {
    arr[i] = NextVal(arr[i - 1], arr[i - 2]);
  }

  int result = QuickSelect(arr, 0, n - 1, k - 1);
  std::cout << result << '\n';

  return 0;
}
