#include <iostream>
#include <vector>

using std::vector;

#define MIN2(a,b)        (a<b?a:b)
#define MIN3(a,b,c)      (MIN2((MIN2(a,b)),c))

int get_change(int m) {
    //write your code here
    
    vector<int> lookup(m+1);
    lookup[0] = 0;
    lookup[1] = 1;
    lookup[2] = 2;
    lookup[3] = 1;
    lookup[4] = 1;
    
    for (int i=5;i<=m;i++) {
        lookup[i] = 1 + MIN3(lookup[i-1],lookup[i-3],lookup[i-4]);
    }
    
    return lookup[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
