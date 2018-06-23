#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct step {
    int stepCount;
    int operation;
};

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  std::vector<step> lookup(n+1);
  lookup[1].stepCount = 0;
  for (int i=2;i<=n;i++) {
      step s = lookup[i-1];
      s.operation = 1;
      if (i%2==0 && lookup[i/2].stepCount < s.stepCount) {
          s.stepCount = lookup[i/2].stepCount;
          s.operation = 2;
      }
      if (i%3==0 && lookup[i/3].stepCount < s.stepCount) {
          s.stepCount = lookup[i/3].stepCount;
          s.operation = 3;
      }
      s.stepCount++;
      lookup[i] = s;
  }
  
  int index = n;
  sequence.push_back(index);
  while (index>1) {
      step s = lookup[index];
      if (s.operation==1) {
          index -= s.operation;
      } else {
          index /= s.operation;
      }
    sequence.push_back(index);  
  }
  reverse(sequence.begin(), sequence.end());    
  return sequence;
}

vector<int> optimal_sequence_greedy(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
