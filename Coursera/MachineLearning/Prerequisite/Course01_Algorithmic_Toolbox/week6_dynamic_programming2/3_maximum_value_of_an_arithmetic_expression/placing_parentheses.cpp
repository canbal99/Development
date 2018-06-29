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
    
    vector< vector<long long> > matrixMin(numbers.size());
    vector< vector<long long> > matrixMax(numbers.size());
    std::for_each(matrixMin.begin(), matrixMin.end(), [numbers](vector<long long>& v) {
        v = vector<long long>(numbers.size());
    });
    std::for_each(matrixMax.begin(), matrixMax.end(), [numbers](vector<long long>& v) {
        v = vector<long long>(numbers.size());
    });
    
    for (int i=0;i<numbers.size();i++) {
        matrixMin[i][i] = numbers[i];
        matrixMax[i][i] = numbers[i];
    }
    
    int value;
    for (int i=1;i<numbers.size();i++) {
        for (int j=0;j<numbers.size()-i;j++) { // j=0 i=3
            for (int k=1;k<=i;k++) {
                if (opers[j+i-k]=='+') {
                    value = eval(matrixMin[j][j+i-k], matrixMin[j+i+1-k][j+i], opers[j+i-k]);
                    if (matrixMin[j][j+i] > value || k==1) {
                        matrixMin[j][j+i] = value;
                    }
                    value = eval(matrixMax[j][j+i-k], matrixMax[j+i+1-k][j+i], opers[j+i-k]);
                    if (matrixMax[j][j+i] < value || k==1) {
                        matrixMax[j][j+i] = value;
                    }
                }
                else if (opers[j+i-k]=='-') {
                    value = eval(matrixMin[j][j+i-k], matrixMax[j+i+1-k][j+i], opers[j+i-k]);
                    if (matrixMin[j][j+i] > value || k==1) {
                        matrixMin[j][j+i] = value;
                    }
                    value = eval(matrixMax[j][j+i-k], matrixMin[j+i+1-k][j+i], opers[j+i-k]);
                    if (matrixMax[j][j+i] < value || k==1) {
                        matrixMax[j][j+i] = value;
                    }
                }
                else {
                    value = eval(matrixMin[j][j+i-k], matrixMin[j+i+1-k][j+i], opers[j+i-k]);
                    //std::cout << matrixMin[j][j+i-k] << opers[j+i-k] << matrixMin[j+i+1-k][j+i] << '=' << value << "\n";
                    if (matrixMin[j][j+i] > value || k==1) {
                        matrixMin[j][j+i] = value;
                    }
                    if (matrixMax[j][j+i] < value || k==1) {
                        matrixMax[j][j+i] = value;
                    }

                    value = eval(matrixMin[j][j+i-k], matrixMax[j+i+1-k][j+i], opers[j+i-k]);
                    //std::cout << matrixMin[j][j+i-k] << opers[j+i-k] << matrixMax[j+i+1-k][j+i] << '=' << value << "\n";
                    if (matrixMin[j][j+i] > value) {
                        matrixMin[j][j+i] = value;
                    }
                    if (matrixMax[j][j+i] < value) {
                        matrixMax[j][j+i] = value;
                    }

                    value = eval(matrixMax[j][j+i-k], matrixMin[j+i+1-k][j+i], opers[j+i-k]);
                    //std::cout << matrixMax[j][j+i-k] << opers[j+i-k] << matrixMin[j+i+1-k][j+i] << '=' << value << "\n";
                    if (matrixMin[j][j+i] > value) {
                        matrixMin[j][j+i] = value;
                    }
                    if (matrixMax[j][j+i] < value) {
                        matrixMax[j][j+i] = value;
                    }

                    value = eval(matrixMax[j][j+i-k], matrixMax[j+i+1-k][j+i], opers[j+i-k]);
                    //std::cout << matrixMax[j][j+i-k] << opers[j+i-k] << matrixMax[j+i+1-k][j+i] << '=' << value << "\n";
                    if (matrixMin[j][j+i] > value) {
                        matrixMin[j][j+i] = value;
                    }
                    if (matrixMax[j][j+i] < value) {
                        matrixMax[j][j+i] = value;
                    }
                }
            }
        }
    }
    /*for (int i=1;i<numbers.size();i++) {
        for (int j=0;j<numbers.size()-i;j++) { // j=0 i=3
            for (int k=1;k<=i;k++)
            {
                value = eval(matrixMin[j][j+i-k], matrixMin[j+i+1-k][j+i], opers[j+i-k]);
                //std::cout << matrixMin[j][j+i-k] << opers[j+i-k] << matrixMin[j+i+1-k][j+i] << '=' << value << "\n";
                if (matrixMin[j][j+i] > value || k==1) {
                    matrixMin[j][j+i] = value;
                }
                if (matrixMax[j][j+i] < value || k==1) {
                    matrixMax[j][j+i] = value;
                }
                
                value = eval(matrixMin[j][j+i-k], matrixMax[j+i+1-k][j+i], opers[j+i-k]);
                //std::cout << matrixMin[j][j+i-k] << opers[j+i-k] << matrixMax[j+i+1-k][j+i] << '=' << value << "\n";
                if (matrixMin[j][j+i] > value) {
                    matrixMin[j][j+i] = value;
                }
                if (matrixMax[j][j+i] < value) {
                    matrixMax[j][j+i] = value;
                }
                
                value = eval(matrixMax[j][j+i-k], matrixMin[j+i+1-k][j+i], opers[j+i-k]);
                //std::cout << matrixMax[j][j+i-k] << opers[j+i-k] << matrixMin[j+i+1-k][j+i] << '=' << value << "\n";
                if (matrixMin[j][j+i] > value) {
                    matrixMin[j][j+i] = value;
                }
                if (matrixMax[j][j+i] < value) {
                    matrixMax[j][j+i] = value;
                }
                
                value = eval(matrixMax[j][j+i-k], matrixMax[j+i+1-k][j+i], opers[j+i-k]);
                //std::cout << matrixMax[j][j+i-k] << opers[j+i-k] << matrixMax[j+i+1-k][j+i] << '=' << value << "\n";
                if (matrixMin[j][j+i] > value) {
                    matrixMin[j][j+i] = value;
                }
                if (matrixMax[j][j+i] < value) {
                    matrixMax[j][j+i] = value;
                }
            }
        }
    }*/
    
    for (int i=0;i<numbers.size();i++) {
        for (int j=0;j<numbers.size();j++) {
            printf("%03lld ", matrixMin[i][j]);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for (int i=0;i<numbers.size();i++) {
        for (int j=0;j<numbers.size();j++) {
            printf("%03lld ", matrixMax[i][j]);
        }
        std::cout << "\n";
    }
    
    return matrixMax[0][numbers.size()-1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
