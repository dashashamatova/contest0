#include <climits>
#include <iostream>
#include <stack>
#include <string>

std::stack<int> input_stack;
std::stack<int> output_stack;
std::stack<int> min_input_stack;
std::stack<int> min_output_stack;

int GetMin() {
  if (min_input_stack.empty() && min_output_stack.empty()) {
    return INT_MAX;
  }
  if (min_input_stack.empty()) {
    return min_output_stack.top();
  }
  if (min_output_stack.empty()) {
    return min_input_stack.top();
  }
  return std::min(min_input_stack.top(), min_output_stack.top());
}

void Enqueue(int x) {
  input_stack.push(x);
  if (min_input_stack.empty() || x <= min_input_stack.top()) {
    min_input_stack.push(x);
  } else {
    min_input_stack.push(min_input_stack.top());
  }
  std::cout << "ok\n";
}

void Dequeue() {
  if (input_stack.empty() && output_stack.empty()) {
    std::cout << "error\n";
    return;
  }

  if (output_stack.empty()) {
    while (!input_stack.empty()) {
      int val = input_stack.top();
      input_stack.pop();
      output_stack.push(val);

      if (min_output_stack.empty() || val <= min_output_stack.top()) {
        min_output_stack.push(val);
      } else {
        min_output_stack.push(min_output_stack.top());
      }
      min_input_stack.pop();
    }
  }

  int front_val = output_stack.top();
  output_stack.pop();
  min_output_stack.pop();
  std::cout << front_val << "\n";
}

void Front() {
  if (input_stack.empty() && output_stack.empty()) {
    std::cout << "error\n";
    return;
  }

  if (output_stack.empty()) {
    while (!input_stack.empty()) {
      int val = input_stack.top();
      input_stack.pop();
      output_stack.push(val);

      if (min_output_stack.empty() || val <= min_output_stack.top()) {
        min_output_stack.push(val);
      } else {
        min_output_stack.push(min_output_stack.top());
      }
      min_input_stack.pop();
    }
  }

  std::cout << output_stack.top() << "\n";
}

void Size() { std::cout << input_stack.size() + output_stack.size() << "\n"; }

void Clear() {
  while (!input_stack.empty()) {
    input_stack.pop();
    min_input_stack.pop();
  }
  while (!output_stack.empty()) {
    output_stack.pop();
    min_output_stack.pop();
  }
  std::cout << "ok\n";
}

void Min() {
  if (input_stack.empty() && output_stack.empty()) {
    std::cout << "error\n";
  } else {
    std::cout << GetMin() << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::string command;
    std::cin >> command;

    if (command == "enqueue") {
      int x;
      std::cin >> x;
      Enqueue(x);
    } else if (command == "dequeue") {
      Dequeue();
    } else if (command == "front") {
      Front();
    } else if (command == "size") {
      Size();
    } else if (command == "clear") {
      Clear();
    } else if (command == "min") {
      Min();
    }
  }

  return 0;
}
