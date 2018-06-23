#include <iostream>
#include <vector>
#include <map>
#include <thread>

using std::vector;
using std::map;

int find_count_start(vector<int> &a, int x, int begin, int end) {
    if (begin>=end) {
        return begin;
    }
    int mid = begin + (end-begin)/2;
    if (x<a[mid])
        return find_count_start(a,x,begin,mid);
    else
        return find_count_start(a,x,mid+1,end);
}

int find_count_end_reverse(vector<int> &a, int x, int begin, int end) {
    if (begin>=end) {
        return begin;
    }
    int mid = begin + (end-begin)/2;
    if (x<=a[mid])
        return find_count_end_reverse(a,x,begin,mid);
    else
        return find_count_end_reverse(a,x,mid+1,end);
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  //write your code here
  
  std::sort(starts.begin(), starts.end());
  std::sort(ends.begin(), ends.end());
  
  for (int i=0;i<points.size();i++) {
      cnt[i] = find_count_start(starts,points[i],0,starts.size()) - find_count_end_reverse(ends,points[i],0,ends.size());
  }
  
  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}





bool compare(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> a = fast_count_segments(starts, ends, points);
    vector<int> b = naive_count_segments(starts, ends, points);
    for (int i=0;i<a.size();i++) {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

void test_solution() {
    const int TEST_COUNT = 10000;
    std::cout << "Test started !!!\n";
    for (int i=0;i<TEST_COUNT;i++) {
        int size = 1+(rand()%50000);
        std::cout << "Test for " << i << ":" << size << "\n";
        vector<int> points(size);
        vector<int> starts(size);
        vector<int> ends(size);
        for (int j=0;j<size;j++) {
            points[j] = (rand()%200000000)-100000000;
            starts[j] = (rand()%200000000)-100000000;
            ends[j]   = (rand()%200000000)-100000000;
            if (starts[j]>ends[j]) {
                std::swap(starts[j],ends[j]);
            }
        }
        if (!compare(starts, ends, points)) {
            std::cout << "error!!!";
            return;
        }
    }
    std::cout << "Test succeeded !!!\n";
}


int main() {
    
    //test_solution();
    //return 0;
    
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
