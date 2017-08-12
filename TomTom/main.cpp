/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: can
 *
 * Created on August 12, 2017, 11:05 AM
 */

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// A: 00
// C: 01
// G: 10
// T: 11
class ACGTString {
public:
    ACGTString(const string& str) {
        array.resize(str.length()*2);
        for (int i=0;i<str.length();i++) {
            array[2*i] = str[i]=='G' || str[i]=='T';
            array[2*i+1] = str[i]=='C' || str[i]=='T';
        }
    }
    
    char operator[](int index) const {
        return array[2*index] ? (array[2*index+1]?'T':'G') : (array[2*index+1]?'C':'A');
    }
    
public:
    vector<bool> array;
};
/*
 * 
 */
int main(int argc, char** argv) {

    string test("ACGTAACCGGTTTGACACGTAACCGGTTTGACACGTAACCGGTTTGACACGTAACCGGTTTGACACGTAACCGGTTTGACACGTAACCGGTTTGACACGTAACCGGTTTGACACGTAACCGGTTTGACACGTAACCGGTTTGACACGTAACCGGTTTGAC");
    const ACGTString acgt(test);
    for (int i=0;i<test.length();i++) {
        cout << test[i];
    }
    cout << endl;
    for (int i=0;i<test.length();i++) {
        cout << acgt[i];
    }
    cout << endl;
    cout << sizeof(acgt.array) << endl;
    
    bitset<192> bittest;
    vector<bool> bittest2(192);
    cout << sizeof(bittest) << "-" << sizeof(bittest2) << endl;
    
    return 0;
}

