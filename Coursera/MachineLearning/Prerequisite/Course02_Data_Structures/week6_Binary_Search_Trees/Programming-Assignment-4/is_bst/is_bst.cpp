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

void in_order(const vector<Node>& tree, vector<int>& result, int index) {
      
      if (tree[index].left!=-1) {
          in_order(tree, result, tree[index].left);
      }
      result.push_back(tree[index].key);
      if (tree[index].right!=-1) {
          in_order(tree, result, tree[index].right);
      }
  }

bool IsBinarySearchTreeOld(const vector<Node>& tree) {
  // Implement correct algorithm here
  vector<int> result;
  if (tree.size()) {
    in_order(tree,result,0);
  }
  for (int i=1;i<result.size();i++) {
      if (result[i]<=result[i-1]) {
          return false;
      }
  }
  return true;
}

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
