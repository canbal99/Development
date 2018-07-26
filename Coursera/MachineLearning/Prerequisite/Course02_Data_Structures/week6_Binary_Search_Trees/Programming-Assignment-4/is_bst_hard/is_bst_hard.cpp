#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool isValid(const vector<Node>& tree, int& value, int index) {
      
      bool result = true;
      
      int left = tree[index].left;
      if (left!=-1) {
          result = isValid(tree, value, left);
      }
      
      result = result && (value<tree[index].key);
      value = tree[index].key;
      
      int right = tree[index].right;
      if (result && right!=-1) {
          value -= 1;
          result = isValid(tree, value, right);
      }
      
      return result;
  }

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  
  int value = 0xFFFFFFFF;
  return tree.size()==0 || isValid(tree, value, 0);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
