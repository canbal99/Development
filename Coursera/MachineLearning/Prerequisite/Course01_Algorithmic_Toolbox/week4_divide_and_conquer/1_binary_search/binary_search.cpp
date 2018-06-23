#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search(const vector<int> &a, int x, int left, int right) {
    if (left>right) {
        return -1;
    }
    if (left==right) {
        return a[left] == x ? left : -1;
    }
    
    int index = (left + right) / 2;
    if (a[index] > x) return binary_search(a,x,left,index-1);
    if (a[index] < x) return binary_search(a,x,index+1,right);
    return index;
}

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size()-1; 
  return binary_search(a,x,left,right);
  
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

bool compare(vector<int> &a, int x) {
    return linear_search(a,x) == binary_search(a,x);
}

void test_solution() {
    const int TEST_COUNT = 10000;
    std::cout << "Test started !!!\n";
    for (int i=0;i<TEST_COUNT;i++) {
        int size = 1+(rand()%10000);
        std::cout << "Test for " << i << ":" << size << "\n";
        vector<int> a;
        for (int j=0;j<size;j++) {
            a.push_back(1+(rand()%1000000000));
        }
        if (!compare(a,rand())) {
            for (int k=0;k<size;k++) {
                std::cout << "error: " << a[k];
            }
            return;
        }
    }
    std::cout << "Test succeeded !!!\n";
}

int main() {
  
  //test_solution();
  //return 0;
    
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    //std::cout << linear_search(a, b[i]) << ' ';
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
