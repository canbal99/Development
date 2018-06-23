#include <iostream>
#include <vector>

using std::vector;
using std::swap;
using std::tuple;
using std::get;
using std::cout;

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  //write your code here
  
  int a1 = left;
  int a2 = ave;
  int ind = left;
  while (a1<ave && a2<right) {
    if (a[a1]>a[a2]) {
        b[ind++] = a[a2++];
        number_of_inversions+=(ave-a1);
    } else {
        b[ind++] = a[a1++];
    }
  }
  while (a1<ave) {
      b[ind++] = a[a1++];
  }
  for (int i=left;i<ind;i++) {
      a[i] = b[i];
  }
  while (a2<right) {
      a[ind++] = a[a2++];
  }
  
  return number_of_inversions;
}

tuple<int,int> partition3(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  int m = l;
  /*cout << "a: ";
  for (int i=0; i<a.size();i++) {
    cout << a[i] << " ";
  }*/
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      m++;
      if (a[i] < x) {
        j++;
        swap(a[j], a[i]);
      }
      if (m!=j) {
        swap(a[m], a[i]);
      }
    }
  }
  swap(a[l], a[j]);    
  
  /*cout << "\nl:" << l << "-r:" << r << "-x:" << x << "\na: ";
  for (int i=0; i<a.size();i++) {
    cout << a[i] << " ";
  }
  cout << "\n" << j << "-" << m << "\n";*/
  
  return tuple<int,int>(j,m);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  
  tuple<int,int> ret = partition3(a, l ,r);
  randomized_quick_sort(a, l, get<0>(ret)-1);
  randomized_quick_sort(a, get<1>(ret) + 1, r);
}

bool compare(vector<int> &a) {
    /*std::cout << "a: ";
    for (int k=0;k<a.size();k++) {
        std::cout << a[k] << " ";
    }
    std::cout << "\n";*/
    vector<int> b(a);
    vector<int> c(a);
    get_number_of_inversions(b, a, 0, a.size());
    randomized_quick_sort(c,0,c.size()-1);
    for (int i=0;i<a.size();i++) {
        if (a[i]!=c[i]) return false;
    }
    return true;
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
        /*if (TEST_COUNT%2==0) {
            for (int j=(size-1)/2;j<size;j++) {
                a[j] = TEST_COUNT;
            }
        }*/
        if (!compare(a)) {
            std::cout << "error: ";
            for (int k=0;k<size;k++) {
                std::cout << a[k] << " ";
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
  vector<int> b(a.size());
  std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
