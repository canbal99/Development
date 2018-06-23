#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

int get_majority_element(vector<int> &a, int left, int right) {
    //write your code here
    unordered_map<int,int> map;

    for (int i=0;i<a.size();i++) {
        auto item = map.find(a[i]);
        if (item==map.end()) {
            map[a[i]] = 1;
        } else {
            item->second++;
        }
    }
    
    for (auto item : map) {
        if (item.second>a.size()/2) {
            return item.first;
        }
    }

    return -1;
}

bool compare(vector<int> &a, int x) {
    return get_majority_element(a,0,0) == x;
}

void test_solution() {
    const int TEST_COUNT = 1000;
    std::cout << "Test started !!!\n";
    for (int i=0;i<TEST_COUNT;i++) {
        int size = 1+(rand()%(100000));
        std::cout << "Test for " << i << ":" << size << "\n";
        vector<int> a;
        for (int j=0;j<size;j++) {
            a.push_back(1+(rand()%(1000000000)));
        }
        if (TEST_COUNT%2==0) {
            for (int j=(size-1)/2;j<size;j++) {
                a[j] = TEST_COUNT;
            }
        }
        if (!compare(a,TEST_COUNT%2==0?TEST_COUNT:-1)) {
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
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
