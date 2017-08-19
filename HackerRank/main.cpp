#include <iostream>
#include <set>
#include <stdio.h>

using namespace std;

#define RANDOM(min,max)     (rand()%(max-min+1) + min)

void printArrivalTimes(int n, int k, bool canceled) {
    for (int l = 0; l < n - 2; l++) {
        if (!canceled)
            cout << RANDOM(-1000,-1) << ' ';
        else
            cout << RANDOM(1,1000) << ' ';
    }
    if (!canceled)
        cout << "0 1" << endl;
    else
        cout << "0 -1" << endl;
}
int main(int argc, char** argv) {
    srand(time(NULL));
    set<int> nValues;
    int t, n, k, a, i, j, l;
    for (i = 0; i < 1; i++) {
        t = 5;//RANDOM(1,5);
        cout << t << endl;
        for (j = 0; j < t; j++) {
            do { // The value of  must be distinct across all the test cases.
                n = RANDOM(3,200);
            } while (!nValues.insert(n).second);
            k = RANDOM(1,n);
            cout << n << ' ' << k << endl;
            printArrivalTimes(n,k,j%2==0);
        }
    }
        
    return 0;
}

