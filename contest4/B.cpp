#include <iostream>
#include <string>

struct Node {
  int key;
  Node* left;
  Node* right;
  Node* parent;
  int size;

  Node(int k)
      : key(k), left(nullptr), right(nullptr), parent(nullptr), size(1) {}
};

Node* root = nullptr;

void Update(Node* node) {
  if (node == nullptr) {
    return;
  }
  node->size = 1;
  if (node->left != nullptr) {
    node->size += node->left->size;
  }
  if (node->right != nullptr) {
    node->size += node->right->size;
  }
}

void Zig(Node* x) {
  Node* p = x->parent;
  p->left = x->right;
  if (x->right != nullptr) {
    x->right->parent = p;
  }

  x->right = p;
  x->parent = p->parent;
  p->parent = x;
  if (x->parent != nullptr) {
    if (x->parent->left == p) {
      x->parent->left = x;
    } else {
      x->parent->right = x;
    }
  } else {
    root = x;
  }

  Update(p);
  Update(x);
}

void Zag(Node* x) {
  Node* p = x->parent;
  p->right = x->left;
  if (x->left != nullptr) {
    x->left->parent = p;
  }
  x->left = p;
  x->parent = p->parent;
  p->parent = x;
  if (x->parent != nullptr) {
    if (x->parent->left == p) {
      x->parent->left = x;
    } else {
      x->parent->right = x;
    }
  } else {
    root = x;
  }

  Update(p);
  Update(x);
}

void Splay(Node* x) {
  while (x != nullptr && x->parent != nullptr) {
    Node* p = x->parent;
    Node* g = p->parent;

    if (g == nullptr) {
      if (p->left == x) {
        Zig(x);
      } else {
        Zag(x);
      }
    } else if (g->left == p && p->left == x) {
      Zig(p);
      Zig(x);
    } else if (g->right == p && p->right == x) {
      Zag(p);
      Zag(x);
    } else if (g->left == p && p->right == x) {
      Zag(x);
      Zig(x);
    } else {
      Zig(x);
      Zag(x);
    }
  }
}

Node* FindNode(int key) {
  Node* curr = root;
  Node* prev = nullptr;

  while (curr != nullptr) {
    prev = curr;
    if (key < curr->key) {
      curr = curr->left;
    } else if (key > curr->key) {
      curr = curr->right;
    } else {
      Splay(curr);
      return curr;
    }
  }

  if (prev != nullptr) {
    Splay(prev);
  }
  return nullptr;
}

Node* Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }

  Node* max_left = left;
  while (max_left->right != nullptr) {
    max_left = max_left->right;
  }

  Splay(max_left);
  max_left->right = right;
  right->parent = max_left;
  Update(max_left);
  return max_left;
}

void Insert(int key) {
  if (root == nullptr) {
    root = new Node(key);
    return;
  }

  Node* curr = root;
  Node* parent = nullptr;

  while (curr != nullptr) {
    parent = curr;
    if (key < curr->key) {
      curr = curr->left;
    } else if (key > curr->key) {
      curr = curr->right;
    } else {
      Splay(curr);
      return;
    }
  }

  Node* new_node = new Node(key);
  new_node->parent = parent;

  if (key < parent->key) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  Splay(new_node);
}

void Remove(int key) {
  Node* node = FindNode(key);
  if (node == nullptr || node->key != key) {
    return;
  }

  Node* left = node->left;
  Node* right = node->right;

  if (left != nullptr) {
    left->parent = nullptr;
  }
  if (right != nullptr) {
    right->parent = nullptr;
  }

  delete node;

  root = Merge(left, right);
  if (root != nullptr) {
    root->parent = nullptr;
  }
}

bool Exists(int key) {
  Node* node = FindNode(key);
  return node != nullptr && node->key == key;
}

std::string Next(int key) {
  if (root == nullptr) {
    return "none";
  }

  Node* curr = root;
  Node* result = nullptr;

  while (curr != nullptr) {
    if (curr->key > key) {
      result = curr;
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  if (result != nullptr) {
    Splay(result);
    return std::to_string(result->key);
  }
  return "none";
}

std::string Prev(int key) {
  if (root == nullptr) {
    return "none";
  }

  Node* curr = root;
  Node* result = nullptr;

  while (curr != nullptr) {
    if (curr->key < key) {
      result = curr;
      curr = curr->right;
    } else {
      curr = curr->left;
    }
  }

  if (result != nullptr) {
    Splay(result);
    return std::to_string(result->key);
  }
  return "none";
}

std::string Kth(int k) {
  if (root == nullptr || k < 0 || k >= root->size) {
    return "none";
  }

  Node* node = root;
  while (node != nullptr) {
    int left_size = (node->left != nullptr) ? node->left->size : 0;

    if (k == left_size) {
      Splay(node);
      return std::to_string(node->key);
    }
    if (k < left_size) {
      node = node->left;
    } else {
      k -= left_size + 1;
      node = node->right;
    }
  }

  return "none";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string cmd;
  int x;

  while (std::cin >> cmd) {
    if (cmd == "insert") {
      std::cin >> x;
      Insert(x);
    } else if (cmd == "delete") {
      std::cin >> x;
      Remove(x);
    } else if (cmd == "exists") {
      std::cin >> x;
      std::cout << (Exists(x) ? "true" : "false") << '\n';
    } else if (cmd == "next") {
      std::cin >> x;
      std::cout << Next(x) << '\n';
    } else if (cmd == "prev") {
      std::cin >> x;
      std::cout << Prev(x) << '\n';
    } else if (cmd == "kth") {
      std::cin >> x;
      std::cout << Kth(x) << '\n';
    }
  }

  return 0;
}
