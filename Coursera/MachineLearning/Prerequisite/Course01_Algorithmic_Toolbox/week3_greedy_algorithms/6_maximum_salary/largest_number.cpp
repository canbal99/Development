#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool compare (string left, string right) {
    
    if (right.length() == left.length()) {
        int comp = right.compare(left);
        return comp < 0;
    } else if (right.length() > left.length()) {
        int comp = right.substr(0,left.length()).compare(left);
        if (comp == 0) {
            return compare(left,right.substr(left.length()));
        } else {
            return comp < 0;
        }
    } else {
        int comp = right.compare(left.substr(0,right.length()));
        if (comp == 0) {
            return compare(left.substr(right.length()),right);
        } else {
            return comp < 0;
        }
    }
}

string largest_number(vector<string> a) {
  //write your code here
  
  std::sort (a.begin(), a.end(), compare);
  //for (int i=0;i<a.size();i++) {
  //    std::cout << a[i] << "\n";
  //}
    
  std::stringstream ret;
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
