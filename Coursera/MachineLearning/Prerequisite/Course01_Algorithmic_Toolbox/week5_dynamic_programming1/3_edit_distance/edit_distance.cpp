#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

#define MIN2(a,b)   (a<b?a:b)
#define MIN3(a,b,c) (MIN2(MIN2(a,b),c))

int edit_distance(const string &str1, const string &str2) {
    //write your code here
    
    vector< vector<int> > editDistance(str1.size()+1);
    for (int i=0;i<editDistance.size();i++) {
        editDistance[i] = vector<int>(str2.size()+1);
    }
    
    for (int y=0;y<=str1.size();y++) {
        editDistance[y][0] = y;
    }
    
    for (int x=0;x<=str2.size();x++) {
        editDistance[0][x] = x;
    }
    
    for (int y=1;y<=str1.size();y++) {
        for (int x=1;x<=str2.size();x++) {
            bool equals = (str1[y-1]==str2[x-1]);
            editDistance[y][x] = 1 + MIN3(editDistance[y-1][x],editDistance[y][x-1],editDistance[y-1][x-1]-(equals?1:0));
        }
    }
    
    return editDistance[str1.size()][str2.size()];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
