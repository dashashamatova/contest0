#include <iostream>
#include <vector>

const int cMod = 1000000000;

struct Node {
  int key;
  int height;
  int balance;
  Node* left;
  Node* right;

  Node(int k) : key(k), height(1), balance(0), left(nullptr), right(nullptr) {}
};

Node* root = nullptr;
int last_answer = 0;
bool last_was_query = false;

void UpdateNode(Node* node) {
  if (node == nullptr) {
    return;
  }

  int left_h = node->left != nullptr ? node->left->height : 0;
  int right_h = node->right != nullptr ? node->right->height : 0;

  node->height = (left_h > right_h ? left_h : right_h) + 1;
  node->balance = left_h - right_h;
}

Node* Zig(Node* x) {
  Node* y = x->left;
  Node* t2 = y->right;

  y->right = x;
  x->left = t2;

  UpdateNode(x);
  UpdateNode(y);

  return y;
}

Node* Zag(Node* x) {
  Node* y = x->right;
  Node* t2 = y->left;

  y->left = x;
  x->right = t2;

  UpdateNode(x);
  UpdateNode(y);

  return y;
}

void HandleLeftImbalance(Node* node, Node* parent, int i) {
  if (node->left->balance >= 0) {
    if (i > 0) {
      if (parent->left == node) {
        parent->left = Zig(node);
      } else {
        parent->right = Zig(node);
      }
    } else {
      root = Zig(node);
    }
  } else {
    node->left = Zag(node->left);
    if (i > 0) {
      if (parent->left == node) {
        parent->left = Zig(node);
      } else {
        parent->right = Zig(node);
      }
    } else {
      root = Zig(node);
    }
  }
}

void HandleRightImbalance(Node* node, Node* parent, int i) {
  if (node->right->balance <= 0) {
    if (i > 0) {
      if (parent->left == node) {
        parent->left = Zag(node);
      } else {
        parent->right = Zag(node);
      }
    } else {
      root = Zag(node);
    }
  } else {
    node->right = Zig(node->right);
    if (i > 0) {
      if (parent->left == node) {
        parent->left = Zag(node);
      } else {
        parent->right = Zag(node);
      }
    } else {
      root = Zag(node);
    }
  }
}

void BalancePath(std::vector<Node*>& path) {
  for (int i = static_cast<int>(path.size()) - 1; i >= 0; --i) {
    Node* node = path[i];
    UpdateNode(node);

    if (node->balance > 1) {
      Node* parent = (i > 0) ? path[i - 1] : nullptr;
      HandleLeftImbalance(node, parent, i);
    } else if (node->balance < -1) {
      Node* parent = (i > 0) ? path[i - 1] : nullptr;
      HandleRightImbalance(node, parent, i);
    }
  }
}

void InsertAvl(int key) {
  if (root == nullptr) {
    root = new Node(key);
    return;
  }

  std::vector<Node*> path;
  Node* current = root;

  while (current != nullptr) {
    path.push_back(current);

    if (key < current->key) {
      if (current->left == nullptr) {
        current->left = new Node(key);
        path.push_back(current->left);
        BalancePath(path);
        return;
      }
      current = current->left;
    } else if (key > current->key) {
      if (current->right == nullptr) {
        current->right = new Node(key);
        path.push_back(current->right);
        BalancePath(path);
        return;
      }
      current = current->right;
    } else {
      return;
    }
  }
}

int FindLowerBound(int key) {
  Node* current = root;
  int result = -1;

  while (current != nullptr) {
    if (current->key >= key) {
      result = current->key;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return result;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> q;

  char op;
  int x;

  for (int i = 0; i < q; ++i) {
    std::cin >> op >> x;

    if (op == '+') {
      if (last_was_query) {
        x = (x + last_answer) % cMod;
      }
      InsertAvl(x);
      last_was_query = false;
    } else {
      last_answer = FindLowerBound(x);
      std::cout << last_answer << '\n';
      last_was_query = true;
    }
  }

  return 0;
}
