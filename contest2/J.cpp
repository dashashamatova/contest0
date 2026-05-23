#include <iostream>
#include <string>
#include <vector>

struct Node {
  long long value;
  int insert_id;
};

std::vector<Node> heap;
std::vector<int> pos;

void SwapNodes(int first_index, int second_index) {
  pos[heap[first_index].insert_id] = second_index;
  pos[heap[second_index].insert_id] = first_index;
  Node temp = heap[first_index];
  heap[first_index] = heap[second_index];
  heap[second_index] = temp;
}

void SiftUp(int current_index) {
  while (current_index > 0) {
    int parent_index = (current_index - 1) / 2;
    if (heap[parent_index].value > heap[current_index].value) {
      SwapNodes(parent_index, current_index);
      current_index = parent_index;
    } else {
      break;
    }
  }
}

void SiftDown(int current_index) {
  int heap_size = heap.size();
  while (true) {
    int left_child_index = 2 * current_index + 1;
    int right_child_index = 2 * current_index + 2;
    int min_index = current_index;

    if (left_child_index < heap_size &&
        heap[left_child_index].value < heap[min_index].value) {
      min_index = left_child_index;
    }
    if (right_child_index < heap_size &&
        heap[right_child_index].value < heap[min_index].value) {
      min_index = right_child_index;
    }
    if (min_index != current_index) {
      SwapNodes(current_index, min_index);
      current_index = min_index;
    } else {
      break;
    }
  }
}

void Insert(long long x, int id) {
  heap.push_back({x, id});
  pos[id] = heap.size() - 1;
  SiftUp(heap.size() - 1);
}

long long GetMin() { return heap[0].value; }

void ExtractMin() {
  int heap_size = heap.size();
  SwapNodes(0, heap_size - 1);
  heap.pop_back();
  if (!heap.empty()) {
    SiftDown(0);
  }
}

void DecreaseKey(int id, long long delta) {
  int element_index = pos[id];
  heap[element_index].value -= delta;
  SiftUp(element_index);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> q;

  pos.resize(q, -1);

  for (int i = 0; i < q; i++) {
    std::string command;
    std::cin >> command;

    if (command == "insert") {
      long long x;
      std::cin >> x;
      Insert(x, i);
    } else if (command == "getMin") {
      std::cout << GetMin() << "\n";
    } else if (command == "extractMin") {
      ExtractMin();
    } else if (command == "decreaseKey") {
      int id;
      long long delta;
      std::cin >> id >> delta;
      DecreaseKey(id - 1, delta);
    }
  }

  return 0;
}
