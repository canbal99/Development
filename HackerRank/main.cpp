#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int count;
    cin >> count;
    multiset<string> nameList;
    string name, email;
    
    for (int i=0;i<count;i++) {
        cin >> name >> email;
        int index = email.rfind('@');
        if (index>=0 && email.substr(index).compare("@gmail.com")==0) {
            nameList.insert(name);
        }
    }
    
    for (auto n : nameList) {
        cout << n << endl;
    }
    
    return 0;
}
