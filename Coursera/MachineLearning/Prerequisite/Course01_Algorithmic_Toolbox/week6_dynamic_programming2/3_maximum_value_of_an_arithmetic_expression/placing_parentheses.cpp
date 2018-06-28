#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

long long get_maximum_value(const string &exp) {
    //write your code here
    std::stringstream stream(exp);
    
    vector<long long> numbers;
    vector<char> opers;
    
    int number;
    char oper;
    stream >> number;
    numbers.push_back(number);
    while(!stream.eof()) {
        stream >> oper;
        opers.push_back(oper);
        stream >> number;
        numbers.push_back(number);
    }
    
    /*for (int i=0;i<opers.size();i++) {
        std::cout << "num:" << numbers[i] << '\n';
        std::cout << "char:"<< (char) opers[i] << '\n';
    }
    std::cout << "num:" << numbers[opers.size()] << '\n';*/
    
    vector< vector<long long> > map(numbers.size());
    std::for_each(map.begin(), map.end(), [numbers](vector<long long>& v) {
        v = vector<long long>(numbers.size());
    });
    
    for (int i=0;i<numbers.size();i++) {
        map[i][i] = numbers[i];
    }
    int value = 0;
    for (int i=1;i<numbers.size();i++) {
        for (int j=0;j<numbers.size()-i;j++) {
            value = eval(map[j][j+i-1], numbers[j+i], opers[j+i-1]);
            if (map[j][j+i] < value) {
                map[j][j+i] = value;
            }
        }
    }
    
    for (int i=0;i<numbers.size();i++) {
        for (int j=0;j<numbers.size();j++) {
            printf("%03d ", map[i][j]);
            //std::cout << map[i][j] << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
