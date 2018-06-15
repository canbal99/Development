#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::multimap;
using std::tuple;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  multimap<double,tuple<int,int>,std::greater<int>> loots;
  
  // write your code here
  for (int i=0;i<weights.size();i++) {
      double unitValue = ((double)values[i])/weights[i];
      loots.insert( std::pair<double,tuple<int,int>>(unitValue, std::make_tuple(values[i],weights[i])) );
  }
  
  for (auto loot : loots) {
      //std::cout << "unit:" << loot.first << " value:" << std::get<0>(loot.second) << " weight:" << std::get<1>(loot.second) << "\n";
      int weight = std::min(capacity,std::get<1>(loot.second));
      value += weight * loot.first;
      capacity -= weight;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
