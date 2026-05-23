#include <iostream>
#include <list>
#include <vector>

const int cTableSize = 10007;
const long long cMultiplier = 1000000007LL;

struct Point {
  long long x;
  long long y;
};

std::vector<std::list<std::pair<long long, int>>> freq_table(cTableSize);
std::vector<std::list<Point>> point_table(cTableSize);

int GetHash(long long key) {
  long long result = key % cTableSize;
  if (result < 0) {
    result += cTableSize;
  }
  return static_cast<int>(result);
}

int PointHash(long long x, long long y) {
  long long key = x * cMultiplier + y;
  return GetHash(key);
}

void ClearFreqTable() {
  for (int i = 0; i < cTableSize; ++i) {
    freq_table[i].clear();
  }
}

void AddDistance(long long distance) {
  int idx = GetHash(distance);

  for (auto& item : freq_table[idx]) {
    if (item.first == distance) {
      item.second++;
      return;
    }
  }

  freq_table[idx].push_back({distance, 1});
}

void PointAdd(long long x, long long y) {
  int idx = PointHash(x, y);

  for (const auto& p : point_table[idx]) {
    if (p.x == x && p.y == y) {
      return;
    }
  }

  point_table[idx].push_back({x, y});
}

bool PointFind(long long x, long long y) {
  int idx = PointHash(x, y);

  for (const auto& p : point_table[idx]) {
    if (p.x == x && p.y == y) {
      return true;
    }
  }

  return false;
}

long long CountIsoscelesTriangles(int n, const std::vector<Point>& points) {
  long long answer = 0;

  for (int i = 0; i < n; ++i) {
    ClearFreqTable();

    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }

      long long dx = points[i].x - points[j].x;
      long long dy = points[i].y - points[j].y;
      long long dist = dx * dx + dy * dy;

      AddDistance(dist);
    }

    for (int j = 0; j < cTableSize; ++j) {
      for (const auto& item : freq_table[j]) {
        long long cnt = item.second;
        answer += cnt * (cnt - 1) / 2;
      }
    }
  }

  return answer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int t;
  std::cin >> n >> t;

  std::vector<Point> points(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }

  if (t == 1) {
    long long answer = CountIsoscelesTriangles(n, points);
    std::cout << answer << "\n";
  } else if (t == 2) {
    std::cout << "0\n";
  }

  return 0;
}
