/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: can
 *
 * Created on September 9, 2017, 11:11 AM
 */

#include <cstdlib>

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

int main(int argc, char** argv) {
    
    vector<int> list = vector<int>(10);
    for (int i=0; i<list.capacity(); i++) {
        list[i] = i * i;
    }
    
    for (int i=0; i<list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
    
    unordered_map<string, int> mapStrings;
    mapStrings["Zero"] = 0;
    mapStrings["One"] = 1;
    mapStrings["Two"] = 2;
    mapStrings["Three"] = 3;
    mapStrings["Four"] = 4;
    for (auto item = mapStrings.begin(); item != mapStrings.end(); item++) {
        cout << item->first << " " << item->second << endl;
    }
    
    map<int, string> mapNumbers;
    mapNumbers[0] = "Zero";
    mapNumbers[1] = "One";
    mapNumbers[2] = "Two";
    mapNumbers[3] = "Three";
    mapNumbers[4] = "Four";
    for (auto item = mapNumbers.begin(); item != mapNumbers.end(); item++) {
        cout << item->first << " " << item->second << endl;
    }

    return 0;
}

