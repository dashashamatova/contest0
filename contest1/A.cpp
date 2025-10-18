#include <iostream>
#include <vector>

void MergeSort(std::vector<std::pair<int, int>>& segments, int left,
               int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;
  MergeSort(segments, left, mid);
  MergeSort(segments, mid + 1, right);

  std::vector<std::pair<int, int>> temp(right - left + 1);
  int i = left;
  int j = mid + 1;
  int k = 0;

  while (i <= mid && j <= right) {
    if (segments[i].first <= segments[j].first) {
      temp[k] = segments[i];
      k = k + 1;
      i = i + 1;
    } else {
      temp[k] = segments[j];
      k = k + 1;
      j = j + 1;
    }
  }

  while (i <= mid) {
    temp[k] = segments[i];
    k = k + 1;
    i = i + 1;
  }

  while (j <= right) {
    temp[k] = segments[j];
    k = k + 1;
    j = j + 1;
  }

  for (int idx = 0; idx < k; idx++) {
    segments[left + idx] = temp[idx];
  }
}

int main() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> segments(n);
  for (int i = 0; i < n; i++) {
    std::cin >> segments[i].first >> segments[i].second;
  }

  if (n > 0) {
    MergeSort(segments, 0, n - 1);
  }

  std::vector<std::pair<int, int>> result;
  if (n > 0) {
    int left = segments[0].first;
    int right = segments[0].second;

    for (int i = 1; i < n; i++) {
      int l = segments[i].first;
      int r = segments[i].second;

      if (l <= right) {
        if (r > right) {
          right = r;
        }
      } else {
        result.push_back({left, right});
        left = l;
        right = r;
      }
    }

    result.push_back({left, right});
  }

  std::cout << result.size() << std::endl;
  for (std::pair<int, int> seg : result) {
    std::cout << seg.first << " " << seg.second << std::endl;
  }
  return 0;
}
