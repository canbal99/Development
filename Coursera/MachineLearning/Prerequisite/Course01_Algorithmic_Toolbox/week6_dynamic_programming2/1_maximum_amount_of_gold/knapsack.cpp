#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

int optimal_weight_daq(int W, int start, const vector<int> &w, unordered_map<int,int> &map) {
    auto result = map.find(W);
    if (result!=map.end()) {
        return result->second;
    }
    
    map[W] = 0;
    int weight;
    for (int i=start;i<w.size();i++) {
        if (w[i] <= W) {
            weight = w[i] + optimal_weight_daq(W-w[i], i+1, w, map);
            if (weight>map[W]) {
                map[W] = weight;
            }
        }
    }
    
    return map[W];
}

int optimal_weight(int W, const vector<int> &w) {
    //write your code here
    unordered_map<int,int> map;
    return optimal_weight_daq(W, 0, w, map);
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
