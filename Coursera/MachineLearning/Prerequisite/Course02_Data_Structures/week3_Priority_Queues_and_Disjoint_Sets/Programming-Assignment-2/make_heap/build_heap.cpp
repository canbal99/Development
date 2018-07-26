#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {

public:
  HeapBuilder() {
      
  }

  HeapBuilder(vector<int>& data) {
      for (int i : data) {
          data_.push_back(i);
      }
  }
  
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;
  
  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwapsForSelectionSort() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i) {
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
    }
  }
  
  int Parent(int i) {
      return (i-1)/2;
  }
  
  int LeftChild(int i) {
      return 2*i+1;
  }
  
  int RightChild(int i) {
      return 2*i+2;
  }
  
  void SiftUp(int i) {
      int parent = Parent(i);
      
      if (parent>=0 && data_[i]<data_[parent]) {
          swap(data_[i], data_[parent]);
          swaps_.push_back(make_pair(i, parent));
          SiftUp(parent);
      }
  }
  
  void SiftDown(int i) {
      int left = LeftChild(i);
      int right = RightChild(i);

      if (left<data_.size() && data_[i]>data_[left]) {
          if (right<data_.size() && data_[right]<data_[left]) {
              swap(data_[i], data_[right]);
              swaps_.push_back(make_pair(i, right));
              SiftDown(right);
          } else {
              swap(data_[i], data_[left]);
              swaps_.push_back(make_pair(i, left));
              SiftDown(left);
          }
      } else if (right<data_.size() && data_[i]>data_[right]) {
          swap(data_[i], data_[right]);
          swaps_.push_back(make_pair(i, right));
          SiftDown(right);
      }
  }

 public:

  void GenerateSwapsForHeap() {
    swaps_.clear();
    int last_item = Parent(data_.size()-1);
    for (int i = last_item; i >= 0; --i) {
        SiftDown(i);
    }
  }
  
  bool isValidMinHeap() {
      int last_item = Parent(data_.size()-1);
      for (int i=0;i<=last_item;i++) {
          int left = LeftChild(i);
          int right = RightChild(i);
          if (data_[i]>data_[left] || (right<data_.size() && data_[i]>data_[right])) {
              return false;
          }
      }
      return true;
  }
  
  void Solve() {
    ReadData();
    GenerateSwapsForHeap();
    WriteResponse();
  }
};

bool compare(vector<int> x) {
    clock_t begin_time, end_time;
    HeapBuilder heapBuilder(x);
    begin_time = clock();
    heapBuilder.GenerateSwapsForHeap();
    end_time = clock();
    std::cout << "heapBuilder: " << x.size() << " in " << (end_time-begin_time)/1000 << "ms\n";
    return heapBuilder.isValidMinHeap() && (end_time-begin_time)/1000<100;
}

#define RANDOM()   (rand()%100000)
void test_solution() {
    const int TEST_COUNT = 100;
    std::cout << "Test started !!!\n";
    for (int i=0;i<TEST_COUNT;i++) {
        int size = 100000;//1+(rand()%100000);
        std::cout << "Test for " << i << ":" << size << "\n";
        vector<int> x(size);
        for (int j=0;j<size;j++) {
            x[j] = RANDOM();
        }
        if (!compare(x)) {
            std::cout << "error!!!\n";
            return;
        }
    }
    std::cout << "Test succeeded !!!\n";
}

int main() {
    //test_solution();
    //return 0;
    
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
